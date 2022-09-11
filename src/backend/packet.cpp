#include "packet.hpp"

Packet::Packet(std::string id_number, uint32_t length, size_t sequence_number)
    : id_(id_number), data_length_(length), sequence_number_(sequence_number), time_stamp_(std::time(nullptr))
{
    size_ = id_length_bytes + packet_length_bytes + length;

    random_bytes_engine rbe;
    std::vector<unsigned char> data(data_length_);
    data_ = data;
    std::generate(begin(data_), end(data_), std::ref(rbe));
}

const std::string Packet::GetId() const
{
    return id_;
}

std::vector<unsigned char> Packet::GetData() const
{
    return data_;
}

std::size_t Packet::GetSize() const
{
    return size_;
}

size_t Packet::GetSequenceNumber() const
{
    return sequence_number_;
}

std::time_t Packet::GetUnixTimeStamp() const
{
    return time_stamp_;
}

size_t Packet::GetHeaderLength()
{
    return header_length_bytes;
}

size_t Packet::HeaderLength = header_length_bytes;