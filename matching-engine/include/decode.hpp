// Luke Britton, 2 Feb 24, decode.h
#ifndef DECODE_H
#define DECODE_H
#define EVENT_BUFFER_SIZE 1024
#include <sbepp/sbepp.hpp>
#include <sbepp-gen/engine_schemas/messages/order_schema.hpp> // sbe code
#include "Stringification.hpp"

namespace decode{
    std::string order(std::array<char, EVENT_BUFFER_SIZE>& buf){
        auto m = sbepp::make_const_view<engine_schemas::messages::order_schema>(buf.data(), buf.size());
        auto res = sbepp::visit<to_string_visitor>(m);
        return fmt::format("{}", res.str());
    };        
}

#endif //DECODE_H