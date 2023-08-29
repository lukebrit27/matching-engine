#include <thread>
#include <chrono>
#include "Book.h"
#include "Order.h"
#include "Logger.h"
// #include "oatpp/web/server/api/ApiController.hpp"

//NEXT TIME DEVVING NOTE
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
   auto logger = Logger::getLogger();
   logger->info("This is a log message from another file.");

   Book orderbook = Book();

   orderbook.submitOrder(2055, 3000, OrderType::limit, 'B');

   orderbook.submitOrder(2055, 33000, OrderType::limit, 'B');
    
   orderbook.submitOrder(2059, 400, OrderType::limit, 'B');
  
   orderbook.submitOrder(2056, 1100, OrderType::limit, 'B');   
    
   orderbook.submitOrder(2055, 2000, OrderType::limit, 'S'); 

};