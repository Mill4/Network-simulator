#ifndef SUMMARY_H
#define SUMMARY_H
#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>
#include "link.hpp"
#include "router.hpp"

/**
 * @brief Summary class to display the summary data at the end of
 * simulation.
 *
 */
class Summary
{
public:
    /**
     * @brief Construct a new Summary object
     *
     * @param time_secs
     * @param sent_packet_size
     * @param received_packet_size
     * @param routers
     */
    Summary(std::string background_data, std::chrono::duration<double> time_secs, size_t sent_packet_size,
            size_t received_packet_size, std::vector<Router *> routers)
        : back_ground_(background_data), elapsed_time_secs_(time_secs), sent_packet_size_(sent_packet_size),
          received_packet_size_(received_packet_size), routers_(routers) {}

    /**
     * @brief Destroy the Summary object
     *
     */
    ~Summary() {}

    /**
     * @brief
     *
     * @return std::string
     */
    std::string GetSummaryAsString();

    /**
     * @brief Get the Time Seconds object
     *
     * @return std::chrono::duration<double>
     */
    std::chrono::duration<double> GetTotalTime();

    /**
     * @brief Get the Sent Packet Size object
     *
     * @return size_t
     */
    size_t GetNumOfSentPackets();

    /**
     * @brief Get the Received Packet Size object
     *
     * @return size_t
     */
    size_t GetNumReceivedPackets();

    /**
     * @brief
     *
     * @return std::string&
     */
    std::string time_formatter(double time_secs);

private:
    std::string back_ground_;
    std::chrono::duration<double> elapsed_time_secs_;
    size_t sent_packet_size_;
    size_t received_packet_size_;
    std::vector<Router *> routers_;
    std::string summaryString;
};

#endif