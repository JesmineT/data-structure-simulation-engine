#include "CardList.h"

// Default constructor
CardList::CardList() : head(nullptr), tail(nullptr), size(0) {}

// Add card to the list using prepend/stack's push behavior
void CardList::addCard(const std::string& name, int points) {
    CardNode* newCard = new CardNode(name, points); // Create new node
    if (head == nullptr) { // Checking for empty list
        head = tail = newCard;
    }
    else {
        newCard->next = head; // Adding to a non-empty list
        head = newCard; // New node becomes the new head
    }
    ++size; // Increment the size
}

// Remove from the head of the list
void CardList::removeCard() {
    if (isEmpty()) {
        throw std::out_of_range("The card list is empty"); // Use exception handling
    }

    CardNode* temp = head; // Store the current head
    head = head->next; // Move head to the next node
    if (head == nullptr) { // If the list is now empty
        tail = nullptr;
    }
    delete temp; // Free memory
    --size; // Decrement list size
}

// Check if the list is empty
bool CardList::isEmpty() const {
    return head == nullptr;
}

// Method to get the current size of the list
int CardList::getSize() const {
    return size;
}

// Method to read and print all cards
void CardList::listAllCards() const {
    if (head == nullptr) {
        std::cout << "No cards in the list." << std::endl;
        return;
    }

    CardNode* current = head; // Start from the head of the linked list
    // Iterate through the linked list until the end is reached
    while (current != nullptr) { // Continue until the current node is null
        std::cout << "- " << current->cardName << " (Points: " << current->cardPoints << ")" << std::endl;
        current = current->next; // Move to the next node in the linked list
    }
}

// Method to peek at the top card
std::pair<std::string, int> CardList::peek() const {
    if (head != nullptr) {
        return { head->cardName, head->cardPoints };  // Return the top card's details
    }
    return { "", 0 };  // Return an empty pair if the list is empty
}

// Destructor
CardList::~CardList() {
    while (head != nullptr) {
        CardNode* temp = head;
        head = head->next;
        delete temp;
    }
}