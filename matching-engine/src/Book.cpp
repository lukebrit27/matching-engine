// Luke Britton, 24 Jul 23, Book.cpp
#include <type_traits>
#include "Book.hpp"
#include "Logger.hpp"
#include "event.hpp"
#include "encode.hpp"
#include <sbepp-gen/engine_schemas/messages/trade_schema.hpp>

Book::Book(std::string arg_instrument_id) : instrument_id(arg_instrument_id){};

// Definition of the comparison function for the struct compareOrders
bool Book::compareOrders::operator()(const Order& ord1, const Order& ord2) const{

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

void Book::queue(Order& new_order){
    char side = new_order.getSide();
    OrderType order_type = new_order.getOrderType();

    switch (order_type){
        case OrderType::limit:{
            if (side == 'B') {
                bids.insert(new_order);  // add to bids (sorted by descending price on insert)
            } 
            else if (side == 'S') {
                asks.insert(new_order); // add to asks (sorted by ascending price on insert)
            }
            break;
        }
        case OrderType::market:{
            if (side == 'B') {
                market_bids.push_back(new_order);  // add to market bids
            } 
            else if (side == 'S') {
                market_asks.push_back(new_order); // add to market asks
            }
            break;
        }        
    } 
};

bool Book::match(Order& new_order){
    /*
    if new order is a market ask then only need to check the bids
        cycle through bids until quantity is filled or reach end of bids 
    if new order is a market bid then only need to check the asks
        cycle through asks until quantity is filled or reach end of asks     
    if new order is a limit ask then only need bids >= than order price (filling largest bid first)
    if new order is a limit bid then only need asks <= than order price (filling smallest ask first)

    TO-DO write the matchMarket() function next
    */
    char side = new_order.getSide();
    OrderType order_type = new_order.getOrderType();

    switch (order_type){
        case OrderType::limit:{
            if (side == 'B') {
                matchMarket(new_order, market_asks);
                matchBook(new_order, asks);
            } 
            else if (side == 'S') {
                matchMarket(new_order, market_bids);
                matchBook(new_order, bids);
            }
            break;
        }
        case OrderType::market:{
            if (side == 'B') {
                matchBook(new_order, asks);
            } 
            else if (side == 'S') {
                matchBook(new_order, bids);
            }
            break;
        }        
    };

    // return true if the order is filled
    return new_order.getOrderStatus() == OrderStatus::filled;    
};

void Book::matchBook(Order& new_order, std::multiset<Order, compareOrders>& orderbook){

    // make sure order isn't already filled
    if(new_order.getOrderStatus() == OrderStatus::filled)
        return;

    bool is_match = true;
    std::multiset<Order, compareOrders>::iterator book_it = orderbook.begin();
    while(is_match && (new_order.getOrderStatus() != OrderStatus::filled) && book_it != orderbook.end()){
        Logger::getLogger()->debug("DEBUGGING LOOP: " + book_it->getOrderDetailsString());
        
        is_match = book_it->checkMatch(new_order);
        // if orders match fill the orders
        if(is_match){
            const unsigned int fill_quantity = book_it->fillOrder(new_order.getLeavesQuantity());
            book_it->publishEvent();
            new_order.fillOrder(fill_quantity);
            new_order.publishEvent();
            publishTradeEvent(&new_order, &(*book_it), fill_quantity);
        };

        // if current order filled, remove from orderbook
        if(book_it->getOrderStatus() == OrderStatus::filled){
            Logger::getLogger()->info("ORDER FILLED - Removing order id: " + book_it->getOrderIDString() + " from book: " + instrument_id);
            book_it = orderbook.erase(book_it);
        }
        else
            ++book_it;
    };    
};

void Book::matchMarket(Order& new_order, std::vector<Order>& market_orders){
    
    // make sure order isn't already filled
    // market orders can't match with other market orders
    if(new_order.getOrderStatus() == OrderStatus::filled || new_order.getOrderType() == OrderType::market)
        return;

    bool is_match = true;
    std::vector<Order>::iterator mkt_it = market_orders.begin();
    while(is_match && (new_order.getOrderStatus() != OrderStatus::filled) && mkt_it != market_orders.end()){
        
        is_match = mkt_it->checkMatch(new_order);
        // if orders match fill the orders
        if(is_match){
            const unsigned int fill_quantity = mkt_it->fillOrder(new_order.getLeavesQuantity());
            mkt_it->publishEvent();
            new_order.fillOrder(fill_quantity);
            new_order.publishEvent();
            publishTradeEvent(&new_order, &(*mkt_it), fill_quantity);
        };

        // if current order filled, remove from orderbook
        if(mkt_it->getOrderStatus() == OrderStatus::filled){
            Logger::getLogger()->info("ORDER FILLED - Removing order id: " + mkt_it->getOrderIDString() + " from book: " + instrument_id);
            mkt_it = market_orders.erase(mkt_it);
        }
        else
            ++mkt_it;
    };            

    
};

void Book::cancelOrder(){

};

std::string Book::getInstrumentID() const{
    return instrument_id;
};

Order Book::getBestBid(){
    if (!bids.empty()) {
        return *bids.begin();
    }
    else{
        throw std::runtime_error("No bids present in the book");
    }
};

Order Book::getBestAsk(){
    if (!asks.empty()) {
        return *asks.begin();
    }
    else{
        throw std::runtime_error("No asks present in the book");
    }
};

// o1 = new order that came in an matched an order on the book
// o2 = order that was already sitting on the book
void Book::publishTradeEvent(const Order* o1, const Order* o2, const unsigned int& fill_quantity){
    auto buf = encode::trade(o1, o2, fill_quantity);
    event::Publisher::getPublisher()->publish(buf);
};
