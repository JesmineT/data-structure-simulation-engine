#include "ItemList.h"

// Default constructor
ItemList::ItemList() : head(nullptr), tail(nullptr), size(0), current(nullptr), isItemActivated(false) {}

// Add a new item to the list by prepending it (adding at the front)
void ItemList::addItem(const std::string& name, int cost) {
    ItemNode* newItem = new ItemNode(name, cost); // Create new node

    // If the list is empty, the new item is both the head and tail
    if (head == nullptr) {
        head = tail = newItem;
        current = head;  // Set current to the first item
    }
    else {
        // If the list is not empty, insert the new item at the front
        newItem->next = head; // New node points to current head
        head->prev = newItem; // Current head points back to new node
        head = newItem; // New node becomes the new head
    }
    ++size; // Increment the size of the list
}

// Remove an item from the list by its name
void ItemList::removeItem(const std::string& itemName) {
    ItemNode* current = head;

    // Traverse the linked list to find the item with the specified name
    while (current != nullptr) {
        if (current->itemName == itemName) {
            // Found the item, now remove it and break out of the loop
            if (current->prev != nullptr) {
                current->prev->next = current->next; // Update previous node's next pointer
            }
            else {
                // Update head if removing the first item node
                head = current->next;
            }

            if (current->next != nullptr) {
                current->next->prev = current->prev; // Update next node's prev pointer
            }
            else {
                // Update tail if removing the last item node
                tail = current->prev;
            }

            delete current; // Free memory
            --size; // Decrement list size
            std::cout << "Removed item: " << itemName << std::endl;
            return; // Exit after removing the first occurrence
        }
        current = current->next; // Move to the next node
    }
    std::cout << "Item not found: " << itemName << std::endl;
}

// Check if the list is empty
bool ItemList::isEmpty() const {
    return size == 0; 
}

// Get the size of the list
int ItemList::getSize() const {
    return size; 
}

// Function to read and print all items
void ItemList::listAllItems() const {
    ItemNode* current = head; // Start from the head of the linked list
    std::cout << "Items:" << std::endl;

    // Iterate through the linked list until the end is reached
    while (current != nullptr) { // Continue until the current node is null
        // Print the item name and level of the current node
        std::cout << "- " << current->itemName << " (Cost " << current->itemCost << ")" << std::endl;
        current = current->next; // Move to the next node in the linked list
    }
}

// Check if an item with a specific name exists in the list
bool ItemList::findItem(const std::string& itemName) const {
    ItemNode* current = head; // Start from the head of the list
    while (current != nullptr) {
        if (current->itemName == itemName) {
            return true; // Item found
        }
        current = current->next; // Move to the next node
    }
    return false; // Item not found
}

// Function to print the current item's details
void ItemList::getCurrentItem() const {
    if (current != nullptr) {
        std::cout << current->itemName << " (Cost: " << current->itemCost << ")" << std::endl;
    }
    else {
        std::cout << "No current item selected." << std::endl;
    }
}

// Move the current pointer to the previous item in the list
void ItemList::moveLeft() {
    if (current == nullptr) {
        std::cout << "The list is empty or no current item selected." << std::endl;
        return;
    }
    if (current->prev != nullptr) {
        current = current->prev; // Move to the previous node
    }
    else {
        std::cout << "Already at the beginning of the list." << std::endl;
    }    
    getCurrentItem();
    promptRemoveCurrentItem();
    promptActivateItem();
}

// Move the current pointer to the next item in the list
void ItemList::moveRight() {
    if (current == nullptr) {
        std::cout << "The list is empty or no current item selected." << std::endl;
        return;
    }
    if (current->next != nullptr) {
        current = current->next; // Move to the next node
    }
    else {
        std::cout << "Already at the end of the list." << std::endl;
    }
    getCurrentItem();
    promptRemoveCurrentItem();
    promptActivateItem();
}

// Getter for item activation status
bool ItemList::getIsItemActivated() const {
    return isItemActivated;
}

// Setter for item activation status
void ItemList::setIsItemActivated(bool status) {
    isItemActivated = status;
}

// Activate the current item
void ItemList::activateItem() {
    if (current != nullptr) {
        isItemActivated = true;  // Set the current item's activation status to true
        std::cout << "Activated item: " << current->itemName << std::endl;
    }
    else {
        std::cout << "No current item to activate." << std::endl;
    }
}

// Function to prompt user if they want to activate the item
void ItemList::promptActivateItem() {
    char choice;
    std::cout << "Do you want to activate this item? (y/n): ";
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        activateItem();
    }
    else if (choice == 'n' || choice == 'N') {
        return; // Exit the function early if the user chooses not to activate
    }
    else {
        std::cout << "Invalid choice. Please enter 'y' or 'n'." << std::endl;
        promptActivateItem(); // Recursively call to prompt again if the input is invalid
    }
}

// Remove the current item from the list
void ItemList::removeCurrentItem() {
    if (current == nullptr) {
        std::cout << "No current item to remove." << std::endl;
        return;
    }
     
    ItemNode* temp = current; // Store the current item in a temporary pointer

    // If there's a previous item, set it as the new current item.
    if (current->prev != nullptr) {
        current = current->prev;
        current->next = temp->next;  // Update the previous item to point to the next item.
    }
    else {
        // If the current item is the first item, update the head.
        head = current->next;
        if (head != nullptr) {
            head->prev = nullptr;  // Make sure the head points back to nullptr.
        }
        current = head;
    }

    // If there's a next item, make sure it points back to the previous item.
    if (temp->next != nullptr) {
        temp->next->prev = temp->prev;
    }
    else {
        // If the current item is the last one, update the tail.
        tail = temp->prev;
    }
    delete temp;  // Free memory
    --size;  // Decrement list size
    std::cout << "Removed the current item." << std::endl;
}

// Prompt the user to remove the current item
void ItemList::promptRemoveCurrentItem() {
    char choice;
    std::cout << "Do you want to remove this item? (y/n): ";
    std::cin >> choice;

    if (choice == 'y' || choice == 'Y') {
        removeCurrentItem();
    }
    else if (choice == 'n' || choice == 'N') {
        return;  // Exit the function early if the user chooses not to remove
    }
    else {
        std::cout << "Invalid choice. Please enter 'y' or 'n'." << std::endl;
        promptRemoveCurrentItem();  // Recursively call to prompt again if the input is invalid
    }
}

// Destructor
ItemList::~ItemList() {
    while (head != nullptr) {
        ItemNode* temp = head;
        head = head->next;
        delete temp;
    }
}