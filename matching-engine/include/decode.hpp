// Luke Britton, 2 Feb 24, decode.h
#ifndef DECODE_H
#define DECODE_H
#define EVENT_BUFFER_SIZE 200
#include <fstream>
#include <unordered_map>
#include <variant>
#include <sbepp/sbepp.hpp>
#include <sbepp-gen/engine_schemas/messages/order_schema.hpp> // sbe code
#include <sbepp-gen/engine_schemas/messages/trade_schema.hpp> // sbe code
#include "Logger.hpp"
#include "utils.hpp"

namespace decode{
    template<typename T>
    struct Column {
        std::vector<T> data;
        void emplace_back(const T& val){
            if constexpr (std::is_same_v<T, std::string>) {
                std::string trimmed_val = val;
                utils::rmTrailingNulls(trimmed_val);
                data.emplace_back(trimmed_val);
            } else {
                data.emplace_back(val);
            }            
        }
    };

    template<typename... Ts>
    using Base = std::unordered_map<std::string, std::variant<Column<Ts>...>>;
    using Table = Base<unsigned int, char, std::string>;

    struct Order{
        using MessageType = char;using EventTimestamp = unsigned int;using Price = unsigned int;using Quantity = unsigned int;
        using LeavesQuantity = unsigned int;using Side = char;using OrderID = std::string;using OrderType = std::string;
        using OrderStatus = std::string;using InstrumentID = std::string;using Trader = std::string;

        Table data;
        Order(){
            data["messageType"] = Column<MessageType>();
            data["eventTimestamp"] = Column<EventTimestamp>();
            data["price"] = Column<Price>();
            data["quantity"] = Column<Quantity>();
            data["leavesQuantity"] = Column<LeavesQuantity>();
            data["side"] = Column<Side>();
            data["orderID"] = Column<OrderID>();
            data["orderType"] = Column<OrderType>();
            data["orderStatus"] = Column<OrderStatus>();
            data["instrumentID"] = Column<InstrumentID>();
            data["trader"] = Column<Trader>();           
        }

        // Function to emplace back into each column of the Order
        template<typename T>
        void emplaceBackToColumn(const std::string& columnName, const T& value) {
            std::get<Column<T>>(data[columnName]).emplace_back(value);
        }
    };

    struct Trade{
        using MessageType = char;using EventTimestamp = unsigned int;using Price = unsigned int;using Quantity = unsigned int;
        using Side = char;using TradeID = std::string;using InstrumentID = std::string;using BuyOrderID = std::string;
        using SellOrderID = std::string;using BuyTrader = std::string;using SellTrader = std::string;

        Table data;
        Trade(){
            data["messageType"] = Column<MessageType>();
            data["eventTimestamp"] = Column<EventTimestamp>();
            data["price"] = Column<Price>();
            data["quantity"] = Column<Quantity>();
            data["side"] = Column<Side>();
            data["tradeID"] = Column<TradeID>();
            data["instrumentID"] = Column<InstrumentID>();
            data["buyOrderID"] = Column<BuyOrderID>();
            data["sellOrderID"] = Column<SellOrderID>();
            data["buyTrader"] = Column<BuyTrader>();
            data["sellTrader"] = Column<SellTrader>();
        }

        // Function to emplace back into each column of the Trade
        template<typename T>
        void emplaceBackToColumn(const std::string& columnName, const T& value) {
            std::get<Column<T>>(data[columnName]).emplace_back(value);
        } 
    };

    struct Data{
        Order orders;
        Trade trades;
    };

    inline void order(std::string& line, Order& orders){
        std::array<char, EVENT_BUFFER_SIZE> buf;
        std::copy(line.data(), line.data() + EVENT_BUFFER_SIZE, buf.begin());
        auto m = sbepp::make_const_view<engine_schemas::messages::order_schema>(buf.data(), buf.size());
        orders.emplaceBackToColumn<Order::MessageType>("messageType", m.messageType().value());
        orders.emplaceBackToColumn<Order::EventTimestamp>("eventTimestamp", m.eventTimestamp().value());
        orders.emplaceBackToColumn<Order::Price>("price", m.price().value());
        orders.emplaceBackToColumn<Order::Quantity>("quantity", m.quantity().value());
        orders.emplaceBackToColumn<Order::LeavesQuantity>("leavesQuantity", m.leavesQuantity().value());
        orders.emplaceBackToColumn<Order::Side>("side", static_cast<char>(m.side()));
        orders.emplaceBackToColumn<Order::OrderID>("orderID", utils::convertToString(m.orderID().data(), m.orderID().size()));
        orders.emplaceBackToColumn<Order::OrderType>("orderType", sbepp::enum_to_string(m.orderType()));
        orders.emplaceBackToColumn<Order::OrderStatus>("orderStatus", sbepp::enum_to_string(m.orderStatus()));
        orders.emplaceBackToColumn<Order::InstrumentID>("instrumentID", utils::convertToString(m.instrumentID().data(), m.instrumentID().size()));
        orders.emplaceBackToColumn<Order::Trader>("trader", utils::convertToString(m.trader().data(), m.trader().size()));
    }

    inline void trade(std::string& line, Trade& trades){
        std::array<char, EVENT_BUFFER_SIZE> buf;
        std::copy(line.data(), line.data() + EVENT_BUFFER_SIZE, buf.begin());
        auto m = sbepp::make_const_view<engine_schemas::messages::trade_schema>(buf.data(), buf.size());
        trades.emplaceBackToColumn<Trade::MessageType>("messageType", m.messageType().value());
        trades.emplaceBackToColumn<Trade::EventTimestamp>("eventTimestamp", m.eventTimestamp().value());
        trades.emplaceBackToColumn<Trade::Price>("price", m.price().value());
        trades.emplaceBackToColumn<Trade::Quantity>("quantity", m.quantity().value());
        trades.emplaceBackToColumn<Trade::Side>("side", static_cast<char>(m.side()));
        trades.emplaceBackToColumn<Trade::TradeID>("tradeID", utils::convertToString(m.tradeID().data(), m.tradeID().size()));
        trades.emplaceBackToColumn<Trade::InstrumentID>("instrumentID", utils::convertToString(m.instrumentID().data(), m.instrumentID().size()));
        trades.emplaceBackToColumn<Trade::BuyOrderID>("buyOrderID", utils::convertToString(m.buyOrderID().data(), m.buyOrderID().size()));
        trades.emplaceBackToColumn<Trade::SellOrderID>("sellOrderID", utils::convertToString(m.sellOrderID().data(), m.sellOrderID().size()));
        trades.emplaceBackToColumn<Trade::BuyTrader>("buyTrader", utils::convertToString(m.buyTrader().data(), m.buyTrader().size()));
        trades.emplaceBackToColumn<Trade::SellTrader>("sellTrader", utils::convertToString(m.sellTrader().data(), m.sellTrader().size()));
    }

    inline void data(std::string& line, char& msg_type, Order& orders, Trade& trades){
        // expected that message type is always the first value after the message header
        switch (msg_type){
            case 'O': order(line, orders); break;
            case 'T': trade(line, trades); break;
            default:
                Logger::getLogger()->warn("DATA DECODER: Ignoring invalid message type: '" + std::string(1, msg_type) + "'");
                break;
        }
    }

    inline Data file(const std::string& file_name, unsigned int last_n_lines = 0){
        std::ifstream file(file_name);
        Data data;

        if (!file.is_open()) {
            Logger::getLogger()->error("DATA DECODER: Error opening file " + file_name);
            return data;
        }

        Order orders;
        Trade trades;

        auto decodeFunc = [&file, &orders, &trades] {
            std::string line;
            unsigned int header_size = sbepp::schema_traits<engine_schemas::schema>::header_type<char>()(sbepp::detail::size_bytes_tag{});
            char msg_type;
            while (std::getline(file, line)) {
                char msg_type = line[header_size];
                decode::data(line, msg_type, orders, trades);
            }
        };
        
        // last_n_lines=0 means reads the whole file
        // last_n_lines!=0 means need to update stream position so only the last n lines are read
        if (last_n_lines != 0){
            file.seekg(0, std::ios::end); // Move to end of file
            std::streamoff fileSize = file.tellg(); // Get file size
            // Read the file backward until n lines are read or beginning of file is reached
            std::string line;
            int linesRead = 0;
            for (std::streamoff pos = fileSize - 1; pos >= 0 && linesRead < last_n_lines; --pos) {
                file.seekg(pos);
                char c;
                file.get(c);
                if (c == '\n') {
                    ++linesRead;
                }
                file.seekg(pos);
            }
        };

        decodeFunc(); // decode orders/trades
        file.close(); // Close the file when done
        data.orders = orders; data.trades = trades;
        return data;
    }
}

#endif //DECODE_H