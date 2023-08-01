// Luke Britton, 6 Jun 23, utils.cpp
#include <algorithm>
#include <random>
#include <utils.h>

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