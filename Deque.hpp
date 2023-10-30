//
// Created by Lenovo on 10/2/2023.
//

#ifndef PP2__NOTATION_CONVERTER__DEQUE_HPP
#define PP2__NOTATION_CONVERTER__DEQUE_HPP
#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>
using namespace std;

class Node {
public: string data;
    Node * next;
    Node * prev;

    Node(string data): data(data),
                       next(nullptr),
                       prev(nullptr) {}
};


class Deque {
private:
    Node* front;
    Node* rear;
    int size;

public:
    Deque();
    ~Deque();

    bool isEmpty() const;
    int getSize() const;
    void pushFront(const std::string& data);
    void pushRear(const std::string& data);
    std::string popFront();
    std::string popRear();
    std::string getFront() const;
    std::string getRear() const;
};

#endif //PP2__NOTATION_CONVERTER__DEQUE_HPP
