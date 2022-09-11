#include "router.hpp"

std::queue<Packet> &Router::GetPacketQueue()
{
    return buffer_;
}

unsigned int Router::GetLostPackets()
{
    return lost_packets_;
}

int Router::GetMaxBufferSize() const
{
    return max_buffer_;
}

unsigned int Router::GetNumOfDroppedPackets() const
{
    return lost_packets_;
}

void Router::ReceivePacket(Packet p)
{
    const std::lock_guard<std::mutex> lock(buffer_lock_);
    if (buffer_.size() >= max_buffer_)
    {
        terminal->consoleLog("Router " + GetName() + " dropped packet Seqnum: " + std::to_string(p.GetSequenceNumber()));
        lost_packets_++;
    }
    else
    {
        buffer_.push(p);
    }
}

void Router::PacketFlowThread(Node *next_node, size_t speed)
{
    auto trans_speed = speed * 1000; // Kbps
    //std::cout << "Packetflowthread started " << GetName() << std::endl;
    terminal = terminal->getInstance();
    while (is_running_ || buffer_.size() > 0)
    {
        if (buffer_.size() > 0)
        {
            if (i >= 10)
            {
                terminal->consoleLog("Router " + GetName() + " transfering packet to " + next_node->GetName() + "\n");
                i = 0;
            }
            buffer_lock_.lock();
            auto packet = buffer_.front();
            buffer_.pop();
            buffer_lock_.unlock();

            auto size = packet.GetSize();
            double delay = (size * 8.0 / trans_speed) * 1000.0; // to Milliseconds

            // Wait ... simulate the time to transmit the packet
            std::this_thread::sleep_for(std::chrono::milliseconds((int)delay));

            //terminal->consoleLogTansfer();

            // Send packet
            SendPacket(packet, next_node);
            i++;
        }
    }
}
