#include "simulator.hpp"
#include "endhost.hpp"
#include "router.hpp"
#include <algorithm>

#include <random>

Simulator::~Simulator()
{
    for (auto n : nodes_)
    {
        delete n;
    }
}

Node *Simulator::GetNodeByName(std::string name)
{
    for (auto n : nodes_)
    {
        if (n->GetName() == name)
        {
            return n;
        }
    }
    return nullptr;
}

std::string Simulator::GenerateRandomIPAddress()
{
    std::random_device crypto_random_generator;
    std::uniform_int_distribution<int> int_distribution(0, 256);

    std::string IP;
    bool set = false;
    while (IP.empty() || !set)
    {
        IP = std::to_string(int_distribution(crypto_random_generator)) + "." + std::to_string(int_distribution(crypto_random_generator)) + "." + std::to_string(int_distribution(crypto_random_generator)) + "." + std::to_string(int_distribution(crypto_random_generator));
        if (!(std::find(IPAddresses_.begin(), IPAddresses_.end(), IP) != IPAddresses_.end()))
        {
            IPAddresses_.push_back(IP);
            break;
        }
    }

    return IP;
}

Node *Simulator::CreateNode(std::string name, NodeType type)
{
    Node *node = nullptr;
    std::string ip = GenerateRandomIPAddress();
    if (type == endhost)
    {
        std::string n;
        if (name.empty())
        {
            n = "PC-" + std::to_string(PC_name_counter);
            PC_name_counter++;
        }
        else
        {
            n = name;
        }
        node = new EndHost(n);
        node->SetIPAddress(ip);
        AddNode(node);
    }
    else if (type == router)
    {
        std::string n;
        if (name.empty())
        {
            n = "R-" + std::to_string(Router_name_counter);
            Router_name_counter++;
        }
        else
        {
            n = name;
        }
        node = new Router(n, 100);
        node->SetIPAddress(ip);
        AddNode(node);
    }
    return node;
}

void Simulator::AddNode(Node *node)
{
    nodes_.push_back(node);
}

void Simulator::RemoveNode(Node *node)
{
    for (auto n : nodes_)
    {
        if (n->GetName() == node->GetName())
        {
            nodes_.remove(node);
            delete node;
        }
    }
}

Link* Simulator::AddLink(Node *node1, Node *node2, double transmission_speed)
{
    // auto n1 = GetNodeByName(node1->GetName());
    // auto n2 = GetNodeByName(node2->GetName());
    auto link = new Link(transmission_speed, node1, node2);
    link->setId(links_.size() + 1);
    links_.push_back(link);
    node1->Connect(node2);
    node2->Connect(node1);
    return link;
}

void Simulator::AddScenario(Node *start, Node *end, size_t dataSize)
{
    auto s = dynamic_cast<EndHost *>(start);
    auto e = dynamic_cast<EndHost *>(end);

    if (s != nullptr && e != nullptr)
    {
        scenarios_.push_back(DataflowScenario(s, e, dataSize, nodes_, links_));
    }
}

std::list<Node *> Simulator::GetNodes() const
{
    return nodes_;
}

std::list<Link *> Simulator::GetLinks() const
{
    return links_;
}

std::list<DataflowScenario> Simulator::GetScenarios() const
{
    return scenarios_;
}

std::string Simulator::RunScenarios()
{

    std::string result;
    NsTerminal *terminal = terminal->getInstance();
    for (auto s : scenarios_)
    {
        auto summary = s.Run();
        result += summary.GetSummaryAsString() + "\n\n";
        //auto summary = s.GetSummary();
    }
    std::cout << result << std::endl;
    return result;
}
