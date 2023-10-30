#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include "NotationConverterInterface.hpp"
#include "Deque.hpp"

class NotationConverter: public NotationConverterInterface {
private:
    bool isOperator(char ch);
    int getPrecedence(char ch);
    Deque decodeInput(string &inStr);

public:

    string formatExpression(const string & str);
    string preprocess(const string & str);
    string infixToPostfix(string inStr);
    string postfixToInfix(string inStr);
    string postfixToPrefix(string inStr);
    string infixToPrefix(string inStr);
    string prefixToInfix(string inStr);
    string prefixToPostfix(string inStr);


};

#endif