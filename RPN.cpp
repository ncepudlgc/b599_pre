#include "RPN.h"
#include <sstream>
#include <stack>

using namespace std;

// Constructor for the custom exception
// custom exception will have different messages for different errors 
InvalidRPNString::InvalidRPNString(const string& msg) : message(msg) {}

// Override the what() method to return the error message
// used for testing in the main function because this is simple and effective.
const char* InvalidRPNString::what() const noexcept {
    return message.c_str();
}

// Calculate the value of the rpn expression
// returns a double after taking in the string input character by character onto a stack.
// Performs operations left to right.
double calculateRPN(const string& input) {
    // Check if the input is just empty or full of spaces
    if (input.empty() || input.find_first_not_of(' ') == string::npos) {
        throw InvalidRPNString("empty stack");
    }

    // Stack is the most efficient way to store the numbers
    stack<double> rpnStack;

    // Splits the string up properly even if there is whitespace
    istringstream iss(input);

    // Take one token from the input stream at a time
    string inputCharacter;

    // Loop through each part of the input
    while (iss >> inputCharacter) {
        try {
            // Try converting the current token to a number
            double num = stod(inputCharacter);
            // if its a number push it onto the stack
            rpnStack.push(num);
        }
        catch (const invalid_argument&) {
            // If it's not a number, it better be a valid operator
            if (inputCharacter != "+" && inputCharacter != "-" && inputCharacter != "*" && inputCharacter != "/") {
                throw InvalidRPNString("invalid character: " + inputCharacter);
            }

            // We need at least two numbers on the stack to do math
            if (rpnStack.size() < 2) {
                throw InvalidRPNString("too few arguments");
            }

            // Pop the top two numbers off the stack
            double b = rpnStack.top(); rpnStack.pop();
            double a = rpnStack.top(); rpnStack.pop();

            // Do the math depending on the operator
            if (inputCharacter == "+") rpnStack.push(a + b);
            else if (inputCharacter == "-") rpnStack.push(a - b);
            else if (inputCharacter == "*") rpnStack.push(a * b);
            else if (inputCharacter == "/") {
                if (b == 0) throw InvalidRPNString("cannot divide by 0");
                rpnStack.push(a / b);
            }
        }
        catch (const out_of_range&) {
            throw InvalidRPNString("number out of range");
        }
    }

    // At the end there should be exactly one number left on the stack
    if (rpnStack.size() != 1) {
        throw InvalidRPNString("too many numbers");
    }

    return rpnStack.top();
}
