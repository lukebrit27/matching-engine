// Luke Britton, 18 Sep 23, Engine.cpp

#ifndef ENGINE_H
#define ENGINE_H
#include <string>
#include <vector>
#include <unordered_map>
#include "Book.hpp"

class Engine{
private:
    //variables
    std::unordered_map<std::string, Book> books;
public:
    //functions
    void start(std::vector<std::string> instruments);
    void addBook(std::string instrument_id);
    bool submitOrder(std::string instrument_id, unsigned int price, unsigned int quantity, std::string order_type, char side);
    Book& getBook(std::string instrument_id);
    bool addEventListener(std::string addr, std::string type);
};
#endif // ENGINE_H