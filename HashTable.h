#include <iostream>
#include <list>
#include <string>

class HashTable {

private:
	static const int SIZE = 10;

	struct Item {
		std::string itemName;
		std::string itemDescription;
		Item* next; // used for collision resolution (separate chaining)
	};

	// An array of pointers to item structures representing the hash table itself
	Item* table[SIZE];

public:
	// Default constructor
	HashTable();

	// Hash function to compute the index for a given key
	int HashFunction(std::string key);

	// Method to add items to the hash table
	void AddItem(std::string itemName, std::string itemDescription); //stores name of people and associates them w their fav drink
	
	// Counts the number of items at a specific index
	int countItemsAtIndex(int index);

	// Prints all items in the hash table
	void PrintTable();

	// Prints items stored at a specific index
	void PrintItemsInIndex(int index);

	// Finds and prints the description of an item given its name
	void FindDescription(std::string itemName);
};
