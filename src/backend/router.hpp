#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <queue>
#include "node.hpp"
#include "packet.hpp"
#include <thread>
#include <mutex>
#include "../frontend/components/ns-terminal.h"

/**
 * @brief Router class, presents one type of node in the network system. 
 * Router object is for transfering data between other nodes. 
 *
 */
class Router : public Node
{
public:
    /**
     * @brief Construct a new Router object
     *
     * @param name
     * @param max_buffer
     */
    Router(std::string name, size_t max_buffer)
        : Node(name), max_buffer_(max_buffer)
    {
        terminal = terminal->getInstance();
    }

    /**
     * @brief Destroy the Router object
     *
     */
    ~Router() {}

    /**
     * @brief Get the Packet Queue object
     *
     * @return std::queue<Packet>&
     */
    std::queue<Packet> &GetPacketQueue();
    /**
     * @brief Get number of lost packets
     *
     * @return unsigned int
     */
    unsigned int GetLostPackets();
    /**
     * @brief Get max buffer size
     *
     * @return int
     */
    int GetMaxBufferSize() const;

    /**
     * @brief Get the node type
     *
     * @return NodeType = router
     */
    NodeType GetType() const { return router; }

    unsigned int GetNumOfDroppedPackets() const;

    /**
     * @brief Add Packet to the buffer if it's not full, otherwise the packet will be dropped
     * 
     * @param p Packet to queue
     */
    void ReceivePacket(Packet p);

    /**
     * @brief Dataflow PacketTransferThread takes care running this method
     * 
     * @param next_node Next node in path, EndHost or Router
     * @param speed Speed of the link that is between this and the next node
     */
    void PacketFlowThread(Node *next_node, size_t speed);

private:
    std::queue<Packet> buffer_;
    unsigned int lost_packets_;
    size_t max_buffer_;
    // lock guard for the buffer
    std::mutex buffer_lock_;
    int i;
    NsTerminal *terminal;
};

#endif
