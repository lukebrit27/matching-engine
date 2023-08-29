// Luke Britton, 6 Jun 23, utils.h
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <chrono>

namespace utils{
    std::vector<int> til(int x);
    std::vector<int> til_shuffle(int x);
    std::string timePointAsString(const std::chrono::system_clock::time_point& tp);
};

#endif //UTILS_H