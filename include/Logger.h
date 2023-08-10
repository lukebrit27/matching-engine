//Luke Britton, 9 Aug 23, Logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>  // Include the daily file sink header
#include <spdlog/async.h>

class Logger {
public:
    static std::shared_ptr<spdlog::logger> getLogger();
};

#endif //LOGGER_H