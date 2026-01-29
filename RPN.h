#pragma once


#include <string>
#include <stdexcept>

// Custom exception for invalid RPN strings
class InvalidRPNString : public std::exception {
private:
    std::string message;
public:
    explicit InvalidRPNString(const std::string& msg);
    const char* what() const noexcept override;
};

// Function declaration
double calculateRPN(const std::string& input);



