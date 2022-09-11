#ifndef DATAFLOWSCENARIO
#define DATAFLOWSCENARIO

#include "endhost.hpp"
#include "node.hpp"
#include "packet.hpp"
#include "link.hpp"
#include "router.hpp"
#include <list>
#include <vector>
#include <map>
#include "summary.hpp"
#include "../frontend/components/ns-terminal.h"

/**
 * @brief Enum of different MTU's
 * 
 * For simplicity, this version only uses Ethernet
 * See more: https://en.wikipedia.org/wiki/Maximum_transmission_unit
 * 
 */
enum Packet_MTU
{
    Ethernet = 1500,
    LTE = 1428,
    _5G = 1420,
    IEEE = 2304
};

/**
 * @brief class DataflowScenario
 * 
 * Description:
 * ------------
 * DataflowScenario represents a scenario made by user where data is sent 
 * from EndHost (start) to EndHost (end). User can define which node will sent data 
 * to where and what is the data size
 * These scenarios will be stored to Simulator class that finally runs all the scenarios
 * 
 * (*EndHost start*) ---link--- (*Router r*) ---link--- (*EndHost end*)
 */
class DataflowScenario
{
public:
    /**
     * @brief Construct a new Dataflow Scenario object
     * 
     * @param s Start node
     * @param e End Node
     * @param size Data size MB (megabyte)
     * 
     * The DataflowScenario class has a constructor that takes in the start node (EndHost), 
     * end node (EndHost), and size of the data (size_t)
     */
    DataflowScenario(EndHost *s, EndHost *e, size_t size, std::list<Node *> all_nodes, std::list<Link *> all_links)
        : start_node_(s), end_node_(e), data_packet_size_(size), all_nodes_(all_nodes), all_links_(all_links) {}

    /**
     * @brief Get the size of data to be sent
     * 
     * @return size_t 
     */
    size_t GetSize() const;

    /**
     * @brief Get the Start Node object
     * 
     * @return EndHost 
     */
    EndHost *GetStartNode() const;

    /**
     * @brief Get the End Node object
     * 
     * @return EndHost 
     */
    EndHost *GetEndNode() const;

    /**
     * @brief Get the Link Between Nodes 
     * 
     * @param node1 
     * @param node2 
     * @return Link* 
     */
    Link *GetLinkBetweenNodes(Node *node1, Node *node2);

    /**
     * @brief Generates list of packets based on the size
     * 
     * Currently the system is using the default value of the Ethernet MTU
     * which is 1500 bytes / packet. Some bytes are reserved for the header.
     * See Packet class for more information
     * 
     * @return std::list<Packet> 
     */
    std::list<Packet> GenerateData();

    /**
     * @brief Checks if this scenario is valid for run
     * 
     * @return true 
     * @return false 
     * 
     * calls FindPath and checks if the end node can be reached from start node,
     * the path also needs to be at least three nodes long,
     * if not returns false, otherwise true
     */
    bool IsValid();

    /**
     * @brief Runs this scenario:
     * 1. If scenario is valid, the data will flow through route from FindPath
     * 2. GenerateData is called which is creating a list of packets to be sent
     * 3. Starting node starts sending packets through link to the next node on the route 
     * 4. Continues until all packets are sent
     * 
     */
    Summary Run();

private:
    EndHost *start_node_;
    EndHost *end_node_;
    size_t data_packet_size_;
    std::list<Node *> all_nodes_;
    std::list<Link *> all_links_;
    const size_t MinNodeCount = 3;
    Packet_MTU mtu_type = Ethernet;

    /**
     * @brief Finds shortest path from start node to end node (if exists)
     * 
     * @return std::list<Node> 
     * 
     * Before the scenario can begin its actions, the route needs to be calculated.
     * This method needs to find all the nodes between the start and end. If the end node is not
     * reachable, this scenario is unvalid.
     * 
     * If the nodes are connected like this:
     * 
     * (*EndHost start*) ---link--- (*Router r*) ---link--- (*EndHost end*)
     * 
     * FindPath will return list: [start, r, end]
     *
     */
    std::vector<Node *> FindPath();

    /**
     * @brief Helper function for FindPath. Function performs DFS traversal in a directed graph to find the 
     * complete path between source and destination nodes
     * 
     * @param graph map of adjacent lists
     * @param src source Node (EndHost)
     * @param dest destination Node (EndHost)
     * @param discovered map of discovered nodes
     * @param path 
     * @return true 
     * @return false 
     */
    bool IsReachable(std::map<std::string, std::vector<Node *>> &graph, Node *src, Node *dest, std::map<std::string, bool> &discovered, std::vector<Node *> &path);

    /**
     * @brief Prints and returns the whole route in format
     *  (endhost) --link_speed-- (router) --link_speed-- (endhost)
     * 
     * @param nodes Nodes in the current path
     * @param links Links in the current path
     */
    std::string PrintWholeRoute(std::vector<Node *> nodes, std::vector<Link *> links);

    /**
     * @brief Thread that sends one packet at the time from the list that was created from bigger data 
     * unit (data_packet_size_)
     * 
     * @param packets Packets to be sent
     * @param next_node The second node on this path
     * @param speed Link speed between the start_node_ and next node 
     * @param path Whole path in this simulation. The method will call termination when all packets are sent
     */
    void PacketSendingThread(std::list<Packet> packets, Node *next_node, size_t speed, std::vector<Node *> path, NsTerminal *terminal);

    /**
     * @brief 
     * 
     * @param sending_node Router that transfers data 
     * @param next_node Next node after the router
     * @param speed Link speed between these nodes
     */
    void PacketTransferThread(Router *sending_node, Node *next_node, size_t speed);

    /**
     * @brief Get the Packet Transfer Thread object
     * 
     * @param n1 starting node
     * @param n2 next node on the path
     * @param s link speed between these nodes
     * @return std::thread 
     */
    std::thread GetThread(Router *r, Node *n2, size_t s);

    /**
     * @brief Terminates the current simulation, that is, notifys the nodes
     * in the path that no more packets are to be transferred and they can stop waiting
     * 
     * @param path Path of nodes in this simulation
     */
    void Terminate(std::vector<Node *> path);

    /**
     * @brief Utility function for development purposes and to help testing
     * 
     * @param routers Routers in the path
     * @param packets List of packets created in this scenario
     * @param end 
     */
    void PrintSummary(std::vector<Router *> routers, std::list<Packet> packets);
};

#endif