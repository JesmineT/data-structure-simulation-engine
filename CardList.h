#ifndef CARDLIST_H
#define CARDLIST_H
#include <iostream>

class CardList {
private:
    // Struct representing each node in the linked list
    struct CardNode {
        std::string cardName; // The name of the card
        int cardPoints; // The points associated with the card
        CardNode* next; // Pointer to the next node in the list

        // Constructor to initialize a CardNode with the card name and points
        CardNode(const std::string& name, int points) 
            : cardName(name), cardPoints(points), next(nullptr) {} // Initialize next to nullptr by default
    };

    CardNode* head;  // Pointer to the first node in the list (head of the linked list)
    CardNode* tail;  // Pointer to the last node in the list (tail of the linked list)
    int size;        // Tracks the number of cards (nodes) in the list

public:
    // Default constructor 
    CardList();

    // Add card to the list
    void addCard(const std::string& name, int points);

    // Remove card from the list
    void removeCard();

    // Check if the list is empty
    bool isEmpty() const;

    // Method to get the current size of the list
    int getSize() const;

    // Method to print all cards in the list
    void listAllCards() const;

    // Method to peek at the top card
    std::pair<std::string, int> peek() const;
    
    // Destructor
    ~CardList();
};
#endif