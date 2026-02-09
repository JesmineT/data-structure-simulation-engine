#ifndef STACK_H
#define STACK_H
#include "CardList.h"

class Stack {
private:
    CardList cardList;

public:
    // Default Constructor for the Stack class
    Stack();

    // Pushes card with name and point to the stack
    void push(const std::string& name, int cost);

    // Pops card from the stack if it is not empty
    void pop();

    // Checks if the stack is empty
    bool isEmpty() const;

    // Get the size of the stack
    int getSize() const;

    // Method to print all the cards in the stack
    void printCards() const;

    // Returns the top card of the stack without removing it
    std::pair<std::string, int> peekCard() const;

    // Destructor
    ~Stack();
};
#endif
