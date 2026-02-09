#include "Player.h"
#include "ShopItem.h" // to prevent ciruclar dependencies

// Initialize the static member
Player* Player::instance = nullptr;

// Private default constructor
// Initializes both Player-specific attributes and those inherited from MainEntity
Player::Player()
    : playerName(""),
    playerReputation(0),
    fSpeed(0.5f),
    hasFortuneCat(false),
    hasFortunePig(false),
    hasFortuneMask(false),
    bag() {
    circle.setRadius(20);      // Set the radius of the player
    circle.setFillColor(sf::Color::Red);  // Set the player's color
    circle.setPosition(460, 150);  // Set initial position
}

// Private overloaded constructor
// Initializes the player with a given name and reputation
Player::Player(std::string name, int reputation) 
  : playerName(name),
    playerReputation(reputation),
    fSpeed(0.5f),
    hasFortuneCat(false),
    hasFortunePig(false),
    hasFortuneMask(false),
    bag() {
    circle.setRadius(20);       // Set the radius of the player
    circle.setFillColor(sf::Color::Red);  // Set the player's color
    circle.setPosition(460, 100);  // Set initial position
}

// Static method to access the single instance of Player
Player* Player::getInstance() {
    // Check if the instance is already created
    if (instance == nullptr) {
        instance = new Player(); // dynamic memory allocation (will remain in memory unless destructed)
    }
    // Log the address
    std::cout << "Player instance address: " << instance << std::endl;

    // Return the singleton instance
    return instance;
}

// Getter for playerName
std::string Player::getPlayerID() {
    return playerName;
}

// Setter for playerName
void Player::setPlayerID(const std::string& name) {
    playerName = name;
}

// Getter for playerReputation
int Player::getPlayerReputation() {
    return playerReputation;
}

// Setter for playerReputation
void Player::setPlayerReputation(int reputation) {
    playerReputation = reputation;
}

// Get player's circle
sf::CircleShape Player::getCircle() {
    return circle;
}

// Getter for player's position
sf::Vector2f Player::getPosition() {
    return circle.getPosition();
}

// Method to set the player's position
void Player::setPosition(const sf::Vector2f& position) {
    circle.setPosition(position); // Set the position of the circle
}

// Method to Draw the Player
void Player::draw(sf::RenderWindow& window) {
    window.draw(circle);
}

// Method for Click Handling
bool Player::isClicked(float mouseX, float mouseY) {
    sf::FloatRect bounds = circle.getGlobalBounds();
    return bounds.contains(mouseX, mouseY);
}

// Method to get the global bounds of the player
sf::FloatRect Player::getGlobalBounds() const {
    return circle.getGlobalBounds();
}

// Method to get the player's speed
float Player::getPlayerSpeed() const {
    return fSpeed;
}

// Method to set the player speed
void Player::setPlayerSpeed(float speed) {
    fSpeed = speed;
}

// Friend extraction operator
// Inputs data from an input stream (e.g., std::cin) to populate a Player object's fields.
std::istream& operator>>(std::istream& aIstream, Player& aPlayer) {
    std::cout << "Enter Player Name: ";
    aIstream >> aPlayer.playerName;
    return aIstream;
}

// Setter for FortuneCat status
void Player::setHasFortuneCat(bool status) {
    hasFortuneCat = status;
}

// Getter for FortuneCat status
bool Player::getHasFortuneCat() const {
    return hasFortuneCat;
}

// Setter for FortunePig status
void Player::setHasFortunePig(bool status) {
    hasFortunePig = status;
}

// Getter for FortunePig status
bool Player::getHasFortunePig() const {
    return hasFortunePig;
}

// Setter for FortuneMask status
void Player::setHasFortuneMask(bool status) {
    hasFortuneMask = status;
}

// Getter for FortuneMask status
bool Player::getHasFortuneMask() const {
    return hasFortuneMask;
}

// Method to update reputation based on the Fortune Cat
void Player::updateReputationForFortuneCat() {
    if (hasFortuneCat && IsItemInBag("Fortune Cat")) {
        // Check if 10 seconds have passed
        if (fortuneCatTimer.getElapsedTime().asSeconds() >= 10) {
            playerReputation += 5; // Gain reputation
            std::cout << "Fortune Cat: Gained +5 reputation points! Current reputation: " << playerReputation << "\n";
            fortuneCatTimer.restart(); // Restart the timer
        }
    }
}

// Method to update reputation based on the Fortune Pig
void Player::updateReputationForFortunePig() {
    if (hasFortunePig && IsItemInBag("Fortune Pig")) {
        // Check if 10 seconds have passed
        if (fortunePigTimer.getElapsedTime().asSeconds() >= 10) {
            playerReputation += 7; // Gain reputation
            std::cout << "Fortune Pig: Gained +7 reputation points! Current reputation: " << playerReputation << "\n";
            fortunePigTimer.restart(); // Restart the timer
        }
    }
}

// Method to update reputation based on the Fortune Mask
void Player::updateReputationForFortuneMask() {
    if (hasFortuneMask && IsItemInBag("Fortune Mask")) {
        // Check if 10 seconds have passed
        if (fortuneMaskTimer.getElapsedTime().asSeconds() >= 10) {
            playerReputation += 6; // Gain reputation
            std::cout << "Fortune Mask: Gained +6 reputation points! Current reputation: " << playerReputation << "\n";
            fortuneMaskTimer.restart(); // Restart the timer
        }
    }
}

// Method to add an item to the Bag
void Player::addItemToBag(const std::string& itemName, int itemCost) {
    bag.addItem(itemName, itemCost);
    std::cout << "Added item '" << itemName << "' of cost " << itemCost << " to the bag.\n";
}

// Method to remove an item to the Bag by itemName
void Player::removeItemFromBag(const std::string& itemName) {
    if (!bag.isEmpty()) {
        bag.removeItem(itemName);
    }
    else {
        std::cout << "Cannot remove item: The bag is already empty.\n";
    }
}

// Method to check if Bag is empty
bool Player::isBagEmpty() const {
    bool empty = bag.isEmpty();
    if (empty) {
        std::cout << "The bag is empty.\n";
    }
    else {
        std::cout << "The bag contains items.\n";
    }
    return empty;
}

// Method to list all items in the Bag
void Player::listItemsInBag() const {
    bag.listAllItems();
}

// Method to check if an item is in the Bag
bool Player::IsItemInBag(const std::string& itemName) {
    return bag.findItem(itemName);
}

// Handles user input for interacting with the Bag
void Player::handleBagMenu() {
    char choice; // Declare choice outside the loop
    bool exitBag = false; // Flag to check if we should exit the bag

    while (!exitBag) { // Loop until exit command is given
        std::cout << "Welcome to your bag!\n";
        std::cout << "Press 1 to list items in the bag.\n";
        std::cout << "Press 2 to exit the bag.\n";
        std::cout << "Press 3 to navigate left in the bag.\n";
        std::cout << "Press 4 to navigate right in the bag.\n";

        // Read the player's choice
        std::cin >> choice;

        if (choice == '1') {
            listItemsInBag();
        }
        else if (choice == '2') {
            std::cout << "Exiting the bag...\n";
            exitBag = true; // Set the flag to exit the loop
        }
        else if (choice == '3') {
            moveLeftInBag();
        }
        else if (choice == '4') {
            moveRightInBag();
        }
        else {
            std::cout << "Invalid choice. Please try again.\n"; // Handle invalid input
        }
    }
}

// Method to move left in the Bag
void Player::moveLeftInBag() {
    bag.moveLeft();
}

// Method to move right in the Bag
void Player::moveRightInBag() {
    bag.moveRight();
}

// Method to activate an item in the Bag
void Player::activateItem() {
    bag.activateItem();
}

// Method to get the current item in the Bag
void Player::getCurrentItemInBag() {
    bag.getCurrentItem();
}

// Method to check if an item is activated in the Bag
bool Player::isItemActivated(const std::string& itemName) const {
    // Check if the item exists in the bag
    if (bag.findItem(itemName)) {
        // Check if the item is currently activated
        return bag.getIsItemActivated();
    }
    return false; // Item not found or not activated
}


// Method to add a scrap to the apron
void Player::addScrapToApron(const std::string& scrapName) {
    apron.addScrap(scrapName);
    std::cout << "Added item '" << scrapName << "' to the apron.\n";
}

// Method to remove a scrap from the apron by scrapName
void Player::removeScrapFromApron(const std::string& scrapName) {
    if (!apron.isEmpty()) {
        apron.removeScrap(scrapName);
    }
    else {
        std::cout << "Cannot remove item: The apron is already empty.\n";
    }
}

// Method to check if the apron is empty
bool Player::isApronEmpty() const {
    bool empty = apron.isEmpty();
    if (empty) {
        std::cout << "The apron is empty.\n";
    }
    else {
        std::cout << "The apron contains items.\n";
    }
    return empty;
}

// Method to list all scraps in the apron
void Player::listScrapsInApron() const {
    apron.listAllScraps();
}

// Method to find scrap in the apron
bool Player::findScrapFromApron(const std::string& scrapName) const {
    return apron.findScrap(scrapName);
}


// Handles user input for interacting with the Apron
void Player::handleApronMenu() {
    char choice; // Declare choice outside the loop
    bool exitApron = false; // Flag to check if we should exit the apron menu

    while (!exitApron) { // Loop until exit command is given
        std::cout << "Welcome to your apron!\n";
        std::cout << "Press 1 to list scraps in the apron.\n";
        std::cout << "Press 2 to exit the apron menu.\n";

        // Read the player's choice
        std::cin >> choice;

        if (choice == '1') {
            listScrapsInApron();  // List all the scraps inside the apron
        }
        else if (choice == '2') {
            std::cout << "Exiting the apron menu...\n";
            exitApron = true; // Set the flag to exit the loop
        }
        else {
            std::cout << "Invalid choice. Please try again.\n"; // Handle invalid input
        }
    }
}

// Destructor
Player::~Player() {
    // Clean up the singleton instance
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

