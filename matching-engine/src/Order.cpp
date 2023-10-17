// Luke Britton, 11 Jul 23, Order.cpp
#include <string>
#include <map>
#include <stdexcept>
#include "Order.hpp"
#include "Logger.hpp"
#include "CurrentTime.hpp"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.


// Destructor
Order::~Order(){
    Logger::getLogger()->debug("ORDER OBJECT DELETED: " + getOrderIDString());    
}

Order& Order::operator=(const Order& other) {
  // Handle self-assignment
  // ensures no weird errors from compiler not wanting constants to be reassigned
  return *this;
}

void Order::validateOrder(){
    //validateOrderType();
    validateSide();
};

void Order::validateSide(){
    if (side != 'B' && side != 'S')
        throw std::invalid_argument("invalid side");
};

std::string Order::getInstrumentID() const{
    return instrument_id;
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

std::string Order::getOrderStatusString() const{
    switch (order_status){
        case OrderStatus::newo: return "newo";
        case OrderStatus::cancelled: return "cancelled";
        case OrderStatus::partiallyFilled: return "partiallyFilled";
        case OrderStatus::filled: return "filled";
        default: return "";
    };     
};

std::vector<std::string> Order::getOrderDetails() const{
    std::vector<std::string> details;

    details.push_back("{instrument_id : " + instrument_id + ", ");
    details.push_back("price : " + std::to_string(price) + ", ");
    details.push_back("quantity : " + std::to_string(quantity) + ", ");
    details.push_back("order_type : " + getOrderTypeString() + ", ");
    details.push_back("order_status : " + getOrderStatusString() + ", ");
    details.push_back("event_timestamp : " + CurrentTime::convertNanosecondsToTimestamp(event_timestamp) + ", ");
    details.push_back("leaves_quantity : " + std::to_string(leaves_quantity) + ", ");
    details.push_back("side : " + std::string(1, side) + ", ");
    details.push_back( "order_id : " + getOrderIDString() + "}");

    return details;
}; 

std::string Order::getOrderDetailsString() const{
    std::vector<std::string> details = getOrderDetails();

    std::string details_string = "";
    std::vector<std::string>::iterator it;
    for (it = details.begin(); it != details.end(); it++) {
        details_string += *it;
    };

    details_string += " \n";

    return details_string;
};

void Order::printOrderDetails() const{

    std::string details_string = getOrderDetailsString();
    Logger::getLogger()->info(details_string);
};

bool Order::fillOrder(unsigned int fill_quantity) const{
    fill_quantity = std::min(fill_quantity, leaves_quantity);

    updateLeavesQuantity(fill_quantity);
    updateOrderStatus();
    updateEventTimestamp();
    Logger::getLogger()->info("ORDER MATCH - order id: " + getOrderIDString() + ", fill quantity: " + std::to_string(fill_quantity) 
    + ", quantity: " + std::to_string(quantity) + ", leaves quantity: " + std::to_string(leaves_quantity));
    return order_status == OrderStatus::filled;
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

void Order::updateEventTimestamp() const{
    event_timestamp = CurrentTime::nanoseconds();
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