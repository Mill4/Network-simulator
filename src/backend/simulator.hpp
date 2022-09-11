#ifndef SIMULATOR
#define SIMULATOR

#pragma once
#include <list>
#include <iostream>

#include "node.hpp"
#include "dataflowscenario.hpp"
#include "link.hpp"

/**
 * @brief class Simulator
 * Description:
 * ------------
 * The Simulator is a class that stores pointers of all the network elements
 * in different list containers. The class allows basic
 * manipulation of these network elements through the functions described
 * below.
 * 
 * The class obviously has a lists of all nework elements pointers as a private member.
 * This class is not copyable (also means not assignable), so copy and assignment 
 * operations for this class is prevented.
 */
class Simulator
{
public:
    /**
     * @brief Construct a new Simulator object
     * The Simulator class has a parameterless constructor that default constructs
     * the members.
     * 
     */
    Simulator() {}

    /**
     * @brief Destroy the Simulator object
     * The destructor of the Simulator class deletes all the network elements in the
     * from their lists.
     */
    ~Simulator();

    /**
     * @brief Create a Node object and add it to the system
     * 
     * @param name name of the node, for example "PC-1"
     * @param type type of the node, for example endhost
     * 
     * This methods creates a new node object and adds it to the system
     * This method also allocates the IP Address
     */
    Node *CreateNode(std::string name, NodeType type);

    /* method AddNode
        * Arguments: A pointer to node.
        * Description: Adds the given node to the simulator.
        *  
        */

    /**
     * @brief Adds the given node to the simulator
     * 
     * @param node For example EndHost
     * 
     * If the pointer is NULL, std::logic_error is thrown.
     * 
     * When a node is added to the simulator, it's ownership
     * is transferred. When the simulator is destroyed, all
     * the nodes are destroyed too.
     */
    void AddNode(Node *node);

    /**
     * @brief Remove the given node from the simulator
     * 
     * @param node For example EndHost
     * 
     * If the pointer is NULL, std::logic_error is thrown.
     * 
     */
    void RemoveNode(Node *node);

    /**
     * @brief Adds a connection, Link, between two nodes
     * 
     * @param node1 Node to be connected (EndHost, Router)
     * @param node2 Node to be connected (EndHost, Router)
     * @param transmission_speed Transmission speed of this link as double
     * 
     * This method is responsible for creating a new Link object
     */
    Link* AddLink(Node *, Node *, double);

    /**
     * @brief Adds a new dataflow scenario to the system
     * 
     * @param start Name of the starting node (EndHost)
     * @param end Name of the target node (EndHost)
     * @param dataSize Size of the data to be sent
     * 
     * This method will take care of creating a new object
     */
    void AddScenario(Node *, Node *, size_t dataSize);

    /**
     * @brief Get the Node object
     * 
     * @return std::list<Node *> 
     * The function returns a const reference to the Node's
     * list of Node pointers. The function takes no parameters and does not change 
     * the Node's state, i.e. the function should be const.
     */
    std::list<Node *> GetNodes() const;

    /**
     * @brief Get the Link object
     * 
     * @return std::list<Link> Returns all the Links, connections, in the system
     */
    std::list<Link *> GetLinks() const;

    /**
     * @brief Get the DataflowScenario objects in the system
     * 
     * @return std::list<DataflowScenario> 
     */
    std::list<DataflowScenario> GetScenarios() const;

    /**
     * @brief Runs the scenario(s) defined by user. After the run a summary will be available. 
     * See DataflowScenario and Summary classes for more details
     * 
     */
    std::string RunScenarios();

private:
    // Holds all the nodes created in the network
    std::list<Node *> nodes_;
    std::list<Link *> links_;
    std::list<DataflowScenario> scenarios_;
    std::list<std::string> IPAddresses_;

    size_t PC_name_counter = 1;
    size_t Router_name_counter = 1;

    // Disallow copying
    Simulator(const Simulator &) {}
    Simulator &operator=(const Simulator &)
    {
        return *this;
    };

    /**
     * @brief Utility function to generate random IP Address in format: XXX.XXX.XXX.XXX
     * 
     * @return std::string IP as string
     * 
     * This method is not suitable to generate real IP addresses that are used
     * in real life. This class keeps track of all addresses in the system and makes
     * sure no duplicate addresses are generated. 
     */
    std::string GenerateRandomIPAddress();

    /**
     * @brief Get the Node by name, helper function
     * 
     * @param name Name as string, originally given by user
     * @return Node* pointer to the Node object or nullptr if no Node were found by given name
     */
    Node *GetNodeByName(std::string name);
};

#endif