#include "RestaurantManager.h"

// Default constructor
RestaurantManager::RestaurantManager()
    : player(nullptr),
    enemySpawned(false),
    currentLevel(1),
    currentReport(nullptr) {
    setCurrentLevel(currentLevel); // Initialize the first level
}

// Initializes the first level with a fixed player reputation and specific customers and scraps
void RestaurantManager::initializeLevel1() {
    player = Player::getInstance(); // Singleton instance of player
    player->setPlayerReputation(99);  // Set fixed reputation for level 1
    
    // Adding instances of derived classes (SeniorCustomer) to the common CustomerEntity* vector demonstrates inheritance.
    // The CustomerEntity class is the base class, and all customer types inherit from it. 
    // RestaurantManager does not need to know the specific types of customers, only that they are of type CustomerEntity.
    customers.push_back(new SeniorCustomer("Senior Steven", { 1350, 605 })); // Add a customer
    // This customer is derived from CustomerEntity, but RestaurantManager uses the base class pointer type, 
    // enabling polymorphism when interacting with different customer types.

    enemy = Enemy(); // Initialize the enemy for this level

    // Add scrap objects with specific positions
    scraps.push_back(Scrap("Wooden Plank", { 1000, 410 }));
    scraps.push_back(Scrap("Chipped Plate", { 700, 230 }));
}

// Initializes the second level with specific customers and scrap objects
void RestaurantManager::initializeLevel2() {
    // Adding instances of derived classes (VIPCustomer, SeniorCustomer) to the customer list demonstrates inheritance.
    // Again, we add different types of customers, but the RestaurantManager doesn't need to know the specific subclass.
    customers.push_back(new VIPCustomer("VIP Alice", { 1250, 605 }));
    customers.push_back(new SeniorCustomer("Senior Lala", { 1300, 605 }));
    // These customers are all derived from CustomerEntity, but RestaurantManager uses the base class pointer type, 
    // enabling polymorphism when interacting with different customer types.
    
    // Add scrap objects for this level
    scraps.push_back(Scrap("Torn Menu", { 500, 410 }));
    scraps.push_back(Scrap("Dented Cooking Pot", { 650, 230 }));
    scraps.push_back(Scrap("Bent Fork", { 600, 550 }));

    enemy = Enemy(); // Initialize enemy for level 2
}

// Initializes the third level with multiple types of customers and scrap objects
void RestaurantManager::initializeLevel3() {
    // Adding instances of different derived classes (SeniorCustomer, PrincessCustomer, VIPCustomer) 
    // to the customer list demonstrates inheritance. Each of these customers is of type CustomerEntity, 
    // but their behaviors may differ depending on the specific subclass.
    customers.push_back(new SeniorCustomer("Senior Steven", { 1350, 605 }));
    customers.push_back(new PrincessCustomer("Princess Babygirl", { 1300, 605 }));
    customers.push_back(new VIPCustomer("VIP Sam", { 1250, 605 }));
    // These customers are all derived from CustomerEntity, but RestaurantManager uses the base class pointer type, 
    // enabling polymorphism when interacting with different customer types.
    
    // Add scrap objects for this level
    scraps.push_back(Scrap("Raggedy Tablecloth", { 850, 210 }));
    scraps.push_back(Scrap("Broken Salt Shaker", { 260, 310 }));

    enemy = Enemy(); // Initialize enemy for level 3
}

// Getter for the customer list
const std::vector<CustomerEntity*>& RestaurantManager::getCustomers() const {
    return customers; // Returns the vector of pointers to CustomerEntity (polymorphism is still applicable)
}

// Getter for the player instance
Player* RestaurantManager::getPlayer() const {
    return player;
}

// Getter for the enemy instance
const Enemy& RestaurantManager::getEnemy() const {
    return enemy;
}

// Getter for the scraps vector, allowing external access to scrap objects
std::vector<Scrap>& RestaurantManager::getScraps() {
    return scraps;
}

// Getter for checking if the enemy has been spawned
bool RestaurantManager::isEnemySpawned() const {
    return enemySpawned;
}

// Updates the game state, spawns the enemy if 10 seconds have passed
void RestaurantManager::update() {
    sf::Time elapsed = enemySpawnClock.getElapsedTime(); // Time since the clock started
    if (elapsed.asSeconds() > 10.0f && !enemySpawned) { // Check if 10 seconds have passed
        enemySpawned = true; // Set spawn status to true
        std::cout << "Enemy has spawned!" << std::endl;
    }
}

// Checks if all customers have finished their meals
bool RestaurantManager::allCustomersFinished(std::vector<CustomerEntity*>& customers) {
    for (auto& customer : customers) {
        if (!customer->hasFinishedMeal()) {  // If any customer hasn't finished, the check fails
            return false;
        }
    }
    return true; // All customers have finished
    // This method demonstrates polymorphism: the call to hasFinishedMeal() will invoke the overridden version
    // in the specific customer class, like SeniorCustomer, VIPCustomer, etc.
}

// Checks if the level is complete and displays/saves report if completed
void RestaurantManager::checkLevelCompletion(sf::RenderWindow& window, std::vector<CustomerEntity*>& customers) {
    if (allCustomersFinished(customers)) { // If all customers have finished meals
        std::cout << "Congratulations! You completed the game." << std::endl;

        // Collect happiness metrics from each customer for the report
        for (const auto& customer : customers) {
            int boostCount = customer->getBoostCount(); // Obtain boost count from customer
            int attackCount = customer->getAttackCount(); // Obtain attack count from customer
            // These functions are polymorphic: the appropriate version is called based on the customer's actual type
            // even though all customers are treated as pointers to the base class CustomerEntity.
            
            // Add customer happiness metrics to the report
            currentReport->addCustomerHappiness(
                customer->getCustomerID(),
                customer->getCurrentHappiness(),
                customer->getMaxHappiness(),
                customer->getReputationBoost(),
                boostCount,
                customer->getReputationAttack(),
                attackCount
            );
        }

        // Set the player's final reputation in the report
        currentReport->setFinalPlayerReputation(player->getPlayerReputation());

        // Display and save the report
        currentReport->displayReport();
        currentReport->saveReportToFile();

        std::cout << "Press any key to continue..." << std::endl; // Prompt for user input
        std::cin.ignore(); // Wait for user to press a key
        std::cin.get(); // Further wait for any key press
    }
    // The loop through customers still relies on polymorphism, calling customer-specific functions
    // like getBoostCount, getAttackCount, and getReputationBoost/Attack for each derived customer.
}

// Checks if the level is complete by verifying all customers have finished meals
bool RestaurantManager::isLevelComplete() {
    return allCustomersFinished(customers);
}

// Sets up a specific level, clearing old data and initializing a new report and level setup
void RestaurantManager::setCurrentLevel(int level) {
    // Clear existing customers if any
    for (auto customer : customers) {
        delete customer;
    }
    customers.clear();

    // Delete the old report and create a new one
    if (currentReport != nullptr) {
        delete currentReport;
    }
    currentReport = new Report("Level_" + std::to_string(level)); // New report for the level

    currentLevel = level; // Update current level

    // Initialize the level
    if (level == 1) {
        initializeLevel1();
    }
    else if (level == 2) {
        initializeLevel2();
    }
    else if (level == 3) {
        initializeLevel3();
    }
}

// Destructor
RestaurantManager::~RestaurantManager() {
    delete currentReport; // Clean up the report memory
}