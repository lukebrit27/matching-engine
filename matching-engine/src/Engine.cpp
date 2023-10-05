// Luke Britton, 18 Sep 23, Engine.cpp
#include <stdexcept>
#include <utility>
#include "Engine.hpp"
#include "Logger.hpp"

void Engine::start(std::vector<std::string> instruments){

    std::vector<std::string>::iterator instr_it;

    for (instr_it = instruments.begin(); instr_it != instruments.end(); ++instr_it) {

        Logger::getLogger()->info("Creating order book for instrument " + *instr_it);
        try{
            addBook(*instr_it);
        }
        catch(const std::invalid_argument& e) {
            std::string msg = e.what();
            Logger::getLogger()->warn("Invalid instrument: " + msg);
        }         
        catch(const std::exception& e) {
            std::string msg = e.what();
            Logger::getLogger()->error("Failed to add book for instrument " + *instr_it + ": " + msg);
        } 
        catch(...){
            Logger::getLogger()->error("Unknown error adding book for instrument " + *instr_it); 
        }
    }
}

void Engine::addBook(std::string instrument_id){

    if (books.find(instrument_id) != books.end()) {
        throw std::invalid_argument("Book for instrument " + instrument_id + " already exists!");
    };

    books.insert(std::make_pair(instrument_id, Book(instrument_id)));
}

bool Engine::submitOrder(std::string instrument_id, unsigned int price, unsigned int quantity, std::string order_type, char side){
    auto book_it = books.find(instrument_id);
    bool success = false;
    
    if (book_it != books.end()) {
        // book found, TO-DO try submit an order, log errors if fails
        // TO-DO add logging
        Book& book = book_it->second;
        try{
            book.submitOrder(price, quantity, order_type, side);
            success = true;
        }
        catch(...){
            std::string log_str = "{instrument_id : " + instrument_id + ", price : " + std::to_string(price) +
            ", quantity : " + std::to_string(quantity) + ", order_type : " + order_type +
            ", side : " + std::string(1, side) + "}";          
            Logger::getLogger()->error("Failed to submit order:  " + log_str); 
        } 
    } 
    else {
        // book not found
        Logger::getLogger()->error("Instrument not found: " + instrument_id);
        success = false;
    }  

    return success;
};