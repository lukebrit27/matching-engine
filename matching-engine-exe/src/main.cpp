#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include "Book.hpp"
#include "Order.hpp"
#include "Logger.hpp"
#include "Engine.hpp"
#include "Stringification.hpp"
#include "encode.hpp"
#include "event.hpp"
#include "decode.hpp"
#include <sbepp/sbepp.hpp>
#include <sbepp-gen/engine_schemas/messages/order_schema.hpp>

// #include "oatpp/web/server/api/ApiController.hpp"

//NEXT TIME DEVVING NOTE
// build feedhandler to manage sbe data and pub to kdb
// add message bus pub/sub framework for subbing to the data

// FUTURE DEVVING 
// Fix price field. Currently int and there's no way to know where to place the decimal place.
// In engine_schemas.xml file, change 
// Figure out prompts for AI traders
// Figure out how AI traders will connect to the exchange
// Figure out how to stream market events to AI traders
// Figure out external_project dependencies. Make sure project can build and run on diff computer (can test this within docker container)

// NICE TO HAVE IDEAS
// users should be able to add fields to orders (actually is this necessary for an mvp? could add this at a later time and write about it)

// PACKAGES
// matching-engine = code for running the exchange logic
// matching-engine-fh = kdb feedhandler for the exchange data
// matching-engine-gw = code for submitting orders to the exchange

//CURRENT GOALS
// Figure out how to write main in such a way that entites can begin submitting orders by loading some library into python
// User Experience should be
    // 1. spin up the exchange via python 
        // a. import matching-engine as eng
        // b. eng.start(`TSLA`GOOG`MSFT);
    // 2. begin submitting orders to that exchange via python
        // a. eng.submitOrder(TSLA, 34.3 )
    // 3. getting statuses on orders
    // 4. getting acknowledgements of orders

//######
// V1 TO-DOS - CORE 
// build functionality to submit and queue orders
// create rules to match orders - limit and market
// dequeue orders
// add in nothrow to handle edge cases where memory fails to be allocated (send failure back to requester)

// V2 TO-DOS - APIs
// figure out an API traders will use to submit orders (OpenAPI?)
// API for streaming subscription to data coming from the engine

// V3 TO-DOs - CHATGPT TRADERs
// look for open source chatGPT like bot that can be the traders on my exchange
// feedhandler to capture data and publish downstream to a kdb database
// market maker rewards (pay to provide liquidity)
// At this point, do a write up on the project (substack?)

// V4 TO-DOs - OPTIMIZE
// memory management
// multi-threading
// network considerations assuming a large trader base of bots (managing connections tcp/multicast, subscriptions etc. credentials to connect to the exchange?)

int main(int argc, char* argv[]){

    
    // Engine engine = Engine(); // initiate engine
    // engine.addEventListener("/tmp/testfile", "file"); // add an event listener
    // engine.start({"TES1","TES2","TES3","TES2"}); // start engine
    // // submit orders
    // engine.submitOrder("TES1", 2055, 3000, "limit", 'B', "trader1"); 
    // engine.submitOrder("TES1", 2055, 33000, "limit", 'B', "trader1"); 
    // engine.submitOrder("TES1", 2059, 400, "limit", 'B', "trader1"); 
    // engine.submitOrder("TES1", 2056, 1100, "limit", 'B', "trader1"); 
    // engine.submitOrder("TES1", 2055, 2000, "limit", 'S', "trader2"); 
    

    // Book& book = engine.getBook("TES1");
    // Order best_bid = book.getBestBid();

    // std::array<char, 1024> buf{};
    // auto m = sbepp::make_view<engine_schemas::messages::order_schema>(buf.data(), buf.size());
    // encode::order(&best_bid, m);

    // // Convert the std::array to a std::string
    // std::string str(buf.data(), buf.size());
    
    // Logger::getLogger()->info("--------------------------------------------------------------");
    // Logger::getLogger()->info(str);

    // decode sbe messages
    Logger::getLogger()->info("--------------------------------------------------------------");
    decode::Data res = decode::file("/tmp/testfile");
    Logger::getLogger()->info("Order ID of the first order record is: " + std::get<decode::Column<decode::Order::OrderID>>(res.orders.data["orderID"]).data[0]);
    Logger::getLogger()->info("Trade ID of the first trades record is: " + std::get<decode::Column<decode::Trade::TradeID>>(res.trades.data["tradeID"]).data[0]);
    
    return 0;
};