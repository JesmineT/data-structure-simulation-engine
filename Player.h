#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <fstream> // for file operations
#include "Enemy.h"
#include "Table.h"
#include "ItemList.h"
#include "ScrapList.h"

class ShopItem; // prevent ciruclar dependencies

class Player {
private:
    static Player *instance; // Static pointer to hold the single instance of Player

    std::string playerName;
    int playerReputation;
    sf::CircleShape circle;  // Circle shape for to represent the Player
    float fSpeed;
    bool hasFortuneCat; // Track if the player has purchased Fortune Cat
    bool hasFortunePig; // Track if the player has purchased Fortune Pig
    bool hasFortuneMask; // Track if the player has purchased Fortune Mask
    sf::Clock fortuneCatTimer; // Timer for reputation gain
    sf::Clock fortunePigTimer; // Timer for reputation gain
    sf::Clock fortuneMaskTimer; // Timer for reputation gain
    ItemList bag; // ItemList instance
    ScrapList apron; // ScrapList instance
    Enemy enemy; // Enemy instance

    // Private constructors to prevent instantiation
    Player();
    Player(std::string playerName, int playerReputation);

public:
    // Static method to access the single instance of Player
    static Player *getInstance();

    // Getter & Setter for playerName
    std::string getPlayerID();
    void setPlayerID(const std::string &playerName);

    // Getter & Setter for playerReputation
    int getPlayerReputation();
    void setPlayerReputation(int playerReputation);

    // Get player's circle
    sf::CircleShape getCircle();

    // Get position of the player
    sf::Vector2f getPosition();

    // Method to set the player's position
    void setPosition(const sf::Vector2f& position);

    // Draw the Player
    void draw(sf::RenderWindow& window);

    // Method for Click handling
    bool isClicked(float mouseX, float mouseY);

    // Method to get the global bounds of the player
    sf::FloatRect getGlobalBounds() const;

    // Method to get the player's speed
    float getPlayerSpeed() const;

    // Method to set the player's speed
    void setPlayerSpeed(float speed);

    // Friend extraction operator
    // Inputs data from an input stream (e.g., std::cin) to populate a Player object's fields.
    friend std::istream &operator>>(std::istream &aIstream, Player &aPlayer);

    // Setter for FortuneCat status
    void setHasFortuneCat(bool status);

    // Getter for FortuneCat status
    bool getHasFortuneCat() const;

    // Setter for FortunePig status
    void setHasFortunePig(bool status);

    // Getter for FortunePig status
    bool getHasFortunePig() const;

    // Setter for FortuneMask status
    void setHasFortuneMask(bool status);

    // Getter for FortuneMask status
    bool getHasFortuneMask() const;

    // Method to update reputation based on the Fortune Cat
    void updateReputationForFortuneCat();

    // Method to update reputation based on the Fortune Pig
    void updateReputationForFortunePig();

    // Method to update reputation based on the Fortune Mask
    void updateReputationForFortuneMask();

    // Method to add an item to the Bag
    void addItemToBag(const std::string& itemName, int itemPoints);

    // Method to add an item to the Bag by itemName
    void removeItemFromBag(const std::string& itemName);

    // Method to check if Bag is empty
    bool isBagEmpty() const;

    // Method to list all items in the Bag
    void listItemsInBag() const;
    
    // Method to check if an item is in the Bag
    bool IsItemInBag(const std::string& itemName);

    // Handles user input for interacting with the Bag
    void handleBagMenu();

    // Method to move left in the Bag
    void moveLeftInBag();

    // Method to move right in the Bag
    void moveRightInBag();

    // Method to activate an item in the Bag
    void activateItem();

    // Method to get the current item in the Bag
    void getCurrentItemInBag();

    // Method to check if an item is activated in the Bag
    bool isItemActivated(const std::string& itemName) const;

    // Method to add a scrap to the apron
    void addScrapToApron(const std::string& name);

    // Method to remove a scrap from the apron by scrapName
    void removeScrapFromApron(const std::string& scrapName);

    // Method to check if the apron is empty
    bool isApronEmpty() const;

    // Method to list all scraps in the apron
    void listScrapsInApron() const;

    // Method to find scrap in the apron
    bool findScrapFromApron(const std::string& scrapName) const;

    // Handles user input for interacting with the Apron
    void handleApronMenu();

    // Destructor
    ~Player();
};
#endif