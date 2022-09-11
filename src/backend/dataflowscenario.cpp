#include "dataflowscenario.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <random>
#include <thread>
#include <chrono>
#include "packet.cpp"

size_t DataflowScenario::GetSize() const
{
    return data_packet_size_;
}

EndHost *DataflowScenario::GetStartNode() const
{
    return start_node_;
}

EndHost *DataflowScenario::GetEndNode() const
{
    return end_node_;
}

std::string GenerateRandomPacketId()
{
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    auto rng = std::default_random_engine{};
    std::shuffle(std::begin(alphabet), std::end(alphabet), rng);
    return alphabet.substr(4);
}

std::list<Packet> DataflowScenario::GenerateData()
{
    int max_size = mtu_type - Packet::GetHeaderLength();                  // max bytes that packet can take
    auto num_of_whole_packets = (data_packet_size_ * 1000000) / max_size; // MB = million
    auto remaining_length = data_packet_size_ % max_size;

    std::list<Packet> result;
    auto seqnum = 1;
    auto id = GenerateRandomPacketId();
    for (size_t i = 0; i < num_of_whole_packets; i++)
    {
        result.push_back(Packet(id, max_size, seqnum));
        seqnum++;
    }
    result.push_back(Packet(id, remaining_length, seqnum));
    return result;
}

bool DataflowScenario::IsReachable(std::map<std::string, std::vector<Node *>> &graph, Node *src, Node *dest, std::map<std::string, bool> &discovered, std::vector<Node *> &path)
{
    // mark the current node as discovered
    discovered[src->GetName()] = true;

    // include the current node in the path
    path.push_back(src);

    // if destination vertex is found
    if (*src == *dest)
    {
        return true;
    }

    // do for every edge (src, n)
    for (auto n : graph[src->GetName()])
    {
        // if 'n' is not yet discovered
        if (!discovered[n->GetName()])
        {
            if (IsReachable(graph, n, dest, discovered, path))
            {
                return true;
            }
        }
    }

    // backtrack: remove the current node from the path
    path.pop_back();

    // return false if destination vertex is not reachable from src
    return false;
}

void printPath(std::vector<Node *> const &path)
{
    for (auto n : path)
    {
        std::cout << n->GetName() << ' ';
    }
    std::cout << std::endl;
}

std::vector<Node *> DataflowScenario::FindPath()
{
    std::vector<Node *> path;

    std::map<std::string, std::vector<Node *>> graph;
    std::map<std::string, bool> visited;

    // init adjacent list and visited list
    for (auto node : all_nodes_)
    {
        graph.insert({node->GetName(),
                      node->GetAdjacents()});
        visited.insert({node->GetName(), false});
    }

    if (IsReachable(graph, start_node_, end_node_, visited, path))
    {
        //std::cout << "Path exists from node " << start_node_.GetName() << " to node " << end_node_.GetName() << std::endl;
    }
    else
    {
        std::cout << "No path exists between nodes " << start_node_->GetName() << " and " << end_node_->GetName() << std::endl;
    }

    return path;
}

bool DataflowScenario::IsValid()
{
    auto nodes = FindPath();

    // If Path is shorter than minimum node count, it's not valid.
    if (nodes.size() < MinNodeCount)
    {
        return false;
    }
    auto iterator_start = nodes.begin();
    auto iterator_end = nodes.end();
    iterator_end--;

    auto start = *iterator_start;
    auto end = *iterator_end;

    if (iterator_start != nodes.end() && *start == *start_node_)
    {
        if (iterator_end != nodes.end() && *end == *end_node_)
        {
            return true;
        }
    }

    return false;
}

Link *DataflowScenario::GetLinkBetweenNodes(Node *node1, Node *node2)
{
    for (auto link : all_links_)
    {
        if (link->IsConnected(node1, node2))
        {
            return link;
        }
    }
    return nullptr;
}

std::string DataflowScenario::PrintWholeRoute(std::vector<Node *> nodes, std::vector<Link *> links)
{
    std::string path = " ";
    for (size_t i = 0; i < nodes.size(); i++)
    {
        if (i >= nodes.size() - 1)
        {
            std::cout << "(" << nodes[i]->GetName() << ") " << std::endl;
            path += "(" + nodes[i]->GetName() + ")";
            break;
        }
        std::cout << "(" << nodes[i]->GetName() << ") ";
        std::cout << "--" << links[i]->GetTransmissionSpeed() << "-- ";
        path += "(" + nodes[i]->GetName() + ") --" + std::to_string(links[i]->GetTransmissionSpeed()) + "-- ";
    }
    return path;
}

void DataflowScenario::PrintSummary(std::vector<Router *> nodes, std::list<Packet> packets)
{
    std::cout << "\n"
              << std::endl;
    std::cout << "************************************" << std::endl;
    std::cout << "******** Scenario finished *********" << std::endl;
    std::cout << "************************************\n"
              << std::endl;

    std::cout << "Summary:" << std::endl;
    std::cout << "  Number of packets sent by " << start_node_->GetName() << ": " << packets.size() << std::endl;
    std::cout << "  Number of packets received by " << end_node_->GetName() << ": " << end_node_->GetNumOfReceivedPackets() << std::endl;
    for (auto r : nodes)
    {
        std::cout << "  Packets dropped by " << r->GetName() << ": " << r->GetLostPackets() << std::endl;
    }
}

Summary DataflowScenario::Run()
{
    std::cout << "************************************" << std::endl;
    std::cout << "******* Scenario is starting *******" << std::endl;
    std::cout << "************************************\n"
              << std::endl;

    if (IsValid())
    {
        auto path = FindPath();
        std::vector<Link *> links_in_path;
        for (size_t i = 0; i < path.size() - 1; i++)
        {
            links_in_path.push_back(GetLinkBetweenNodes(path[i], path[i + 1]));
        }
        std::string backgroun_info = " Dataflow path: \n";
        std::cout << "Dataflow path: " << std::endl;
        backgroun_info += PrintWholeRoute(path, links_in_path) + "\n\n";
        std::cout << std::endl;

        std::vector<Router *> routers;

        auto packets = GenerateData();
        backgroun_info += " Size of the original data: " + std::to_string(data_packet_size_) + " MB\n";
        backgroun_info += " Packet MTU = " + std::to_string((int)Ethernet) + " bytes\n";
        std::cout << "Size of the data to be sent: " << data_packet_size_ << " MB" << std::endl;
        std::cout << "Number of packets: " << packets.size() << " (Packet MTU = " << int(Ethernet) << " bytes)\n"
                  << std::endl;

        // Start timer
        auto start = std::chrono::high_resolution_clock::now();

        std::list<std::thread> threads;
        // Create thread for every router along the path, these nodes will be waiting for the packets to arrive
        for (size_t j = 1; j < path.size() - 1; j++)
        {
            auto router = dynamic_cast<Router *>(path[j]);
            auto link = GetLinkBetweenNodes(path[j], path[j + 1]);
            threads.push_back(GetThread(router, path[j + 1], link->GetTransmissionSpeed()));
            routers.push_back(router);
        }
        NsTerminal *terminal;
        terminal = terminal->getInstance();
        // This thread starts pushing the packets forward, the thread is detached to run as its own
        std::thread data_sending_thread(&DataflowScenario::PacketSendingThread, this, packets, path[1], links_in_path[0]->GetTransmissionSpeed(), path, terminal);
        data_sending_thread.detach();

        // Mainthread will wait for the other threads to finish before finishing. If there are
        // packets in the buffers, this will take a while
        for (auto &thr : threads)
        {
            thr.join();
        }

        // Stop time
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        return Summary(backgroun_info, elapsed, packets.size(), end_node_->GetNumOfReceivedPackets(), routers);
    }
    std::chrono::duration<double> e;
    return Summary("", e, 0, 0, std::vector<Router *>{});
}

void DataflowScenario::PacketSendingThread(std::list<Packet> packets, Node *next_node, size_t speed, std::vector<Node *> path, NsTerminal *terminal)
{
    auto trans_speed = speed * 1000; // Kbps
    std::cout << "Started to send packets. Please wait... " << std::endl;
    int i = 0;
    while (packets.size() > 0)
    {
        auto packet = packets.front();
        auto size = packet.GetSize();
        double delay = (size * 8.0 / trans_speed) * 1000.0; // to Milliseconds

        // Wait ... simulate the time to transmit the packet
        std::this_thread::sleep_for(std::chrono::milliseconds((int)delay));

        // Send packet
        start_node_->SendPacket(packet, next_node);
        packets.pop_front();
        if (i == 10)
        {
            terminal->consoleLog("Packet sent from " + start_node_->GetName() + " Seqnum: " + std::to_string(packet.GetSequenceNumber()) + "\n");
            i = 0;
        }

        //terminal->consoleLog("Packet sent from " + start_node_->GetName() + " Seqnum: " + std::to_string(packet.GetSequenceNumber()));
        //std::cout << "packet sent " << i << std::endl;
        i++;
    }

    Terminate(path);
}

void DataflowScenario::PacketTransferThread(Router *sending_node, Node *next_node, size_t speed)
{
    auto router = dynamic_cast<Router *>(sending_node);
    router->SetRunningState(true);
    router->PacketFlowThread(next_node, speed);
}

std::thread DataflowScenario::GetThread(Router *r, Node *n2, size_t s)
{
    return std::thread(&DataflowScenario::PacketTransferThread, this, r, n2, s);
}

void DataflowScenario::Terminate(std::vector<Node *> path)
{
    for (auto n : path)
    {
        n->SetRunningState(false);
    }
}
