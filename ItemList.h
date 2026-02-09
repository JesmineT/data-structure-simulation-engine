#ifndef ITEMLIST_H
#define ITEMLIST_H
#include <string>
#include <iostream>

class ItemList {
private:
    // Struct representing each node in the doubly linked list
    struct ItemNode {
        std::string itemName; // Name of the item
        int itemCost; // Name of the item
        ItemNode* next; // Pointer to the next node in the list
        ItemNode* prev; // Pointer to the previous node in the list

        // Constructor to initialize the node with item name and cost
        ItemNode(const std::string& name, int cost)
            : itemName(name), itemCost(cost), next(nullptr), prev(nullptr) {}
    };
    ItemNode* head; // Pointer to the first node in the list
    ItemNode* tail; // Pointer to the last node in the list
    int size; // Number of items in the list
    ItemNode* current; // Pointer to track the current item
    bool isItemActivated = false; // Boolean flag to track whether an item is activated
     
public:
    // Default constructor
    ItemList();

    // Add a new item to the list with a name and cost
    void addItem(const std::string& name, int cost);

    // Remove an item from the list by its name
    void removeItem(const std::string& itemName);

    // Check if the list is empty
    bool isEmpty() const;

    // Get the current size of the list
    int getSize() const;

    // Print all items in the list
    void listAllItems() const;

    // Check if a particular item exists in the list
    bool findItem(const std::string& itemName) const;

    // Display the details of the current item
    void getCurrentItem() const;

    // Move the current pointer to the previous item in the list
    void moveLeft();

    // Move the current pointer to the next item in the list
    void moveRight();

    // Getter & Setter for item activation status
    bool getIsItemActivated() const;
    void setIsItemActivated(bool status);

    // Function to activate the current item
    void activateItem();
    
    // Prompt the user to activate the current item
    void promptActivateItem();

    // Remove the current item from the list
    void removeCurrentItem();

    // Prompt the user to remove the current item
    void promptRemoveCurrentItem();

    // Destructor 
    ~ItemList();
};
#endif
