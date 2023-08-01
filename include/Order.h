//Luke Britton, 11 Jul 23, Order.h
#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <boost/uuid/uuid.hpp>

enum class OrderType {limit, market};
enum class OrderStatus {newo, cancelled, partiallyFilled, filled};

class Order{
private:
    //variables
    std::chrono::time_point<std::chrono::high_resolution_clock> event_timestamp;
    unsigned int price;
    unsigned int quantity;
    mutable unsigned int leaves_quantity;
    char side;
    boost::uuids::uuid order_id;  
    OrderType order_type;  
    mutable OrderStatus order_status; 
    //functions
    void updateLeavesQuantity(unsigned int fill_quantity) const;
    void updateOrderStatus() const;
public:
    //constructor
    Order(unsigned int arg_price, unsigned int arg_quantity, OrderType arg_order_type, char arg_side);
    //variables
    //functions
    void validateOrder();
    void validateSide();
    unsigned int getPrice() const;
    unsigned int getQuantity() const;
    unsigned int getLeavesQuantity() const;
    char getSide() const;
    boost::uuids::uuid getOrderID() const;
    std::string getOrderIDString() const;
    OrderType getOrderType() const;   
    std::string getOrderTypeString() const;  
    OrderStatus getOrderStatus() const; 
    std::vector<std::string> getOrderDetails() const;
    void printOrderDetails() const;  
    bool fillOrder(unsigned int fill_quantity) const;
    bool checkMatch(Order& order) const;
};

#endif //ORDER_H