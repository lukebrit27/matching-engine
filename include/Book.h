#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <set>
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

public:
    //functions
    void match();
    void queue(Order order);
    void executeTrade();
    void dequeue();
    void submitOrder(unsigned int price, unsigned int quantity, std::string order_type, char side);
    void cancelOrder();
    std::vector<Order*> getTopOfBook(unsigned int level);
    bool compareOrders(const Order& ord1, const Order& ord2); //const ensures the Orders won't be changed when being passed by reference
    void printBids(unsigned int num);
};

#endif // BOOK_H