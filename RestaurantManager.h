#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H
#include <vector>
#include <conio.h>
#include "CustomerEntity.h"
#include "VIPCustomer.h"
#include "SeniorCustomer.h"
#include "PrincessCustomer.h"
#include "Player.h"
#include "Report.h"
#include <SFML/System/Clock.hpp>
#include "Shop.h"
#include "Scrap.h"

class RestaurantManager {
private:
    std::vector<Scrap> scraps; // Vector to hold scrap objects, representing various discarded items in the restaurant
    
    std::vector<CustomerEntity*> customers; // Vector to store pointers to customers present in the level
    // Polymorphism is demonstrated here: the vector holds pointers to base class type CustomerEntity, 
    // but can point to objects of derived classes like SeniorCustomer, VIPCustomer, PrincessCustomer etc.

    Player* player; // Pointer to the player instance, used to manage player interactions and state
    Enemy enemy; // Instance of the enemy, initialized in each level
    int currentLevel; // Integer to track the current level of the game
    sf::Clock enemySpawnClock; // Clock to track time since level start to determine when to spawn the enemy
    bool enemySpawned; // Boolean to track if the enemy has already been spawned in the current level
    Report* currentReport; // Pointer to a Report object, used to record player and customer stats for each level

public:
    // Default constructor
    RestaurantManager();

    // Method to initialize level 1
    void initializeLevel1();

    // Method to initialize level 2
    void initializeLevel2();

    // Method to initialize level 3
    void initializeLevel3();

    // Getter for the customer list
    const std::vector<CustomerEntity*>& getCustomers() const;

    // Getter for the player instance
    Player* getPlayer() const;

    // Getter for the enemy instance
    const Enemy& getEnemy() const;

    // Getter for the scraps vector, allowing external access to scrap objects
    std::vector<Scrap>& getScraps();

    // Getter for checking if the enemy has been spawned
    bool isEnemySpawned() const;

    // Updates the game state, spawns the enemy if 10 seconds have passed
    void update();

    // Check if all customers have finished their meals
    bool allCustomersFinished(std::vector<CustomerEntity*>& customers);

    // Checks if the level is complete and displays/saves report if completed
    void checkLevelCompletion(sf::RenderWindow& window, std::vector<CustomerEntity*>& customers);

    // Checks if the level is complete by verifying all customers have finished meals
    bool isLevelComplete();

    // Sets up a specific level, clearing old data and initializing a new report and level setup
    void setCurrentLevel(int level);

    // Destructor
    ~RestaurantManager();
};
#endif