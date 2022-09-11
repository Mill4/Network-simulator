#ifndef ENDHOST_H
#define ENDHOST_H

#pragma once

#include "node.hpp"
#include "packet.hpp"
#include <list>
#include "../frontend/components/ns-terminal.h"

/**
 * @brief EndHost class represent a network node that can send and receive data. 
 * Can be thought as a PC as well. 
 * 
 */
class EndHost : public Node
{
public:
    EndHost(std::string name) : Node(name)
    {
        terminal->getInstance();
    }

    ~EndHost() {}

    /**
     * @brief Get the node type
     * 
     * @return NodeType = endhost
     */
    NodeType GetType() const { return endhost; }

    /**
     * @brief Receives packet i.e, puts it in the packet list 
     * 
     * @param p 
     */
    void ReceivePacket(Packet p);

    /**
     * @brief Get num of received packets
     * 
     * @return size_t 
     */
    size_t GetNumOfReceivedPackets() const;

    /**
     * @brief Empty the packet list
     * 
     */
    void Clear();

private:
    std::list<Packet> received_packets_;
    NsTerminal *terminal;
};

#endif
