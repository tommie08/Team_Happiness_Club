#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <cmath>
#include <stdexcept>

class Token {
public:
    enum Type { NUMBER, OPERATOR, PARENTHESIS };
    Type type;
    double value;
    char symbol;

    Token(double val) : type(NUMBER), value(val), symbol(0) {}
    Token(char sym) : type(isOperator(sym) ? OPERATOR : PARENTHESIS), value(0), symbol(sym) {}

private:
    static bool isOperator(char c) {
        return std::string("+-*/%^").find(c) != std::string::npos;
    }
};

class ExpressionTreeNode {
public:
    Token token;
    ExpressionTreeNode *left, *right;

    ExpressionTreeNode(Token tk) : token(tk), left(nullptr), right(nullptr) {}
};

class ExpressionTreeBuilder {
public:
    ExpressionTreeNode* buildTree(const std::vector<Token>& infixTokens) {
        std::vector<Token> postfixTokens = toPostfix(infixTokens);
        std::stack<ExpressionTreeNode*> stack;

        for (const auto& token : postfixTokens) {
            if (token.type == Token::NUMBER) {
                stack.push(new ExpressionTreeNode(token));
            } else if (token.type == Token::OPERATOR) {
                ExpressionTreeNode* node = new ExpressionTreeNode(token);

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
    std::vector<Token> toPostfix(const std::vector<Token>& tokens) {
        std::stack<Token> stack;
        std::vector<Token> output;

        for (const auto& token : tokens) {
            if (token.type == Token::NUMBER) {
                output.push_back(token);
            } else if (token.type == Token::OPERATOR) {
                while (!stack.empty() && stack.top().type != Token::PARENTHESIS && 
                       getPrecedence(stack.top()) >= getPrecedence(token)) {
                    output.push_back(stack.top());
                    stack.pop();
                }
                stack.push(token);
            } else if (token.symbol == '(') {
                stack.push(token);
            } else if (token.symbol == ')') {
                while (!stack.empty() && stack.top().symbol != '(') {
                    output.push_back(stack.top());
                    stack.pop();
                }
                if (!stack.empty()) stack.pop(); // Pop '('
            }
        }

        while (!stack.empty()) {
            output.push_back(stack.top());
            stack.pop();
        }

        return output;
    }

    int getPrecedence(const Token& token) {
        switch (token.symbol) {
            case '+': case '-': return 1;
            case '*': case '/': case '%': return 2;
            case '^': return 3;
            default: return -1;
        }
    }
};

class ExpressionTreeEvaluator {
public:
    double evaluate(ExpressionTreeNode* root) {
        if (!root) return 0;

        if (root->token.type == Token::NUMBER) {
            return root->token.value;
        }

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

std::vector<Token> tokenize(const std::string& input) {
    std::vector<Token> tokens;
    std::string numberBuffer;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        if (isdigit(c) || c == '.') {
            numberBuffer += c;
        } else {
            if (!numberBuffer.empty()) {
                tokens.push_back(Token(std::stod(numberBuffer)));
                numberBuffer.clear();
            }

            if (c == ' ') continue;

            if ((c == '+' || c == '-') && (tokens.empty() || tokens.back().type != Token::NUMBER && tokens.back().symbol != ')')) {
                numberBuffer += c;
            } else {
                tokens.push_back(Token(c));
            }
        }
    }

    if (!numberBuffer.empty()) {
        tokens.push_back(Token(std::stod(numberBuffer)));
    }

    return tokens;
}

void deleteTree(ExpressionTreeNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void runTest(const std::string& expression, double expected) {
    std::vector<Token> tokens = tokenize(expression);
    ExpressionTreeBuilder builder;
    ExpressionTreeNode* root = builder.buildTree(tokens);
    ExpressionTreeEvaluator evaluator;
    double result = evaluator.evaluate(root);

    if (std::abs(result - expected) < 1e-6) {
        std::cout << "Test passed for: " << expression << std::endl;
    } else {
        std::cerr << "Test failed for: " << expression << ". Expected: " << expected << ", got: " << result << std::endl;
    }

    deleteTree(root);
}

int main() {
    // Example Tests
    runTest("2 + 3 * 4", 14);
    runTest("(2 + 3) * 4", 20);
    // More tests...

    return 0;
}