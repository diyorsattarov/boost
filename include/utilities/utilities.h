#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <memory>
#include <sstream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <bar/bar.h>
#include <message_handler/message_handler.h>

class Utilities {
public:
    static std::shared_ptr<spdlog::logger> console_logger();
    static std::shared_ptr<spdlog::logger> file_logger(const std::string& filename);
    static std::shared_ptr<spdlog::logger> combined_logger(const std::string& filename);

private:
    static std::shared_ptr<spdlog::logger> create_console_logger();
    static std::shared_ptr<spdlog::logger> create_file_logger(const std::string& filename);
};

#endif