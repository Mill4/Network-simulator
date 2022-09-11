#include "endhost.hpp"

void EndHost::ReceivePacket(Packet p)
{
    //std::cout << "Packet received at EndHost: " << GetName() << " Sequence number is: " << p.GetSequenceNumber() << std::endl;
    //terminal->consoleLog(); //("Packet received at EndHost: " + GetName() + "\n"); // + " Seqnum: " + std::to_string(p.GetSequenceNumber()) + "\n");
    received_packets_.push_back(p);
}

size_t EndHost::GetNumOfReceivedPackets() const
{
    return received_packets_.size();
}
