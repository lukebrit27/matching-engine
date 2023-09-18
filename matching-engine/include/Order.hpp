//Luke Britton, 11 Jul 23, Order.h
#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <map>
#include <boost/uuid/uuid.hpp>

enum class OrderType {limit, market};
enum class OrderStatus {newo, cancelled, partiallyFilled, filled};

class Order{
protected:
    //variables
    const std::string instrument_id;
    mutable uint64_t event_timestamp;
    const unsigned int price;
    const unsigned int quantity;
    mutable unsigned int leaves_quantity;
    const char side;
    const boost::uuids::uuid order_id;  
    const OrderType order_type;  
    mutable OrderStatus order_status; 
    //functions
    void updateLeavesQuantity(unsigned int fill_quantity) const;
    void updateOrderStatus() const;
    void updateEventTimestamp() const;
public:
    //constructor
    Order(std::string arg_instrument_id, unsigned int arg_price, unsigned int arg_quantity, OrderType arg_order_type, char arg_side);
    //destructor
    ~Order();
    //variables
    //operators
    Order& operator=(const Order& other);
    //functions
    void validateOrder();
    void validateSide();
    std::string getInstrumentID() const;
    unsigned int getPrice() const;
    unsigned int getQuantity() const;
    unsigned int getLeavesQuantity() const;
    char getSide() const;
    boost::uuids::uuid getOrderID() const;
    std::string getOrderIDString() const;
    OrderType getOrderType() const;   
    std::string getOrderTypeString() const;  
    OrderStatus getOrderStatus() const; 
    std::string getOrderStatusString() const;
    std::vector<std::string> getOrderDetails() const;
    std::string getOrderDetailsString() const;
    void printOrderDetails() const;  
    bool fillOrder(unsigned int fill_quantity) const;
    bool checkMatch(Order& order) const;
};

#endif //ORDER_H