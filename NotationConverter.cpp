#include "NotationConverter.hpp"
#include "Deque.hpp"
#include <stdexcept>
#include <sstream>
#include <algorithm>

// Helper function definitions
bool NotationConverter::isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int NotationConverter::getPrecedence(char ch) {
    switch (ch) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

Deque NotationConverter::decodeInput(std::string& inStr) {
    inStr = preprocess(inStr);
    Deque dq;
    stringstream ss(inStr);
    string token;
    while (ss >> token) {

        for (char c: token) {
            if (!isalnum(c) && !isOperator(c) && c != '(' && c != ')') {
                throw runtime_error("Invalid character encountered");
            }
        }
        dq.pushRear(token);
    }
    return dq;
}

string NotationConverter::formatExpression(const string & str) {
    string result;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ' && i > 0 && (str[i - 1] == '(' || str[i - 1] == ')')) {
            continue;
        }
        if (str[i] == ' ' && i < str.size() - 1 && (str[i + 1] == '(' || str[i + 1] == ')')) {
            continue;
        }
        result += str[i];
    }

    string finalResult;
    for (size_t i = 0; i < result.size(); ++i) {
        if (result[i] == '*' || result[i] == '/' || result[i] == '+' || result[i] == '-') {
            if (i > 0 && result[i - 1] != ' ') {
                finalResult += ' ';
            }
            finalResult += result[i];
            if (i < result.size() - 1 && result[i + 1] != ' ') {
                finalResult += ' ';
            }
        } else {
            finalResult += result[i];
        }
    }

    return finalResult;
}

string NotationConverter::preprocess(const string & str) {
    string result;
    for (char ch: str) {
        if (ch == '(' || ch == ')' || isOperator(ch)) {
            result += " ";
            result += ch;
            result += " ";
        } else {
            result += ch;
        }
    }
    return result;
}

string NotationConverter::infixToPostfix(string inStr) {
    Deque stack;
    Deque input = decodeInput(inStr);
    string output = "";

    while (!input.isEmpty()) {
        string token = input.popFront();

        if (!isOperator(token[0]) && token != "(" && token != ")") {
            output += token + " ";
        } else if (token == "(") {
            stack.pushRear(token);
        } else if (token == ")") {
            while (stack.getRear() != "(") {
                output += stack.popRear() + " ";
            }
            stack.popRear();
        } else {
            while (!stack.isEmpty() && getPrecedence(token[0]) <= getPrecedence(stack.getRear()[0])) {
                output += stack.popRear() + " ";
            }
            stack.pushRear(token);
        }
    }

    while (!stack.isEmpty()) {
        output += stack.popRear() + " ";
    }

    if (!output.empty()) {
        output.pop_back();
    }

    return output;
}

string NotationConverter::postfixToInfix(string inStr) {
    Deque stack;
    Deque input = decodeInput(inStr);

    while (!input.isEmpty()) {
        string token = input.popFront();

        if (!isOperator(token[0])) {
            stack.pushRear(token);
        } else {
            string operand2 = stack.popRear();
            string operand1 = stack.popRear();
            string infixExp = "(" + operand1 + " " + token + " " + operand2 + ")";
            stack.pushRear(infixExp);
        }
    }

    return formatExpression(stack.popRear());
}

string NotationConverter::postfixToPrefix(string inStr) {

    string infixStr = postfixToInfix(inStr);

    return infixToPrefix(infixStr);
}

string NotationConverter::infixToPrefix(string inStr) {
    Deque stack;
    reverse(inStr.begin(), inStr.end());
    Deque input = decodeInput(inStr);
    string output = "";

    while (!input.isEmpty()) {
        string token = input.popFront();

        if (!isOperator(token[0]) && token != "(" && token != ")") {
            output = token + " " + output;
        } else if (token == ")") {
            stack.pushRear(token);
        } else if (token == "(") {
            while (stack.getRear() != ")") {
                output = stack.popRear() + " " + output;
            }
            stack.popRear();
        } else {
            while (!stack.isEmpty() && getPrecedence(token[0]) <= getPrecedence(stack.getRear()[0])) {
                output = stack.popRear() + " " + output;
            }
            stack.pushRear(token);
        }
    }

    while (!stack.isEmpty()) {
        output = stack.popRear() + " " + output;
    }

    return output;
}

string NotationConverter::prefixToInfix(string inStr) {
    Deque stack;
    Deque input = decodeInput(inStr);

    while (!input.isEmpty()) {
        string token = input.popRear();

        if (!isOperator(token[0])) {
            stack.pushRear(token);
        } else {
            string operand1 = stack.popRear();
            string operand2 = stack.popRear();
            string infixExp = "(" + operand1 + " " + token + " " + operand2 + ")";
            stack.pushRear(infixExp);
        }
    }

    return formatExpression(stack.popRear());
}

string NotationConverter::prefixToPostfix(string inStr) {

    string infixStr = prefixToInfix(inStr);

    return infixToPostfix(infixStr);
}
