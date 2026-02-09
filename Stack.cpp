#include "Stack.h"

// Default Constructor for the Stack class
Stack::Stack() {}

// Pushes card with name and cost to the stack
void Stack::push(const std::string& name, int cost) {
    cardList.addCard(name, cost); // Call the CardList's method to add a card
}

// Pops card from the stack if it is not empty
void Stack::pop() {
    if (!isEmpty()) {
        cardList.removeCard();
    }
    else {
        std::cout << "Stack is empty. No cards to remove.\n";
    }
}

// Checks if the stack is empty
bool Stack::isEmpty() const { 
    return cardList.isEmpty();
}

// Get the size of the stack
int Stack::getSize() const {
    return cardList.getSize();
}

// Method to print all the cards in the stack
void Stack::printCards() const {
    cardList.listAllCards();
}

// Returns the top card of the stack without removing it
std::pair<std::string, int> Stack::peekCard() const {
    return cardList.peek();
}

// Destructor
Stack::~Stack() {}