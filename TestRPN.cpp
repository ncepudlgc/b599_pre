#include "RPN.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

// Test counter
int totalTests = 0;
int passedTests = 0;
int failedTests = 0;

// Helper function to check if two doubles are approximately equal
bool approximatelyEqual(double a, double b, double epsilon = 1e-9) {
    return abs(a - b) < epsilon;
}

// Test function template
void test(const string& testName, const string& input, double expected, bool expectException = false, const string& expectedExceptionMsg = "") {
    totalTests++;
    cout << "Test " << totalTests << ": " << testName << " ... ";
    
    try {
        double result = calculateRPN(input);
        
        if (expectException) {
            cout << "FAILED (Expected exception but got result: " << result << ")" << endl;
            failedTests++;
            return;
        }
        
        if (approximatelyEqual(result, expected)) {
            cout << "PASSED (Result: " << result << ")" << endl;
            passedTests++;
        } else {
            cout << "FAILED (Expected: " << expected << ", Got: " << result << ")" << endl;
            failedTests++;
        }
    } catch (const InvalidRPNString& e) {
        if (expectException) {
            if (expectedExceptionMsg.empty() || string(e.what()).find(expectedExceptionMsg) != string::npos) {
                cout << "PASSED (Exception: " << e.what() << ")" << endl;
                passedTests++;
            } else {
                cout << "FAILED (Expected exception containing: '" << expectedExceptionMsg 
                     << "', Got: '" << e.what() << "')" << endl;
                failedTests++;
            }
        } else {
            cout << "FAILED (Unexpected exception: " << e.what() << ")" << endl;
            failedTests++;
        }
    } catch (const exception& e) {
        cout << "FAILED (Unexpected exception type: " << e.what() << ")" << endl;
        failedTests++;
    }
}

int main() {
    cout << "========================================" << endl;
    cout << "RPN Calculator Comprehensive Test Suite" << endl;
    cout << "========================================" << endl << endl;
    
    // Basic arithmetic operations
    cout << "--- Basic Arithmetic Operations ---" << endl;
    test("Simple addition: 2 3 +", "2 3 +", 5.0);
    test("Simple subtraction: 5 2 -", "5 2 -", 3.0);
    test("Simple multiplication: 4 3 *", "4 3 *", 12.0);
    test("Simple division: 10 2 /", "10 2 /", 5.0);
    test("Division with decimal result: 7 2 /", "7 2 /", 3.5);
    cout << endl;
    
    // Negative numbers
    cout << "--- Negative Numbers ---" << endl;
    test("Negative number addition: -2 3 +", "-2 3 +", 1.0);
    test("Subtraction with negative: 5 -2 -", "5 -2 -", 7.0);
    test("Negative multiplication: -3 -4 *", "-3 -4 *", 12.0);
    test("Negative division: -10 2 /", "-10 2 /", -5.0);
    test("All negative: -2 -3 +", "-2 -3 +", -5.0);
    cout << endl;
    
    // Decimal numbers
    cout << "--- Decimal Numbers ---" << endl;
    test("Decimal addition: 2.5 3.7 +", "2.5 3.7 +", 6.2);
    test("Decimal subtraction: 10.5 3.2 -", "10.5 3.2 -", 7.3);
    test("Decimal multiplication: 2.5 4.0 *", "2.5 4.0 *", 10.0);
    test("Decimal division: 7.5 2.5 /", "7.5 2.5 /", 3.0);
    test("Small decimals: 0.1 0.2 +", "0.1 0.2 +", 0.3);
    cout << endl;
    
    // Complex expressions
    cout << "--- Complex Expressions ---" << endl;
    test("Three operands: 2 3 + 4 +", "2 3 + 4 +", 9.0);
    test("Multiple operations: 2 3 + 4 *", "2 3 + 4 *", 20.0);
    test("Nested operations: 10 2 / 3 +", "10 2 / 3 +", 8.0);
    test("Long expression: 1 2 + 3 + 4 + 5 +", "1 2 + 3 + 4 + 5 +", 15.0);
    test("Mixed operations: 15 7 1 1 + - / 3 * 2 1 1 + + -", "15 7 1 1 + - / 3 * 2 1 1 + + -", 5.0);
    test("Complex: 2 3 4 + *", "2 3 4 + *", 14.0);
    test("Complex: 4 2 5 * + 1 3 2 * + /", "4 2 5 * + 1 3 2 * + /", 2.0);
    cout << endl;
    
    // Single number
    cout << "--- Single Number ---" << endl;
    test("Single positive number: 42", "42", 42.0);
    test("Single negative number: -42", "-42", -42.0);
    test("Single decimal: 3.14", "3.14", 3.14);
    cout << endl;
    
    // Large numbers
    cout << "--- Large Numbers ---" << endl;
    test("Large addition: 1000000 2000000 +", "1000000 2000000 +", 3000000.0);
    test("Large multiplication: 1000 1000 *", "1000 1000 *", 1000000.0);
    test("Very large: 999999999 1 +", "999999999 1 +", 1000000000.0);
    cout << endl;
    
    // Edge cases with valid input
    cout << "--- Edge Cases (Valid) ---" << endl;
    test("Zero addition: 0 5 +", "0 5 +", 5.0);
    test("Zero multiplication: 5 0 *", "5 0 *", 0.0);
    test("Identity addition: 5 0 +", "5 0 +", 5.0);
    test("Identity multiplication: 5 1 *", "5 1 *", 5.0);
    test("Very small decimal: 0.0001 0.0002 +", "0.0001 0.0002 +", 0.0003);
    cout << endl;
    
    // Error cases: Empty and whitespace
    cout << "--- Error Cases: Empty/Whitespace ---" << endl;
    test("Empty string", "", 0.0, true, "empty stack");
    test("Only spaces", "   ", 0.0, true, "empty stack");
    test("Only tabs", "\t\t", 0.0, true, "empty stack");
    test("Mixed whitespace", "  \t  \t  ", 0.0, true, "empty stack");
    cout << endl;
    
    // Error cases: Invalid characters
    cout << "--- Error Cases: Invalid Characters ---" << endl;
    test("Invalid character: a", "a", 0.0, true, "invalid character");
    test("Invalid character: x", "x", 0.0, true, "invalid character");
    test("Invalid character: @", "@", 0.0, true, "invalid character");
    test("Mixed valid and invalid: 2 3 x", "2 3 x", 0.0, true, "invalid character");
    test("Invalid operator: %", "%", 0.0, true, "invalid character");
    test("Invalid operator: ^", "^", 0.0, true, "invalid character");
    cout << endl;
    
    // Error cases: Too few arguments
    cout << "--- Error Cases: Too Few Arguments ---" << endl;
    test("Only operator: +", "+", 0.0, true, "too few arguments");
    test("One number then operator: 2 +", "2 +", 0.0, true, "too few arguments");
    test("Two operators: + -", "+ -", 0.0, true, "too few arguments");
    test("Three operators: + - *", "+ - *", 0.0, true, "too few arguments");
    cout << endl;
    
    // Error cases: Too many numbers
    cout << "--- Error Cases: Too Many Numbers ---" << endl;
    test("Two numbers: 2 3", "2 3", 0.0, true, "too many numbers");
    test("Three numbers: 1 2 3", "1 2 3", 0.0, true, "too many numbers");
    test("Four numbers: 1 2 3 4", "1 2 3 4", 0.0, true, "too many numbers");
    test("Numbers with operator: 2 3 4 +", "2 3 4 +", 0.0, true, "too many numbers");
    test("Multiple numbers: 1 2 3 4 5", "1 2 3 4 5", 0.0, true, "too many numbers");
    cout << endl;
    
    // Error cases: Division by zero
    cout << "--- Error Cases: Division by Zero ---" << endl;
    test("Division by zero: 5 0 /", "5 0 /", 0.0, true, "cannot divide by 0");
    test("Division by zero (decimal): 5 0.0 /", "5 0.0 /", 0.0, true, "cannot divide by 0");
    test("Division by zero (negative): -5 0 /", "-5 0 /", 0.0, true, "cannot divide by 0");
    test("Complex division by zero: 2 3 + 0 /", "2 3 + 0 /", 0.0, true, "cannot divide by 0");
    cout << endl;
    
    // Whitespace variations
    cout << "--- Whitespace Variations ---" << endl;
    test("Extra spaces: 2   3   +", "2   3   +", 5.0);
    test("Tabs: 2\t3\t+", "2\t3\t+", 5.0);
    test("Mixed whitespace: 2  3\t+", "2  3\t+", 5.0);
    test("Leading/trailing spaces:  2 3 +  ", "  2 3 +  ", 5.0);
    test("Newlines: 2\n3\n+", "2\n3\n+", 5.0);
    cout << endl;
    
    // Operator precedence simulation
    cout << "--- Operator Precedence Simulation ---" << endl;
    test("Left to right: 8 4 2 / /", "8 4 2 / /", 4.0); // (8 / (4/2)) = 8/2 = 4
    test("Left to right: 2 3 + 4 5 + *", "2 3 + 4 5 + *", 45.0); // (2+3) * (4+5) = 5*9 = 45
    test("Left to right: 10 2 / 5 *", "10 2 / 5 *", 25.0); // (10/2) * 5 = 5*5 = 25
    cout << endl;
    
    // Precision tests
    cout << "--- Precision Tests ---" << endl;
    test("High precision: 0.1 0.2 +", "0.1 0.2 +", 0.3);
    test("Many decimals: 3.1415926535 2.7182818284 +", "3.1415926535 2.7182818284 +", 5.8598744819);
    test("Very small: 0.0000001 0.0000002 +", "0.0000001 0.0000002 +", 0.0000003);
    cout << endl;
    
    // Summary
    cout << "========================================" << endl;
    cout << "Test Summary" << endl;
    cout << "========================================" << endl;
    cout << "Total tests: " << totalTests << endl;
    cout << "Passed: " << passedTests << endl;
    cout << "Failed: " << failedTests << endl;
    cout << "Success rate: " << fixed << setprecision(2) 
         << (100.0 * passedTests / totalTests) << "%" << endl;
    cout << "========================================" << endl;
    
    if (failedTests > 0) {
        cout << "\nFAILED TESTS DETECTED! Please review the output above." << endl;
        return 1;
    } else {
        cout << "\nAll tests passed!" << endl;
        return 0;
    }
}
