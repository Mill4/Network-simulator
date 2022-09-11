#ifndef PACKET_H
#define PACKET_H

#include <iostream>
#include <cstddef>
#include <ctime>
#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>
using random_bytes_engine = std::independent_bits_engine<
    std::default_random_engine, CHAR_BIT, unsigned char>;

const size_t id_length_bytes = 4;
const size_t packet_length_bytes = 4;

const size_t header_length_bytes = 16;

/**
 * @brief Packet class represents a single network packet that can be sent between nodes.
 * 
 * Packet is originally split from a bigger unit of data.
 * In our system we use Ethernet MTU as a default max packet sixe (1500 bytes)
 * 
 * The packet header has an ID (4 letter string - 4 bytes)
 * 
 */
class Packet
{
public:
    /**
     * @brief Construct a new Packet object
     * 
     * @param id_number Packet id - 4 bytes (4 letters)
     * @param length 4 bytes  ( MTU - header  --->  current max 1500-8-4-4 = 1484)
     * @param sequence_number 8 bytes
     */
    Packet(std::string id_number, uint32_t length, size_t sequence_number);

    /**
     * @brief Destroy the Packet object
     *
     */
    virtual ~Packet() {}

    /**
     * @brief Get the Id object
     *
     * @return const std::string
     */
    const std::string GetId() const;

    /**
     * @brief Get the Data array
     * 
     * @return std::vector<unsigned char> (random binary data at the moment)
     */
    std::vector<unsigned char> GetData() const;

    /**
     * @brief Get the Size object
     *
     * @return std::size_t
     */
    std::size_t GetSize() const;

    /**
     * @brief Get the Sequence Number of the packet
     * 
     * The packets should come in order {1, 2, 3, 4....}
     * 
     * @return size_t 
     */
    size_t GetSequenceNumber() const;

    /**
     * @brief Get the Unix Time Stamp of the packet
     * 
     * @return std::time_t Seconds since 01-Jan-1970
     */
    std::time_t GetUnixTimeStamp() const;

    /**
     * @brief Get the Header Length of the packet of this system
     * 
     * @return size_t 
     */
    static size_t GetHeaderLength();

private:
    std::string id_;
    size_t data_length_;
    size_t sequence_number_;
    size_t size_;
    std::time_t time_stamp_;
    std::vector<unsigned char> data_;

    static size_t HeaderLength;
};

#endif // PACKET_H