#ifndef UTILS_H
#define UTILS_H

#include <vector>

class utils{
public:
    static std::vector<int> til(int x);
    static std::vector<int> til_shuffle(int x);
    static std::string timePointAsString(const std::chrono::system_clock::time_point& tp);
};

#endif //UTILS_H