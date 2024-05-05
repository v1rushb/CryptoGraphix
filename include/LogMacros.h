#ifndef LOGDEFINES_H
#define LOGDEFINES_H
#include "../src/Logger.cpp"

#define LOG_INFO(msg) Logger::getInstance("../Logger/App.logs")->log(msg, LogLevel::INFO)
#define LOG_WARNING(msg) Logger::getInstance("../Logger/App.logs")->log(msg, LogLevel::WARNING)
#define LOG_ERROR(msg) Logger::getInstance("../Logger/App.logs")->log(msg, LogLevel::ERROR)

#endif