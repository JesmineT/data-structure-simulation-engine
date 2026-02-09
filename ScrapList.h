#ifndef SCRAPLIST_H
#define SCRAPLIST_H
#include <iostream>
#include <string>

class ScrapList {
private:
    // Struct representing each node in the linked list
    struct ScrapNode {
        std::string scrapName;  // The name of the scrap item
        ScrapNode* next;        // Pointer to the next node in the list

        // Constructor to initialize a ScrapNode with a scrap name
        ScrapNode(const std::string& name)
            : scrapName(name), next(nullptr) {}  // Initialize next to nullptr by default
    };

    ScrapNode* head;  // Pointer to the first node in the list (head of the linked list)
    ScrapNode* tail;  // Pointer to the last node in the list (tail of the linked list)
    int size;         // Tracks the number of scraps (nodes) in the list

public:
    // Default constructor
    ScrapList();

    // Function to add scrap to the list
    void addScrap(const std::string& scrapName);

    // Function to remove a scrap item by name from the list
    void removeScrap(const std::string& scrapName);

    // Check if list is empty
    bool isEmpty() const;

    // Method to get the current size of the list
    int getSize() const;

    // Method to print all scraps in the list
    void listAllScraps() const;

    // Method to find the scrap in the list by taking in the scrapName
    bool findScrap(const std::string& scrapName) const;

    // Destructor
    ~ScrapList();
};
#endif