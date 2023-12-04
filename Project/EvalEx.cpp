#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cmath>
#include <cctype>
#include <stdexcept>

// Function to check if a character is an operator
bool isOperator(char c) {
    return std::string("+-*/%^").find(c) != std::string::npos;
}

// Class representing a token in the expression
class Token {
public:
    enum Type { NUMBER, OPERATOR, PARENTHESIS };
    Type type;
    double value;
    char symbol;

    // Constructor for a number token
    Token(double val) : type(NUMBER), value(val), symbol(0) {}

    // Constructor for an operator or parenthesis token
    Token(char sym) : type(isOperator(sym) ? OPERATOR : PARENTHESIS), value(0), symbol(sym) {}
};

// Class representing a node in the expression tree
class ExpressionTreeNode {
public:
    Token token;
    ExpressionTreeNode *left, *right;

    // Constructor for a node with a token
    ExpressionTreeNode(Token tk) : token(tk), left(nullptr), right(nullptr) {}
};

// Class responsible for building the expression tree
class ExpressionTreeBuilder {
public:
    // Function to build the expression tree from infix tokens
    ExpressionTreeNode* buildTree(const std::vector<Token>& infixTokens) {
        std::vector<Token> postfixTokens = toPostfix(infixTokens);
        std::stack<ExpressionTreeNode*> stack;

        // Iterate through the postfix tokens
        for (std::vector<Token>::const_iterator it = postfixTokens.begin(); it != postfixTokens.end(); ++it) {
            const Token& token = *it;
            if (token.type == Token::NUMBER) {
                stack.push(new ExpressionTreeNode(token));
            } else if (token.type == Token::OPERATOR) {
                ExpressionTreeNode* node = new ExpressionTreeNode(token);

                // Pop the top two nodes from the stack and assign them as the left and right children of the current node
                if (!stack.empty()) {
                    node->right = stack.top(); stack.pop();
                }
                if (!stack.empty()) {
                    node->left = stack.top(); stack.pop();
                }

                stack.push(node);
            }
        }

        return stack.empty() ? nullptr : stack.top();
    }

private:
    // Function to convert infix tokens to postfix tokens
    std::vector<Token> toPostfix(const std::vector<Token>& tokens) {
        std::stack<Token> stack;
        std::vector<Token> output;

        // Iterate through the tokens
        for (std::vector<Token>::const_iterator it = tokens.begin(); it != tokens.end(); ++it) {
            const Token& token = *it;
            if (token.type == Token::NUMBER) {
                output.push_back(token);
            } else if (token.type == Token::OPERATOR) {
                // Pop operators from the stack and add them to the output until a lower precedence operator is encountered
                while (!stack.empty() && stack.top().type != Token::PARENTHESIS && 
                       getPrecedence(stack.top()) >= getPrecedence(token)) {
                    output.push_back(stack.top());
                    stack.pop();
                }
                stack.push(token);
            } else if (token.symbol == '(') {
                stack.push(token);
            } else if (token.symbol == ')') {
                // Pop operators from the stack and add them to the output until a '(' is encountered
                while (!stack.empty() && stack.top().symbol != '(') {
                    output.push_back(stack.top());
                    stack.pop();
                }
                if (!stack.empty()) stack.pop(); // Pop '('
            }
        }

        // Pop any remaining operators from the stack and add them to the output
        while (!stack.empty()) {
            output.push_back(stack.top());
            stack.pop();
        }

        return output;
    }

    // Function to get the precedence of an operator
    int getPrecedence(const Token& token) {
        switch (token.symbol) {
            case '+': case '-': return 1;
            case '*': case '/': case '%': return 2;
            case '^': return 3;
            default: return -1;
        }
    }
};

// Class responsible for evaluating the expression tree
class ExpressionTreeEvaluator {
public:
    // Function to evaluate the expression tree and return the result
    double evaluate(ExpressionTreeNode* root) {
        if (!root) return 0;

        if (root->token.type == Token::NUMBER) {
            return root->token.value;
        }

        // Recursively evaluate the left and right subtrees and perform the corresponding operation
        double leftVal = evaluate(root->left);
        double rightVal = evaluate(root->right);

        switch (root->token.symbol) {
            case '+': return leftVal + rightVal;
            case '-': return leftVal - rightVal;
            case '*': return leftVal * rightVal;
            case '/': 
                if (rightVal == 0) throw std::runtime_error("Division by zero");
                return leftVal / rightVal;
            case '%': return static_cast<int>(leftVal) % static_cast<int>(rightVal);
            case '^': return std::pow(leftVal, rightVal);
            default: throw std::runtime_error("Invalid operator");
        }
    }
};

// Function to tokenize the input expression
std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::string numberBuffer;
    bool expectNumber = true; // Flag indicating if a number is expected

    // Iterate through the characters in the input string
    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        // Check if the character is a digit or a decimal point
        if (isdigit(c) || c == '.') {
            numberBuffer += c;
            expectNumber = false;
        } else {
            // Handle unary operators
            if ((c == '+' || c == '-') && expectNumber) {
                // Check if the unary operator is followed by a digit or decimal
                if (i + 1 < input.length() && (isdigit(input[i + 1]) || input[i + 1] == '.')) {
                    numberBuffer += c; // Treat as part of the next number
                    continue;
                }
            }

            // Process the accumulated number, if any
            if (!numberBuffer.empty()) {
                tokens.push_back(Token(std::stod(numberBuffer)));
                numberBuffer.clear();
            }

            // Skip spaces
            if (c == ' ') continue;

            // Add operator or parenthesis tokens
            if (isOperator(c) || c == '(' || c == ')') {
                tokens.push_back(Token(c));
                expectNumber = (c == '('); // Expect a number after '('
            } else {
                throw std::runtime_error("Invalid character in expression: " + std::string(1, c));
            }
        }
    }

    // Process any remaining number in the buffer
    if (!numberBuffer.empty()) {
        tokens.push_back(Token(std::stod(numberBuffer)));
    }

    return tokens;
}

// Function to delete the expression tree
void deleteTree(ExpressionTreeNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Function to run a test case with a valid expression
void runTest(const std::string& expression, double expected) {
    std::vector<Token> tokens = tokenize(expression);
    ExpressionTreeBuilder builder;
    ExpressionTreeNode* root = builder.buildTree(tokens);
    ExpressionTreeEvaluator evaluator;
    double result = evaluator.evaluate(root);

    // Check if the result matches the expected value
    if (std::abs(result - expected) < 1e-6) {
        std::cout << "Test passed for: " << expression << ". Correctly identified result: " << result << std::endl;
    } else {
        std::cerr << "Test failed for: " << expression << ". Expected: " << expected << ", got: " << result << std::endl;
    }

    deleteTree(root);
}

// Function to run a test case with an invalid expression
void runInvalidTest(const std::string& expression, const std::string& expectedError) {
    try {
        std::vector<Token> tokens = tokenize(expression);
        ExpressionTreeBuilder builder;
        ExpressionTreeNode* root = builder.buildTree(tokens);
        ExpressionTreeEvaluator evaluator;
        double result = evaluator.evaluate(root);
        std::cerr << "Test failed for: " << expression << ". Expected error: " << expectedError << ", but no error occurred." << std::endl;
        deleteTree(root);
    } catch (const std::exception& e) {
        std::string error = e.what();
        if (error.find(expectedError) != std::string::npos) {
            std::cout << "Test passed for: " << expression << ". Correctly identified error: " << error << std::endl;
        } else {
            std::cerr << "Test failed for: " << expression << ". Expected error: " << expectedError << ", got: " << error << std::endl;
        }
    }
}

int main() {
    // Test Cases Add-01 to Add-02
    runTest("3 + 4", 7);
    runTest("(((2 + 3))) + (((1 + 2)))", 8);

    //Test Case Sub-01 to Sub-02
    runTest("8 - (5 - 2)", 5);
    runTest("(((2 - 3))) - (((1 - 2)))", 0);

    //Test Cases Mul-01 to Mul-03
    runTest("10 * 2", 20);
    runTest("10 * 2 / 5", 4);
    runTest("8 * 3*8", 192);

    //Test Cases Div-01 to Div-03
    runTest("15 / 3", 5);
    runTest("(((20 / 5))) / (((10 / 10)))", 4);
    runTest("(5 / 8) / 9^3", 0.000857339);

    //Test Cases Exp-01 to Exp-04
    runTest("2 ^ 3", 8);
    runTest("(2 ^ (3 ^ 3))", 134217728);
    runTest("(-(2^(2^4)))", -65536);
    runTest("(-2) ^ (-3)", -0.125);

    //Test Cases Mix-01 to Mix-06
    runTest("4 * (3 + 2) % 7 - 1", 5);
    runTest("(((2 ^ (1 + 1)) + ((3 - 1) ^ 2)) / ((4 / 2) % 3))", 4);
    runTest("((5 * 2) - ((3 / 1) + ((4 % 3))))", 6);
    runTest("(((((5 - 3))) * (((2 + 1))) + ((2 * 3))))", 12);
    runTest("((9 + 6)) / ((3 * 1) / (((2 + 2))) - 1)", -60);
    runTest("15 - 3 / 3", 14);
    
    //Test Cases Una-01 to Una-08
    runTest("-(+1) + (+2)", 1);
    runTest("-(-(-3)) + (-4) + (+5)", -2);
    runTest("+2 ^ (-3)", 0.125);
    runTest("-(+2) * (+3) - (-4) / (-5)", -6.8);
    runTest("+(-2) * (-3) - ((-4) / (+5))", 6.8);
    runTest("-(5 - 2)", -3);
    runTest("-(-(+2) ^ 3)", 8);
    runTest("-(+4) / (2 * 2)", -1);

    // Test Cases Err-01 to Err-04
    runInvalidTest("4 / 0", "Division by zero");
    runInvalidTest("7 & 3", "Invalid character in expression: &");
    runInvalidTest("((5 + 2) / (3 * 0))", "Division by zero");
    runInvalidTest("((7 * 3) @ 2)", "Invalid character in expression: @");

    // User input handling
    std::string userInput;
    std::cout << "\nEnter an expression to evaluate or type 'exit' to quit: ";
    while (std::getline(std::cin, userInput) && userInput != "exit") {
        try {
            std::vector<Token> tokens = tokenize(userInput);
            ExpressionTreeBuilder builder;
            ExpressionTreeNode* root = builder.buildTree(tokens);
            ExpressionTreeEvaluator evaluator;
            double result = evaluator.evaluate(root);
            std::cout << "Result: " << result << std::endl;
            deleteTree(root);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        std::cout << "\nEnter another expression or type 'exit' to quit: ";
    }

    return 0;
}