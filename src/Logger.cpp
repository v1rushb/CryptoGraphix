#ifndef LOGGER_CPP
#define LOGGER_CPP
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include "../include/LogMacros.h"

enum class LogLevel {
    INFO, WARNING, ERROR,
};

using namespace std;

class Logger {
private:
    static Logger* instance;
    ofstream logFile;
    LogLevel logLevel = LogLevel::INFO;

    explicit Logger(const string& fileName) {
        logFile.open(fileName, ios::out | ios::app);
        if (!logFile.is_open()) {
            cerr << "Failed to open log file: " << fileName << endl;
            exit(1);
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    string getTimestamp() {
        auto now = chrono::system_clock::now();
        auto in_time_t = chrono::system_clock::to_time_t(now);
        stringstream ss;
        ss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
        return ss.str();
    }

    string getLevelString(LogLevel level) {
        switch(level) {
            case LogLevel::INFO: return "[INFO]";
            case LogLevel::WARNING: return "[WARNING]";
            case LogLevel::ERROR: return "[ERROR]";
            default: return "[UNKNOWN]";
        }
    }

    string getColoredLevelString(LogLevel level) {
        switch(level) {
            case LogLevel::INFO:
                return "\033[32m[INFO]\033[0m";  // Green
            case LogLevel::WARNING:
                return "\033[33m[WARNING]\033[0m";  // Yellow
            case LogLevel::ERROR:
                return "\033[31m[ERROR]\033[0m";  // Red
            default:
                return "\033[37m[UNKNOWN]\033[0m";  // Grey
        }
    }

public:
    static Logger* getInstance(const string& fileName) {
        if (instance == nullptr) {
            instance = new Logger(fileName);
        }
        return instance;
    }

    void setLogLevel(LogLevel level) {
        logLevel = level;
    }

    void log(const string& message, LogLevel level) {
        if (level < logLevel) {
            return;
        }

        string timestamp = getTimestamp();
        string logLevelString = getLevelString(level);
        string coloredLogLevelString = getColoredLevelString(level);

        string consoleMessage = timestamp + " " + coloredLogLevelString + " " + message;
        string fileMessage = timestamp + " " + logLevelString + " " + message;

        // cout << consoleMessage << endl;
        logFile << fileMessage << endl;
    }
};

Logger* Logger::instance = nullptr;
Logger* logger = Logger::getInstance("../Logger/App.logs");

#endif