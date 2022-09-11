#include "node.hpp"

std::string Node::GetName() const
{
    return name_;
}

std::string Node::GetIPAddress() const
{
    return IP_address_;
}

void Node::SetIPAddress(std::string &address)
{
    IP_address_ = address;
}

void Node::Connect(Node *&other)
{
    adjacents_.push_back(other);
}

bool Node::operator==(const Node &other) const
{
    if (this->GetName() == other.GetName() && this->GetIPAddress() == other.GetIPAddress())
    {
        return true;
    }
    return false;
}

std::vector<Node *> Node::GetAdjacents() const
{
    return adjacents_;
}

void Node::SendPacket(Packet p, Node *node_to_send)
{
    node_to_send->ReceivePacket(p);
}

void Node::SetRunningState(bool val)
{
    is_running_ = val;
}
