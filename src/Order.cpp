// Luke Britton, 11 Jul 23, Order.cpp
#include <string>
#include <map>
#include <iostream>
#include <stdexcept>
#include "Order.h"
#include <utils.h>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.


// Constructor: Initialize the Order object
Order::Order(unsigned int arg_price, unsigned int arg_quantity, OrderType arg_order_type, char arg_side){

    price = arg_price;
    quantity = arg_quantity;
    order_type = arg_order_type;
    event_timestamp = std::chrono::high_resolution_clock::now();
    leaves_quantity = arg_quantity;
    side = arg_side;
    order_id = boost::uuids::random_generator()();
    order_status = OrderStatus::newo;

    validateOrder();
}

void Order::validateOrder(){
    //validateOrderType();
    validateSide();
};

void Order::validateSide(){
    if (side != 'B' && side != 'S')
        throw std::invalid_argument("invalid side");
};

unsigned int Order::getPrice() const{
    return price;
};
unsigned int Order::getQuantity() const{
    return quantity;
};
unsigned int Order::getLeavesQuantity() const{
    return leaves_quantity;
};
char Order::getSide() const{
    return side;
};
boost::uuids::uuid Order::getOrderID() const{
    return order_id;
};

std::string Order::getOrderIDString() const{
    return boost::uuids::to_string(order_id);
};

OrderType Order::getOrderType() const{
    return order_type;
}; 

std::string Order::getOrderTypeString() const{
    switch (order_type){
        case OrderType::limit: return "limit";
        case OrderType::market: return "market";
        default: return "";
    };    
};

OrderStatus Order::getOrderStatus() const{
    return order_status;
}; 

std::vector<std::string> Order::getOrderDetails() const{
    std::vector<std::string> details;

    details.push_back("price | " + std::to_string(price) + "\n");
    details.push_back("quantity | " + std::to_string(quantity) + "\n");
    details.push_back("order_type | " + getOrderTypeString() + "\n");
    details.push_back("event_timestamp | " + utils::timePointAsString(event_timestamp) + "\n");
    details.push_back("leaves_quantity | " + std::to_string(leaves_quantity) + "\n");
    details.push_back("side | " + std::to_string(side) + "\n");
    details.push_back( "order_id | " + getOrderIDString() + "\n");

    return details;
}; 


void Order::printOrderDetails() const{
    std::vector<std::string> details = getOrderDetails();

    std::vector<std::string>::iterator it;
    for (it = details.begin(); it != details.end(); it++) {
        std::cout << *it << std::endl;
    }

    std::cout << "" << std::endl;
};

bool Order::fillOrder(unsigned int fill_quantity) const{
    fill_quantity = std::min(fill_quantity, leaves_quantity);

    updateLeavesQuantity(fill_quantity);
    updateOrderStatus();
};

void Order::updateLeavesQuantity(unsigned int fill_quantity) const{
    leaves_quantity = leaves_quantity - std::min(fill_quantity, leaves_quantity);
};

void Order::updateOrderStatus() const{
    switch (order_status){
        case OrderStatus::newo:{
            if (leaves_quantity == 0)
                order_status = OrderStatus::filled;
            else if ((leaves_quantity > 0) && leaves_quantity < quantity)
                order_status = OrderStatus::partiallyFilled;
            else if (leaves_quantity > quantity)
                throw std::range_error("leaves quantity is greater than the quantity");

        };
        case OrderStatus::partiallyFilled:{
            if (leaves_quantity == 0)
                order_status = OrderStatus::filled;
            else if (leaves_quantity > quantity)
                throw std::range_error("leaves quantity is greater than the quantity");
        }
    };   
};

bool Order::checkMatch(Order& order) const{
    if (order_type == OrderType::market || order.getOrderType() == OrderType::market)
        return side != order.getSide() && order_type != order.getOrderType(); // handles case where at least 1 market order
    else if (side == 'B' && order.getSide() == 'S') 
        return price >= order.getPrice();
    else if (side == 'S' && order.getSide() == 'B')
        return price <= order.getPrice(); // Sort asks by lowest price first
    else
        return false;           
};    