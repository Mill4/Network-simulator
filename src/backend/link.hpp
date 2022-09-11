#ifndef LINK_H
#define LINK_H

#include <iostream>
#include "node.hpp"

/**
 * @brief Link Class represents a connection between nodes. 
 * In our system, the link only has speed and no other properties.
 *
 */
class Link
{
public:
    /**
     * @brief Construct a new Link object
     *
     * @param transmission_speed
     * @param connection_node1
     * @param connection_node2
     */
    
    Link(size_t transmission_speed, Node *connection_node1, Node *connection_node2)
        : transpeed_(transmission_speed), node1_(connection_node1), node2_(connection_node2) {}

    /**
     * @brief Destroy the Link object
     *
     */
    virtual ~Link() {}

    /**
     * @brief Get the Transmission Speed of the link
     *
     * @return double
     */
    size_t GetTransmissionSpeed();

    /**
     * @brief Get the Node 1 object
     *
     * @return Node
     */
    Node *GetNode1();

    /**
     * @brief Get the Node 2 object
     *
     * @return Node
     */

    Node *GetNode2();

    /**
     * @brief Checks if given nodes are connected to this Link
     * 
     * @param n1 EndHost or Router
     * @param n2 EndHost or Router
     * @return true 
     * @return false 
     */
    bool IsConnected(Node *n1, Node *n2) const;
    void setId(int);
    int getId() const;

private:
    size_t transpeed_;
    Node *node1_;
    Node *node2_;
    int id_;
};

#endif // LINK_H
