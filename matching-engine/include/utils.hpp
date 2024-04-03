// Luke Britton, 6 Jun 23, utils.h
#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <chrono>
#include <sbepp/sbepp.hpp>

namespace utils{
    std::vector<int> til(int x);
    std::vector<int> til_shuffle(int x);
    std::string timePointAsString(const std::chrono::system_clock::time_point& tp);
    std::string convertToString(const char* a, int size);
    
    template<typename T, typename Tag>
    void fillField(T& field, const std::string& inputString){
        unsigned int length = std::min(sbepp::type_traits<Tag>::length(), inputString.length());
        if (length == 0){
            return;
        };
        // Copy the string content to the field
        for (int i = 0; i < length; ++i) {
            field[i] = inputString[i];
        };
    }
};

#endif //UTILS_H