#ifndef SHOP_H
#define SHOP_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "CustomerEntity.h"
#include "Player.h"
#include "Enemy.h"
#include "Stack.h"
#include "ItemTree.h"
#include "ShopItem.h"
#include "ReputationBoostingKit.h"
#include "WaterBottle.h"
#include "FortuneCat.h"
#include "Pearls.h"
#include "Cigarettes.h"
#include "FortunePig.h"
#include "FortuneMask.h"
#include "SpeedBoostingKit.h"
#include "Boots.h"
#include "Butter.h"
#include "Heels.h"
#include "Axolotl.h"
#include "Hashtable.h"

class Shop {
private:
    sf::RenderWindow shopWindow; // Shop window
    std::vector<ShopItem*> shopItems; // List of shop items to be displayed on the Shop window
    HashTable hashTable; // Hashtable instance
    sf::Font font; // Font for displaying text
    Player* player; // Pointer to Player instance
    Enemy* enemy; // Pointer to Enemy instance
    CustomerEntity* customer; // Pointer to Customer instance
    Stack& cardStack; // Stack to hold actions
    bool cardClaimed; // Flag to check if card has claimed 
    int selectedItemIndex; // Index of the currently selected item
    ItemTree* reputationItemsTree; // First item tree for reputation items
    ItemTree* speedItemsTree; // Second item tree for speed items
    bool reputationItemsTreeDisplayed; // Flag to check if reputation items tree is displayed
    bool speedItemsTreeDisplayed; // Flag to check if the speed items tree is displayed
    sf::RectangleShape popButton; // Shape for the Pop button
    sf::Text popButtonText; // Text for the Pop button
    sf::RectangleShape bagButton;    // Shape for the Bag button
    sf::Text bagButtonText;          // Text for the Bag button
    sf::RectangleShape hashopediaButton; // Shape for the Hashopedia button
    sf::Text hashopediaButtonText;       // Text for the Hashopedia button
    sf::RectangleShape apronButton; // Shape for the apron button
    sf::Text apronButtonText;       // Text for the apron button

    // Private constructor to prevent instantiation
    Shop(Player* playerInstance, Enemy* enemyInstance, CustomerEntity* customerInstance, Stack& cardStackInstance);
    
    // Static pointer to a single instance of the Shop (for Singleton pattern)
    static Shop* instance;

public:
    // Singleton pattern to get the single instance of Shop
    static Shop* getInstance(Player* playerInstance, Enemy* enemyInstance, CustomerEntity* customerInstance, Stack& cardStackInstance);
    void openShop(); // Open the shop window and handle the shop loop
    void resetShop(); // Resets the shop window for a new session later
    void displayItems(); // Display all shop items with positions and properties
    void displayReputationItemsTree(); // Displays the tree of reputation-related items
    void displaySpeedItemsTree(); // Displays the tree of speed-related items
    void handleInput(); // Handles user input in the shop window (such as button clicks, keyboard clicks, item selection etc)
    void purchaseItem(int index); // Purchases an item based on the given index
    ItemTree* findNode(ItemTree* node, ShopItem* item); // Finds a node in the item tree for a specific item
    void buildReputationItemsTree(); // Builds the binary tree for reputation items
    void buildSpeedItemsTree(); // Builds the binary tree for speed items
    void createPopButton(); // Creates the "Pop" button 
    void createBagButton(); // Creates the "Bag" button 
    void createHashopediaButton(); // Creates the "Hashopedia" button 
    void createApronButton(); // Creates the "Apron" button 
    void addShopItem(ShopItem* newItem); // Adds a new item to the shop's item vector and stores its name and description in the hash table for quick lookup
    ~Shop(); // Destructor
};
#endif
