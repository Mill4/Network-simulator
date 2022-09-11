#include "summary.hpp"
#include <string.h>

std::chrono::duration<double> Summary::GetTotalTime()
{
    return elapsed_time_secs_;
}

size_t Summary::GetNumOfSentPackets()
{
    return sent_packet_size_;
}

size_t Summary::GetNumReceivedPackets()
{
    return received_packet_size_;
}

std::string Summary::time_formatter(double secs)
{
    int milli_sec = static_cast<int>(secs * 1000.);

    int minute = milli_sec / (1000 * 60);
    milli_sec -= minute * (1000 * 60);
    std::string result;
    if (minute < 10)
    {
        result += "0" + std::to_string(minute);
    }
    else
    {
        result += std::to_string(minute);
    }
    result += ":";
    int second = milli_sec / 1000;
    milli_sec -= second * 1000;
    if (second < 10)
    {
        result += "0" + std::to_string(second);
    }
    else
    {
        result += std::to_string(second);
    }
    result += "." + std::to_string(milli_sec);

    return result;
}

std::string Summary::GetSummaryAsString()
{

    // auto average_time_in_seconds = elapsed_time_secs_.count() / received_packet_size_;
    auto average_time_in_seconds =
        received_packet_size_ == 0 ? 0
                                   : elapsed_time_secs_.count() / received_packet_size_;

    std::string total_time_string = time_formatter(elapsed_time_secs_.count());
    std::string average_time_string = time_formatter(average_time_in_seconds);
    std::cout << "total time is " << elapsed_time_secs_.count() << std::endl;
    std::cout << "average time is " << average_time_in_seconds << std::endl;

    summaryString = "======================================================================\n\n";
    summaryString += " Simulation info:\n\n";
    summaryString += back_ground_ + "\n";
    summaryString += " Summary: \n";
    summaryString += "  Total no of packets sent ************************** " +
                     std::to_string(sent_packet_size_) + "\n" +
                     "  Total no of packets received ********************** " +
                     std::to_string(received_packet_size_) + "\n";
    summaryString += "\n";
    summaryString += "  Total transmission time (mm:ss.mls) *************** " +
                     total_time_string + "\n" +
                     "  Average transmission time / packet (mm:ss.mls) **** " +
                     average_time_string + "\n";
    summaryString += "\n";
    for (auto i : routers_)
    {
        auto dropped = received_packet_size_ == sent_packet_size_ ? 0 : i->GetNumOfDroppedPackets();
        summaryString += "  Router " + i->GetName() + " dropped " +
                         std::to_string(dropped) + " packets\n";
    }
    summaryString += "\n";
    summaryString += "======================================================================\n";

    return summaryString;
}
