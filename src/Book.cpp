#include "Book.h"
#include <iostream>


// Definition of the comparison function for the struct compareOrders
bool Book::compareOrders::operator()(const Order& ord1, const Order& ord2) const{

    std::cout << "Order1 " << ord1.getOrderIDString() << ": " << ord1.getPrice() << " > " << "Order2 " << ord2.getOrderIDString() << ": " << ord2.getPrice() << " = " << (ord1.getPrice() > ord2.getPrice()) << std::endl;   
    std::cout << "############################################" << std::endl;       
    // Return true if ord1 should be placed before ord2 in the multiset
    // Return false otherwise
    if (ord1.getSide() == 'B' && ord2.getSide() == 'B') {
        return ord1.getPrice() > ord2.getPrice(); // Sort bids by highest price first
    } else if (ord1.getSide() == 'S' && ord2.getSide() == 'S') {
        return ord1.getPrice() < ord2.getPrice(); // Sort asks by lowest price first
    } else {
        // Orders with different sides should not be compared
        return false;
    }             
};

void Book::submitOrder(unsigned int price, unsigned int quantity, std::string order_type, char side){
    Order order = Order(price, quantity, order_type, side);
    queue(order);
    //match();
};

void Book::queue(Order order){
    char side = order.getSide();

    if (side == 'B') {
        bids.insert(order);  // add to bids (sorted by descending price on insert)
    } 
    else if (side == 'S') {
        asks.insert(order); // add to asks (sorted by ascending price on insert)
    }      
};

void Book::match(){
    //if 
};

void Book::executeTrade(){

};

void Book::dequeue(){

};

void Book::cancelOrder(){

};

// std::vector<Order*> Book::getTopOfBook(int level){

// };

bool Book::compareOrders(const Order& ord1, const Order& ord2){
    // if (ord1.side == 'B' && ord2.side == 'B') {
    //     return ord1.price > ord2.price; // Sort bids by highest price first
    // } else if (ord1.side == 'S' && ord2.side == 'S') {
    //     return ord1.price < ord2.price; // Sort asks by lowest price first
    // } else {
    //     // Orders with different sides should not be compared
    //     return false;
    // }    
};

void Book::printBids(unsigned int num){
    auto it = bids.begin();
    for (int i = 0; i < num && it != bids.end(); ++i, ++it) {
        it->printOrderDetails();
    };
};