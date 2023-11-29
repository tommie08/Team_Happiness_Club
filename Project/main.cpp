#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <map>
#include <sstream>
#include <stdexcept>

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^';
}

// Function to determine the precedence of an operator
int precedence(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/' || c == '%') return 2;
    if (c == '+' || c == '-') return 1;
    return -1;
}

// Function to convert infix expression to postfix
std::string infixToPostfix(const std::string& infix) {
    std::stack<char> stack;
    std::string postfix;

    for (char c : infix) {
        if (std::isdigit(c)) {
            postfix += c;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                postfix += stack.top();
                stack.pop();
            }
            stack.pop(); // Remove the '(' from the stack
        } else if (isOperator(c)) {
            while (!stack.empty() && precedence(c) <= precedence(stack.top())) {
                postfix += stack.top();
                stack.pop();
            }
            stack.push(c);
        }
    }

    // Pop all remaining operators from the stack
    while (!stack.empty()) {
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}

// Function to evaluate postfix expression
double evaluatePostfix(const std::string& postfix) {
    std::stack<double> stack;

    for (char c : postfix) {
        if (std::isdigit(c)) {
            stack.push(c - '0'); // Convert char to int
        } else if (isOperator(c)) {
            double val2 = stack.top();
            stack.pop();
            double val1 = stack.top();
            stack.pop();

            switch (c) {
                case '+': stack.push(val1 + val2); break;
                case '-': stack.push(val1 - val2); break;
                case '*': stack.push(val1 * val2); break;
                case '/': 
                    if (val2 == 0) throw std::runtime_error("Division by zero");
                    stack.push(val1 / val2); 
                    break;
                case '%': stack.push(static_cast<int>(val1) % static_cast<int>(val2)); break;
                case '^': stack.push(std::pow(val1, val2)); break;
                default: throw std::runtime_error("Invalid operator");
            }
        }
    }

    return stack.top();
}

int main() {
    std::string expression;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, expression);

    try {
        std::string postfix = infixToPostfix(expression);
        double result = evaluatePostfix(postfix);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
