#include "Book.h"
#include "Order.h"
#include <iostream>

// V1 TO-DOS - CORE 
// build functionality to submit and queue orders
// create rules to match orders - limit and market
// dequeue orders

// V2 TO-DOS - APIs
// figure out an API traders will use to submit orders (OpenAPI?)
// API for streaming subscription to data coming from the engine

// V3 TO-DOs - CHATGPT TRADERs
// look for open source chatGPT like bot that can be the traders on my exchange
// feedhandler to capture data and publish downstream to a kdb database
// At this point, do a write up on the project (substack?)

// V4 TO-DOs - OPTIMIZE
// memory management
// multi-threading
// network considerations assuming a large trader base of bots (managing connections, subscriptions etc. credentials to connect to the exchange?)

int main(int argc, char* argv[]){

   Book orderbook = Book();

   std::cout << "Submitting first order!" << std::endl;
   std::cout << "" << std::endl;   
   orderbook.submitOrder(2055, 3000, "limit", 'B');

   std::cout << "Submitting second order!" << std::endl;
   std::cout << "" << std::endl;      
   orderbook.submitOrder(2055, 33000, "limit", 'B');

   std::cout << "Submitting third order!" << std::endl;
   std::cout << "" << std::endl;      
   orderbook.submitOrder(2059, 400, "limit", 'B');

   std::cout << "Submitting fourth order!" << std::endl;
   std::cout << "" << std::endl;      
   orderbook.submitOrder(2056, 1100, "limit", 'B');   

   std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << std::endl;  
   orderbook.printBids(10);
};