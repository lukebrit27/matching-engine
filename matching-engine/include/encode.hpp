// Luke Britton, 2 Feb 24, encode.hpp
#ifndef ENCODE_H
#define ENCODE_H
#define EVENT_BUFFER_SIZE 200
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include "Order.hpp"
#include "utils.hpp"
#include "CurrentTime.hpp"
#include <sbepp/sbepp.hpp>
#include <sbepp-gen/engine_schemas/messages/order_schema.hpp> // sbe code
#include <sbepp-gen/engine_schemas/messages/trade_schema.hpp> // sbe code

namespace encode{
    inline std::array<char, EVENT_BUFFER_SIZE> order(const Order* o){

        std::array<char, EVENT_BUFFER_SIZE> buf{};
        auto m = sbepp::make_view<engine_schemas::messages::order_schema>(buf.data(), buf.size());   
        sbepp::fill_message_header(m);

        m.eventTimestamp(o->getEventTimestamp());
        m.price(o->getPrice());
        m.quantity(o->getQuantity());
        m.leavesQuantity(o->getLeavesQuantity());
        m.side(o->getSBESide());
        m.orderType(o->getSBEOrderType());
        m.orderStatus(o->getSBEOrderStatus());
        m.messageType('O');

        auto oid = m.orderID();
        utils::fillField<engine_schemas::types::STRING36<char>, ::engine_schemas::schema::types::STRING36> (oid, o->getOrderIDString());

        auto sym = m.instrumentID();
        utils::fillField<engine_schemas::types::STRING4<char>, ::engine_schemas::schema::types::STRING4> (sym, o->getInstrumentID());

        auto trader = m.trader();
        utils::fillField<engine_schemas::types::STRING20<char>, ::engine_schemas::schema::types::STRING20> (trader, o->getTrader());
        
        return buf;
    }

    // o1 = new order that came in an matched an order on the book
    // o2 = order that was already sitting on the book
    // Time order priority algo dictates that trade price is executed at o2
    inline std::array<char, EVENT_BUFFER_SIZE> trade(const Order* o1, const Order* o2, const unsigned int& fill_quantity){

        std::array<char, EVENT_BUFFER_SIZE> buf{};
        auto m = sbepp::make_view<engine_schemas::messages::trade_schema>(buf.data(), buf.size());        
        sbepp::fill_message_header(m);

        m.eventTimestamp(CurrentTime::nanoseconds());
        m.price(o2->getPrice());
        m.quantity(fill_quantity);
        m.side(o1->getSBESide()); // o1 triggered the trade so put it as the side
        m.messageType('T');

        const std::string tradeID = boost::uuids::to_string(boost::uuids::random_generator()());
        auto tid = m.tradeID();
        utils::fillField<engine_schemas::types::STRING36<char>, ::engine_schemas::schema::types::STRING36> (tid, tradeID);

        auto sym = m.instrumentID();
        utils::fillField<engine_schemas::types::STRING4<char>, ::engine_schemas::schema::types::STRING4> (sym, o1->getInstrumentID());

        const Order* buy_order; const Order* sell_order;
        if (o1->isBuy()){
            buy_order = o1;
            sell_order = o2;
        }
        else{
            buy_order = o2;
            sell_order = o1;            
        };
        auto buy_oid = m.buyOrderID();
        utils::fillField<engine_schemas::types::STRING36<char>, ::engine_schemas::schema::types::STRING36> (buy_oid, buy_order->getOrderIDString());

        auto sell_oid = m.sellOrderID();
        utils::fillField<engine_schemas::types::STRING36<char>, ::engine_schemas::schema::types::STRING36> (sell_oid, sell_order->getOrderIDString());        

        auto buy_trader = m.buyTrader();
        utils::fillField<engine_schemas::types::STRING20<char>, ::engine_schemas::schema::types::STRING20> (buy_trader, buy_order->getTrader());

        auto sell_trader = m.sellTrader();
        utils::fillField<engine_schemas::types::STRING20<char>, ::engine_schemas::schema::types::STRING20> (sell_trader, sell_order->getTrader());

        return buf;       
    }    
}

#endif //ENCODE_H