#include "Deque.hpp"


// Constructor
Deque::Deque() : front(nullptr), rear(nullptr), size(0) {}

// Destructor
Deque::~Deque() {
    while (!isEmpty()) {
        popFront();
    }
}

// Check if the deque is empty
bool Deque::isEmpty() const {
    return size == 0;
}

// Get the current size of the deque
int Deque::getSize() const {
    return size;
}

// Add an element to the front of the deque
void Deque::pushFront(const std::string& data) {
    Node* newNode = new Node(data);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        newNode->next = front;
        front->prev = newNode;
        front = newNode;
    }
    size++;
}

// Add an element to the rear of the deque
void Deque::pushRear(const std::string& data) {
    Node* newNode = new Node(data);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        newNode->prev = rear;
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

// Remove and return an element from the front of the deque
std::string Deque::popFront() {
    if (isEmpty()) {
        throw std::runtime_error("Deque is empty");
    }
    Node* temp = front;
    std::string value = front->data;
    front = front->next;
    if (front) {
        front->prev = nullptr;
    } else {
        rear = nullptr;
    }
    delete temp;
    size--;
    return value;
}

// Remove and return an element from the rear of the deque
std::string Deque::popRear() {
    if (isEmpty()) {
        throw std::runtime_error("Deque is empty");
    }
    Node* temp = rear;
    std::string value = rear->data;
    rear = rear->prev;
    if (rear) {
        rear->next = nullptr;
    } else {
        front = nullptr;
    }
    delete temp;
    size--;
    return value;
}

// Get the element at the front of the deque
std::string Deque::getFront() const {
    if (isEmpty()) {
        throw std::runtime_error("Deque is empty");
    }
    return front->data;
}

// Get the element at the rear of the deque
std::string Deque::getRear() const {
    if (isEmpty()) {
        throw std::runtime_error("Deque is empty");
    }
    return rear->data;
}
