#ifndef NODE
#define NODE

#include <string>
#include <vector>

#include "packet.hpp"

/**
 * @brief Nodetype enum
 * 
 * The nodes can be either EndHost or Router
 * 
 */
enum NodeType
{
    endhost,
    router
};

/**
 * @brief Abstract Node class
 * 
 * Other network nodes derive from this class (EndHost, Router)
 */
class Node
{
public:
    /**
     * @brief Construct a new Node object
     * 
     * @param name Name given by user, for example "PC-1", "Router-5" or "John's PC"
     * 
     * In addition, constructor initializes the IP address, Simulator will take care that it's unique
     */
    Node(std::string name) : name_(name), is_running_(false) {}

    virtual ~Node() {}

    /**
     * @brief Virtual function. Get the Node type
     * 
     * @return NodeType 
     */
    virtual NodeType GetType() const = 0;

    /**
     * @brief Get the Name object
     * 
     * @return std::string Name given to the node by user
     */
    std::string GetName() const;

    /**
     * @brief Get the IPAddress object
     * 
     * @return std::string IP address, generated by Simulator class
     */
    std::string GetIPAddress() const;

    /**
     * @brief Get the Adjacents Nodes of this object
     * 
     * @return std::list<Node *> 
     * 
     * Needed for the FindPath method
     */
    std::vector<Node *> GetAdjacents() const;

    /**
     * @brief Sets random generated IP Address to tis Node
     * 
     * @param address IP in format XXX.XXX.XXX.XXX
     */
    void SetIPAddress(std::string &address);

    /**
     * @brief Connects this Node with another node which is added to adjacent list
     * 
     * @param other EndHost or Router
     */
    void Connect(Node *&other);

    /**
     * @brief Sends packet to next Node, 
     * 
     * @param p Packet to be sent
     * @param node_to_send EndHost or Router
     */
    void SendPacket(Packet p, Node *node_to_send);

    /**
     * @brief Virtual method for receiving packet. Implemented differently in EndHost and Router
     * 
     * @param p Packet object
     */
    virtual void ReceivePacket(Packet p) = 0;

    /**
     * @brief Set the Running State to true or false. This is used to control the packet flow 
     * from DataflowScenario class. If all packets are sent, the other nodes will be notified. 
     * 
     * @param val true or false
     */
    void SetRunningState(bool val);

    /**
     * @brief If Nodes have same names or IP addresses, they are equal
     * 
     * @param other 
     * @return true 
     * @return false 
     */
    bool operator==(const Node &other) const;

private:
    std::string name_;
    std::string IP_address_;
    std::vector<Node *> adjacents_;

protected:
    bool is_running_;
};

#endif
