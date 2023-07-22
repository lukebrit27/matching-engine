//Luke Britton, 11 Jul 23, Order.h
#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <boost/uuid/uuid.hpp>

class Order{
private:
    //variables
    std::chrono::time_point<std::chrono::high_resolution_clock> event_timestamp;
    unsigned int price;
    unsigned int quantity;
    unsigned int leaves_quantity;
    char side;
    boost::uuids::uuid order_id;
    std::string order_type;    
public:
    //constructor
    Order(unsigned int arg_price, unsigned int arg_quantity, std::string arg_order_type, char arg_side);
    //variables
    static const std::string valid_order_types[];
    //functions
    void validateOrder();
    void validateOrderType();
    unsigned int getPrice() const;
    unsigned int getQuantity() const;
    unsigned int getLeavesQuantity() const;
    char getSide() const;
    boost::uuids::uuid getOrderID() const;
    std::string getOrderIDString() const;
    std::string getOrderType() const;   
    std::vector<std::string> getOrderDetails() const;
    void printOrderDetails() const;  
};

#endif //ORDER_H