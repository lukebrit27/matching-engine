// Luke Britton, 2 Feb 24, decode.h
#ifndef DECODE_H
#define DECODE_H
#define EVENT_BUFFER_SIZE 200
#include <sbepp/sbepp.hpp>
#include <sbepp-gen/engine_schemas/messages/order_schema.hpp> // sbe code
#include <sbepp-gen/engine_schemas/messages/trade_schema.hpp> // sbe code
#include "Stringification.hpp"
#include "Logger.hpp"

namespace decode{
    inline std::string order(std::string& line){
        std::array<char, EVENT_BUFFER_SIZE> buf;
        std::copy(line.data(), line.data() + EVENT_BUFFER_SIZE, buf.begin());
        auto m = sbepp::make_const_view<engine_schemas::messages::order_schema>(buf.data(), buf.size());
        auto res = sbepp::visit<to_string_visitor>(m);
        return fmt::format("{}", res.str());
    };

    inline std::string trade(std::string& line){
        std::array<char, EVENT_BUFFER_SIZE> buf;
        std::copy(line.data(), line.data() + EVENT_BUFFER_SIZE, buf.begin());
        auto m = sbepp::make_const_view<engine_schemas::messages::trade_schema>(buf.data(), buf.size());
        auto res = sbepp::visit<to_string_visitor>(m);
        return fmt::format("{}", res.str());
    };

    inline std::string data(std::string& line){
        // TO-DO write function that checks message type and applies correct decode function
        // expected that message type is always the first value after the message header
        unsigned int header_size = sbepp::schema_traits<engine_schemas::schema>::header_type<char>()(sbepp::detail::size_bytes_tag{});
        char msg_type = line[header_size];
        switch (msg_type){
            case 'O': return order(line);
            case 'T': return trade(line);
            default:{
                Logger::getLogger()->warn("DATA DECODER: Ignoring invalid message type: '" + std::string(1, msg_type) + "'");
                return "";
            }
        }
    }
}

#endif //DECODE_H