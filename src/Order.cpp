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


//instatiate valid order types
const std::string Order::valid_order_types[] = {"market", "limit"};

// Constructor: Initialize the Order object
Order::Order(unsigned int arg_price, unsigned int arg_quantity, std::string arg_order_type, char arg_side){

    price = arg_price;
    quantity = arg_quantity;
    order_type = arg_order_type;
    event_timestamp = std::chrono::high_resolution_clock::now();
    leaves_quantity = arg_quantity;
    side = arg_side;
    order_id = boost::uuids::random_generator()();

    validateOrder();
}

void Order::validateOrder(){
    validateOrderType();
};

void Order::validateOrderType(){
    //validate order_type
    //N.B. pointers not really necessary here 
    int* num_order_types = new int;
    *num_order_types = sizeof(valid_order_types);
    bool* is_valid = new bool(false);

    for (int i=0; i<(*num_order_types-1); i++){
        if (order_type == valid_order_types[i]){
            *is_valid = true;
            break;
        }
    };
    if (!*is_valid)
        throw std::invalid_argument("invalid order_type");

    delete num_order_types;
    delete is_valid;

}

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

std::string Order::getOrderType() const{
    return order_type;
}; 

std::vector<std::string> Order::getOrderDetails() const{
    std::vector<std::string> details;

    details.push_back("price | " + std::to_string(price) + "\n");
    details.push_back("quantity | " + std::to_string(quantity) + "\n");
    details.push_back("order_type | " + order_type + "\n");
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