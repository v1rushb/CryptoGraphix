#ifndef ERRORHANDLER_CPP
#define ERRORHANDLER_CPP
#include <exception>
#include <string>

using namespace std;

class CustomException : public exception {
private:
    string message;

public:
    CustomException(const string& msg = "An error has occurred. Please try again later.") 
        : message(msg) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};
#endif
