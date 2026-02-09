#include "ScrapList.h"

// Default constructor
ScrapList::ScrapList() : head(nullptr), tail(nullptr), size(0) {}

// Function to add scrap item to the list (prepending)
void ScrapList::addScrap(const std::string& scrapName) {
    ScrapNode* newScrap = new ScrapNode(scrapName); // Create new node
    if (head == nullptr) { // Checking for empty list
        head = tail = newScrap;
    }
    else {
        newScrap->next = head; // Adding to a non-empty list
        head = newScrap; // New node becomes the new head
    }
    ++size; // Increment the size
}

// Function to remove a scrap item by name from the list
void ScrapList::removeScrap(const std::string& scrapName) {
    // Check if the list is empty
    if (head == nullptr) {
        std::cout << "The scrap list is empty. Nothing to remove." << std::endl;
        return;  // Exit if the list is empty, nothing to remove
    }

    // Check if the scrap to remove is at the head of the list
    if (head->scrapName == scrapName) {
        // If the scrap is at the head, update the head pointer to the next node
        ScrapNode* temp = head;  // Store the current head to delete later
        head = head->next;       // Move head to the next node
        if (head == nullptr) {
            tail = nullptr;  // If the list becomes empty, set the tail to nullptr
        }
        delete temp;   // Free the memory of the old head node
        --size;         // Decrement the size of the list
        std::cout << "Removed " << scrapName << " from the scrap list." << std::endl;
        return;  // Exit after removal is complete
    }

    // If the scrap is not at the head, search through the rest of the list
    ScrapNode* current = head;
    while (current->next != nullptr) {
        // If the next node has the scrap to remove
        if (current->next->scrapName == scrapName) {
            // Remove the node by adjusting the 'next' pointer of the current node
            ScrapNode* temp = current->next;  // Store the node to delete
            current->next = current->next->next;  // Skip the node to remove
            if (current->next == nullptr) {
                tail = current;  // If the node removed was the last, update the tail pointer
            }
            delete temp;  // Free the memory of the removed node
            --size;  // Decrease the list size
            std::cout << "Removed " << scrapName << " from the scrap list." << std::endl;
            return;  // Exit after removal is complete
        }
        current = current->next;  // Move to the next node in the list
    }

    // If the scrap item was not found in the list
    std::cout << scrapName << " not found in the scrap list." << std::endl;
}

// Check if list is empty
bool ScrapList::isEmpty() const {
    return head == nullptr;
}

// Method to get the current size of the list
int ScrapList::getSize() const {
    return size;
}

// Function to read and print all scrap items
void ScrapList::listAllScraps() const {
    if (head == nullptr) {
        std::cout << "No scraps in the list." << std::endl;
        return;
    }

    ScrapNode* current = head; // Start from the head of the linked list
    // Iterate through the linked list until the end is reached
    while (current) {
        std::cout << "- " << current->scrapName << std::endl;
        current = current->next;
    }
}

// Find scrap in the list
bool ScrapList::findScrap(const std::string& scrapName) const {
    ScrapNode* current = head; // Start from the head of the list
    while (current) {
        if (current->scrapName == scrapName) {
            return true;  // Scrap found
        }
        current = current->next; // Move to the next node in the list
    }
    return false;  // Scrap not found
}

// Destructor
ScrapList::~ScrapList() {
    while (head != nullptr) {
        ScrapNode* temp = head;
        head = head->next;
        delete temp;
    }
}