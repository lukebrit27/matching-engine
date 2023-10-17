// Luke Britton, 24 Jul 23, Book.h
#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <set>
#include <vector>
#include <variant>
#include <memory>
#include "Order.hpp"
#include "Logger.hpp"

class Book{
private:
    //structs
    struct compareOrders{
        bool operator()(const Order& ord1, const Order& ord2) const;
    };
    //variables
    std::multiset<Order, compareOrders> bids;
    std::multiset<Order, compareOrders> asks;
    std::vector<Order> market_bids;
    std::vector<Order> market_asks;
    const std::string instrument_id;
    //functions
    bool match(Order& new_order);
    void matchBook(Order& new_order, std::multiset<Order, compareOrders>& orderbook);
    void matchMarket(Order& new_order, std::vector<Order>& market_orders);
    void queue(Order& new_order);

public:
    // constructor
    Book(std::string arg_instrument_id);
    // template functions 
    // need to be instatiated in header file so source files that include this 
    // header can see the implementation to correctly compile func with correct types
    // for their function calls
    template<typename T>
    requires std::is_same_v<T, OrderType> || std::is_same_v<T, std::string>
    void submitOrder(unsigned int price, unsigned int quantity, T order_type, char side){
        std::shared_ptr<Order> order = std::make_shared<Order>(instrument_id, price, quantity, order_type, side);
        Logger::getLogger()->info("NEW ORDER SUBMITTED - " + order->getOrderDetailsString());
        bool filled = match(*order);
        if (!filled)
            queue(*order);
        else
            Logger::getLogger()->info("NEW ORDER FILLED - order id: " + order->getOrderIDString());
    }; 
    // functions   
    void cancelOrder();
    std::string getInstrumentID() const;
    std::vector<Order*> getTopOfBook(unsigned int level);
};

#endif // BOOK_H