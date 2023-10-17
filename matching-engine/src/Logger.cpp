//Luke Britton, 9 Aug 23, Logger.cpp

#include "Logger.hpp"  // Header file for the logger singleton

std::shared_ptr<spdlog::logger> Logger::getLogger() {
    static std::shared_ptr<spdlog::logger> logger = [] {

        // Initialize the thread pool for asynchronous logging
        // default for now is 8192 messages allowed in the queue, on thread in the thread pool
        // TO-DO At some point some experiment with optimzing these numbers
        spdlog::init_thread_pool(8192, 1); 

        // Create and configure the asynchronous logger with daily rotating file sink
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto rotating_file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logfile", 0, 0);  // "0, 0" means rotate daily at midnight
        std::vector<spdlog::sink_ptr> sinks = {console_sink, rotating_file_sink};

        auto async_logger = std::make_shared<spdlog::async_logger>("shared_logger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
        async_logger->set_level(spdlog::level::info);
        async_logger->set_pattern("[%Y-%m-%d %H:%M:%S.%f] [%n] [%l] %v");

        // Register a callback to shut down the logger when the program exits
        std::atexit([] { spdlog::shutdown(); });

        return async_logger;
    }();
    

    return logger;
}
