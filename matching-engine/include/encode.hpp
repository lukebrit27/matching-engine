// Luke Britton, 2 Feb 24, encode.h
#ifndef ENCODE_H
#define ENCODE_H
#include "Order.hpp"
#include "utils.hpp"
#include <sbepp/sbepp.hpp>
#include <sbepp-gen/engine_schemas/messages/order_schema.hpp> // sbe code

namespace encode{
    void order(const Order* o, auto& m){

        sbepp::fill_message_header(m);

        m.eventTimestamp(o->getEventTimestamp());
        m.price(o->getPrice());
        m.quantity(o->getQuantity());
        m.leavesQuantity(o->getLeavesQuantity());
        m.side(o->getSBESide());
        m.orderType(o->getSBEOrderType());
        m.orderStatus(o->getSBEOrderStatus());

        auto oid = m.orderID();
        utils::fillField<engine_schemas::types::STRING36<char>, ::engine_schemas::schema::types::STRING36> (oid, o->getOrderIDString());

        auto sym = m.instrumentID();
        utils::fillField<engine_schemas::types::STRING4<char>, ::engine_schemas::schema::types::STRING4> (sym, o->getInstrumentID());        
    }
}

#endif //ENCODE_H