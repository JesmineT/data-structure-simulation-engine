#include "Hashtable.h"

// Default constructor, initializes the hash table
// creates an empty "item" for each index in the hashtable, setting itemName and itemDescription
// to "empty" and the next pointer to nullptr
// this initialization helps check whether an index is empty when adding new items
HashTable::HashTable() {
	for (int i = 0; i < SIZE; i++) {
		table[i] = new Item;
		table[i]->itemName = "Empty Data";
		table[i]->itemDescription = "Empty Data";
		table[i]->next = nullptr;
	}
}

// This method computes a hash value for the provided key (item name)
// Sums ASCII values of each char in the string to generate a hash
// Hash value is then taken to modulo "SIZE" to ensure it falls within bounds of array indices
int HashTable::HashFunction(std::string key) {
	int hash = 0;
	int index;

	for (int i = 0; i < key.length(); i++) {
		hash = hash + (int)key[i];
	}
	index = hash % SIZE;

	return index;
}

// This method adds new item to the hash table
// First computes the index using the Hash function
// If slot is empty, directly stores the item
// If slot not empty, creates a new 'item' and traverses the
// linked list at the end to append the new item
void HashTable::AddItem(std::string itemName, std::string itemDescription) {
	int index = HashFunction(itemName);

    if (table[index]->itemName == "Empty Data") {
        table[index]->itemName = itemName;
        table[index]->itemDescription = itemDescription;
    } else {
        Item* current = table[index];
        while (current->next != nullptr) {
            current = current->next;
        }
        Item* newItem = new Item{ itemName, itemDescription, nullptr};
        current->next = newItem;
    }
}

// This method counts how many times items are stored at a specific index in the hash table
// Returns 0 if slot is empty, otherwise, it counts the items in the linked list
int HashTable::countItemsAtIndex(int index) {
	int count = 0;
	Item* current = table[index];
	while (current != nullptr && current->itemName != "Empty Data") {
		++count;
		current = current->next;
	}
	return count;
}


// This method prints the contents of the entire hash table
// Iterators thru each index and uses NumberOfItemsInIndex 
// method to display name, description and count of items
void HashTable::PrintTable() {
	for (int i = 0; i < SIZE; ++i) {
		int itemCount = countItemsAtIndex(i);
		std::cout << "------------------------------------------------\n";
		std::cout << "Index: " << i << "\n";
		std::cout << table[i]->itemName << " | " << table[i]->itemDescription << "\n";
		std::cout << "Items at this index: " << itemCount << "\n";
		std::cout << "------------------------------------------------\n";
	}
}


// This method prints all items stored at a specific index
// Handles the case where index is empty by printing a corresponding message
// If items are present, traverses the linked list and prints each item's name and description
void HashTable::PrintItemsInIndex(int index) {
	Item* current = table[index];
	if (current->itemName == "empty") {
		std::cout << "Index " << index << " is empty.\n";
	}
	else {
		std::cout << "Items at index " << index << ":\n";
		while (current != nullptr) {
			std::cout << "------------------------------------------------\n";
			std::cout << "Item Name: " << current->itemName << "\n";
			std::cout << "Item Description: " << current->itemDescription << "\n";
			std::cout << "------------------------------------------------\n";
			current = current->next;
		}
	}
}

// This method searches for an item by name and prints its description if found
// It computes the index using the Hash fucnction and traverses the linked list at the index
// If the item name matches, it sets a flag and stores the description for later display
// if item not found, outputs a message indicating that the item wasnt found
void HashTable::FindDescription(std::string name) {
	int index = HashFunction(name);
	bool foundItemName = false;
	std::string description;

	Item* current = table[index];
	while (current != nullptr) {
		if (current->itemName == name) {
			foundItemName = true;
			description = current->itemDescription;
		}
		current = current->next;
	}
	if (foundItemName == true) {
		std::cout << "\n------------------------------------------------\nItem Description for " << name << ":\n------------------------------------------------\n" << description << " \n------------------------------------------------\n" << std::endl;
	}
	else {
		std::cout << name << "'s description was not found in the HashTable\n";
	}
}