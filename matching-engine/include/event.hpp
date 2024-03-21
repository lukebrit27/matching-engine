// Luke Britton, 15 Feb 24, event.hpp

#ifndef EVENT_H
#define EVENT_H
#define EVENT_BUFFER_SIZE 200
#include <string>
#include <unordered_map>
#include <variant>
#include <fstream>
#include "ThreadPool.hpp"

namespace event{

    class Publisher{
        
        private:
            static constexpr int TYPE = 0, HANDLE = 1; // readibility // defined at compile time
            using Conn = std::variant<std::string, std::shared_ptr<std::ofstream>>; // string or file stream pointer
            std::unordered_map<std::string, std::array<Conn, 2>> connections;
            ThreadPool thread_pool;

            // functions
            void validateAddr(std::string& addr);
            void validateType(std::string& type);
            
        public:
            // constructor
            Publisher();
            // functions
            void addListener(std::string& addr, std::string& type);
            bool listenerExists(std::string& addr);
            std::shared_ptr<std::ofstream> connectFile(std::string& addr, std::string& type);
            // void connectIP(std::string& addr, std::string& type);
            void publish(std::array<char, EVENT_BUFFER_SIZE>& buf);
            static std::shared_ptr<Publisher> getPublisher();         
    };

}
#endif // EVENT_H