#ifndef CURRENT_TIME_H
#define CURRENT_TIME_H

#include <chrono>
#include <cstdint>
#include <sstream>
#include <iomanip>

namespace CurrentTime{
    inline uint64_t milliseconds() 
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>
                (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    inline uint64_t microseconds() 
    {
        return std::chrono::duration_cast<std::chrono::microseconds>
                (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }

    inline uint64_t nanoseconds()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>
                (std::chrono::high_resolution_clock::now().time_since_epoch()).count();
    }  

    inline std::string convertNanosecondsToTimestamp(uint64_t ns)
    {
        std::chrono::high_resolution_clock::time_point tp{std::chrono::nanoseconds(ns)};
        std::time_t tt = std::chrono::high_resolution_clock::to_time_t(tp);
        std::tm* tm_utc = std::gmtime(&tt);

        std::stringstream ss;
        ss << std::put_time(tm_utc, "%Y-%m-%d %H:%M:%S") << '.' << std::setw(9) << std::setfill('0') << (ns % 1000000000) << " UTC";
        
        return ss.str();
    }    
}

#endif  /* CURRENT_TIME_H */