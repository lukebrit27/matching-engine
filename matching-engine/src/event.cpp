// Luke Britton, 21 Feb 24, event.cpp
#include <stdexcept>
#include <memory>
#include "event.hpp"

using namespace event;

// constructor
Publisher::Publisher() : thread_pool(1) {};

void Publisher::validateAddr(std::string& addr){
    auto it = connections.find(addr);
    if (it != connections.end())
        throw std::invalid_argument("Connection " + addr + " already exists!");    
};

void Publisher::validateType(std::string& type){
    if (type == "file")
        return;
    else
        throw std::invalid_argument("Invalid type " + type + ". Options are 'file'");
};

std::shared_ptr<std::ofstream> Publisher::connectFile(std::string& addr, std::string& type){
    std::shared_ptr<std::ofstream> file = std::make_shared<std::ofstream>(addr);
    if (!file->is_open())
        throw std::runtime_error("Failed to open file " + addr);
    return file;
};

void Publisher::addListener(std::string& addr, std::string& type){
    validateAddr(addr);
    validateType(type);
    if (type == "file"){
        connections[addr][HANDLE] = connectFile(addr, type);
        connections[addr][TYPE] = type;        
    }
};

bool Publisher::listenerExists(std::string& addr){
    bool exists = false;
    auto it = connections.find(addr);
    if (it != connections.end())
        exists = true;    
    return exists;
};

void Publisher::publish(std::array<char, EVENT_BUFFER_SIZE>& buf){
    // loop through connections and write
    // *connections[addr][HANDLE] << buf << endl
    // run on separate thread pool
    for (const auto& conn : connections) {
        thread_pool.enqueue([buf, conn] {
            const auto& handle = conn.second[HANDLE];
        // if it is a file then write to it
        if (std::holds_alternative<std::shared_ptr<std::ofstream>>(handle)) {
            auto fileStreamPtr = std::get<std::shared_ptr<std::ofstream>>(handle); // get desired type from variant
            *fileStreamPtr << '\n'; // ensures data is written on a new line
            fileStreamPtr->write(buf.data(), buf.size());
        }
        });
    };
};

// shared pointer to single instance of a Publisher
std::shared_ptr<Publisher> Publisher::getPublisher() {
    static std::shared_ptr<Publisher> instance = std::make_shared<Publisher>();
    return instance;
};