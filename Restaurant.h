#ifndef RESTAURANT_H
#define RESTAURANT_H
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Table.h"
#include "WaitingArea.h"
#include "ServingHatch.h"
#include "Food.h"
#include "CustomerEntity.h"
#include "Enemy.h"
#include "RestaurantManager.h"
#include "StepTile.h"
#include "AudioManager.h"
#include "Stack.h"
#include "Scrap.h"

class Restaurant {
private:
    sf::Font font; // Font for displaying text
    sf::RectangleShape bagButton; // Shape for the bag button
    sf::Text bagButtonText; // Text for the bag button
    sf::RectangleShape apronButton; // Shape for the apron button
    sf::Text apronButtonText; // Text for the apron button
    sf::Vector2f apronButtonPosition; // Define the apronButton's position and size
    sf::Vector2f apronButtonSize;
    sf::Vector2f bagButtonPosition; // Define the bagButton's position and size
    sf::Vector2f bagButtonSize;

    // Various shopItem instances that can be used in the game
    SpeedBoostingKit speedBoostingKit;
    Boots boots;
    Heels heels;
    Butter butter;
    Axolotl axolotl;
    FortuneCat fortuneCat;
    FortunePig fortunePig;
    FortuneMask fortuneMask;
    ReputationBoostingKit reputationBoostingKit;
    Cigarettes cigarettes;
    Pearls pearls;
    WaterBottle waterBottle;

    // AudioManager instance to handle game sounds and music
    AudioManager audioManager;

    // The SFML RenderWindow object that represents the game window
    sf::RenderWindow window;

    // Pointer to keep track of currently selected customer
    CustomerEntity *selectedCustomer;

    // Pointer to keep track of currently selected food
    Food *selectedFood;

    // Pointer to keep track of currently selected table
    Table *selectedTable;

    // Represents the waiting area where customers wait to be seated
    WaitingArea waitingArea;

    // Represents the serving hatch where food is prepared and served to the customers
    ServingHatch servingHatch;

    // Food objects representing different food types: appetizer, main course, and dessert
    Food appetizer, mainCourse, dessert, champagne;

    // Vector for tables
    std::vector<Table> tables;

    // Stores pointers to different derived customer types, 
    // using the base class pointer (CustomerEntity*) to enable polymorphism at runtime.
    std::vector<CustomerEntity*> customers;

    // A pointer to the singleton Player object representing the player in the game
    Player *player;

    // Enemy object
    Enemy enemy;

    // RestaurantManager object
    RestaurantManager restaurantManager; 

    // Vector for the StepTiles
    std::vector<StepTile> stepTiles; // Vector to hold StepTile instances

    // Current level of the game
    int currentLevel;

    // Stack instance for managing cards
    Stack cardStack;

    // Pointer to the Shop class for managing item purchases
    Shop* shop;

public:
    // Overloaded Constructor with width and height as unsigned to prevent negative dimensions
    Restaurant(unsigned int width, unsigned int height, const std::string &title);

    // Main game loop
    void run();

    // Define this method to check if the player is within the StepTile boundaries, helping in pathing and movement restriction
    bool isWithinStepTileBoundaries(const sf::Vector2f& position) const;

    // Destructor
    ~Restaurant();

private: // Intended for internal use only, managing the restaurant's operations
    // Function to check if the player collides with any scrap and remove it
    void checkPlayerScrapCollision();

    // Checks if player collides with a customer
    void checkPlayerCustomerCollision();

    // Processes all events
    void processEvents();

    // Updates game state and elements each frame
    void update();

    // Updates game state and elements each frame
    bool checkCollision(const Player& player, const Enemy& enemy);

    // Renders the game elements on the screen
    void render();

    // Handles logic when the player is close to specific objects or characters
    void handlePlayerProximity();

    // Handles right-click interactions
    void handleRightClick(float mouseX, float mouseY);
};
#endif
