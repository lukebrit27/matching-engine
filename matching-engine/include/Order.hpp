//Luke Britton, 11 Jul 23, Order.h
#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <map>
#include "CurrentTime.hpp"
#include "Logger.hpp"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <sbepp-gen/engine_schemas/messages/order_schema.hpp> // sbe code

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
    const std::string trader;
    //functions
    void updateLeavesQuantity(unsigned int fill_quantity) const;
    void updateOrderStatus() const;
    void updateEventTimestamp() const;
public:
    //constructor  
    template<typename T>
    requires std::is_same_v<T, OrderType> || std::is_same_v<T, std::string>
    Order(std::string arg_instrument_id, unsigned int arg_price, unsigned int arg_quantity, T arg_order_type, char arg_side, std::string arg_trader) :
        instrument_id(arg_instrument_id), price(arg_price), quantity(arg_quantity), order_type(castOrderTypeString(arg_order_type)), side(arg_side), order_id(boost::uuids::random_generator()()), trader(arg_trader) {

        event_timestamp = CurrentTime::nanoseconds();
        leaves_quantity = arg_quantity;
        order_status = OrderStatus::newo;

        validateOrder();

        Logger::getLogger()->debug("NEW ORDER OBJECT CREATED: " + getOrderIDString());
    };
    //destructor
    ~Order();
    //variables
    //operators
    Order& operator=(const Order& other);
    //template functions
    template<typename T>
    requires std::is_same_v<T, OrderType> || std::is_same_v<T, std::string> 
    OrderType castOrderTypeString(T& order_type_str) const {   
        if constexpr (std::is_same_v<T, std::string>) {
            if (order_type_str == "limit")
                return OrderType::limit;
            else if (order_type_str == "market")
                return OrderType::market;
            else
                throw std::invalid_argument("Invalid order_type: " + order_type_str);
        }
        else
            return order_type_str;
    }   
    //functions
    void validateOrder();
    void validateSide();
    uint64_t getEventTimestamp() const;
    std::string getInstrumentID() const;
    unsigned int getPrice() const;
    unsigned int getQuantity() const;
    unsigned int getLeavesQuantity() const;
    char getSide() const;
    std::string getTrader() const;
    boost::uuids::uuid getOrderID() const;
    std::string getOrderIDString() const;
    OrderType getOrderType() const;   
    std::string getOrderTypeString() const;
    OrderStatus getOrderStatus() const; 
    std::string getOrderStatusString() const;
    std::vector<std::string> getOrderDetails() const;
    std::string getOrderDetailsString() const;
    engine_schemas::types::Side getSBESide() const;
    engine_schemas::types::OrderStatus getSBEOrderStatus() const;
    engine_schemas::types::OrderType getSBEOrderType() const;    
    void printOrderDetails() const;  
    unsigned int fillOrder(unsigned int fill_quantity) const;
    bool checkMatch(Order& order) const;
    void publishEvent() const;
    bool isBuy() const;
};

#endif //ORDER_H