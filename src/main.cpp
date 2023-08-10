#include "Book.h"
#include "Order.h"
#include <iostream>
#include "Logger.h"

//NEXT TIME DEVVING NOTE
// Add more logging and validate matching logic working as expected
// figure out API for submitting orders
// figure out if there's a way to add 'debug' logging that can be turned on & off 

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