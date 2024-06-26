// Luke Britton, 6 Jun 23, utils.cpp
#include <algorithm>
#include <random>
#include <utils.hpp>

// Generate a vector containing integers from 0 to x-1
std::vector<int> utils::til(int x){
    std::vector<int> l;
    for (int i=0; i<x; i++){
        l.push_back(i);
    };
    return l;
};

// Generate a vector containing integers from 0 to x-1 and shuffle them
std::vector<int> utils::til_shuffle(int x){
    std::vector<int> l = til(x);

    // Create a random number generator with a seed based on the current time
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);

    // Shuffle the elements using std::shuffle
    std::shuffle(l.begin(), l.end(), rng); 

    return l;
};


std::string utils::timePointAsString(const std::chrono::system_clock::time_point& tp) {
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::ctime(&t);
    ts.resize(ts.size()-1);
    return ts;
}

// converts character array
// to string and returns it
std::string utils::convertToString(const char* a, int size)
{
    int i;
    std::string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}

void utils::rmTrailingNulls(std::string &str) {
    size_t pos = str.find_last_not_of('\x00');
    if (pos != std::string::npos) {
        str.erase(pos + 1); // Erase from the position of the last non-null character to the end
    } else {
        // If the entire string consists of null characters, clear the string
        str.clear();
    }
}