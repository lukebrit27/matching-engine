// Luke Britton, 24 Jul 23, Book.h
#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <set>
#include <vector>
#include "Order.h"

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
    //functions
    bool match(Order& new_order);
    void matchBook(Order& new_order, std::multiset<Order, compareOrders>& orderbook);
    void matchMarket(Order& new_order, std::vector<Order>& market_orders);
    void queue(Order& new_order);  

public:
    //functions
    void submitOrder(unsigned int price, unsigned int quantity, OrderType order_type, char side);
    void cancelOrder();
    std::vector<Order*> getTopOfBook(unsigned int level);
    void printBids(unsigned int num);
};

#endif // BOOK_H