#include "link.hpp"
#include "node.hpp"

/**
 * @brief
 *
 * @return double
 */
size_t Link::GetTransmissionSpeed()
{
    return transpeed_;
}

Node *Link::GetNode1()
{
    return node1_;
}

Node *Link::GetNode2()
{
    return node2_;
}

bool Link::IsConnected(Node *n1, Node *n2) const
{
    if ((*node1_ == *n1 || *node1_ == *n2) && (*node2_ == *n1 || *node2_ == *n2))
    {
        return true;
    }
    return false;
}

void Link::setId(int id) {
    id_ = id;
}

int Link::getId() const {
    return id_;
}
