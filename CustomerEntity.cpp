#include <iostream>
#include "CustomerEntity.h"

// Default Constructor
CustomerEntity::CustomerEntity()
  : fID(""),
    fPosition({0.0f, 0.0f}), // default values (will be overriden by the child classes)
    fMaxHappiness(1000), // default values (will be overriden by the child classes)
    fCurrentHappiness(200), // default values (will be overriden by the child classes)
    fReputationBoost(50), // default values (will be overriden by the child classes)
    fReputationAttack(50), // default values (will be overriden by the child classes)
    fMessage(""),
    seated(false),
    waitingForFood(false),
    assignedFood(nullptr),
    appetizerOrdered(false),
    mainCourseOrdered(false),
    dessertOrdered(false),
    champagneOrdered(false),
    seatedClock(),
    foodClock(),
    expectedFoodType(FoodType::None),
    finishedMeal(false),
    assignedTable(nullptr),
    messagePrinted(false),
    boostCount(0),
    attackCount(0) {
    circle.setRadius(20);
    circle.setFillColor(sf::Color::Black); // sample color (will be overriden by the child classes)
    circle.setPosition(fPosition.x, fPosition.y); // Initialize circle position
}

// Overloaded Constructor
CustomerEntity::CustomerEntity(std::string id, Position position, float radius, int maxHappiness, int currentHappiness, int reputationBoost, int reputationAttack)
  : fID(id),
    fPosition(position),
    fMaxHappiness(maxHappiness),
    fCurrentHappiness(currentHappiness),
    fReputationBoost(reputationBoost),
    fReputationAttack(reputationAttack),
    fMessage(""),
    seated(false),
    waitingForFood(false),
    assignedFood(nullptr),
    appetizerOrdered(false),
    mainCourseOrdered(false),
    dessertOrdered(false),
    champagneOrdered(false),
    seatedClock(),
    foodClock(),
    expectedFoodType(FoodType::None),
    finishedMeal(false),
    assignedTable(nullptr),
    messagePrinted(false),
    boostCount(0),
    attackCount(0) {
    circle.setRadius(radius);
    circle.setFillColor(sf::Color::Black); // sample color (will be overriden by the child classes)
    circle.setPosition(fPosition.x, fPosition.y); // Initialize circle position
}

// Getter for fID
std::string CustomerEntity::getCustomerID() {
    return fID;
}

// Setter for fID
void CustomerEntity::setCustomerID(std::string& id) {
    fID = id;
}

// Getter for fPosition
Position CustomerEntity::getPosition() {
    return fPosition;
}

// Setter for fPosition
void CustomerEntity::setPosition(float x, float y) {
    circle.setPosition(x, y);
    fPosition = { x, y };
}

// Getter for fMaxHappiness
int CustomerEntity::getMaxHappiness() {
    return fMaxHappiness;
}

// Setter for fMaxHappiness
void CustomerEntity::setMaxHappiness(int maxHappiness) {
    fMaxHappiness = maxHappiness;
}

// Getter for fCurrentHappiness
int CustomerEntity::getCurrentHappiness() {
    return fCurrentHappiness;
}

// Setter for fCurrentHappiness
void CustomerEntity::setCurrentHappiness(int currentHappiness) {
    fCurrentHappiness = currentHappiness;
}

// Getter for fReputationBoost
int CustomerEntity::getReputationBoost() {
    return fReputationBoost;
}

// Setter for fReputationBoost
void CustomerEntity::setReputationBoost(int reputationBoost) {
    fReputationBoost = reputationBoost;
}

// Getter for fReputationAttack
int CustomerEntity::getReputationAttack() {
    return fReputationAttack;
}

// Setter for fReputationAttack
void CustomerEntity::setReputationAttack(int reputationAttack) {
    fReputationAttack = reputationAttack;
}

// Getter for fMessage
std::string CustomerEntity::getMessage() {
    return fMessage;
}

// Setter for fMessage
void CustomerEntity::setMessage(std::string message) {
    fMessage = std::move(message);
}

// Getter for seated status
bool CustomerEntity::isSeated() {
    return seated;
}

// Setter for seated status
void CustomerEntity::setSeated(bool status) {
    seated = status;
    if (status) {
        seatedClock.restart();
    }
}

// Status if Customer has finished their meal
bool CustomerEntity::hasFinishedMeal() {
    return finishedMeal;
}

// Method to Draw the Customer
void CustomerEntity::draw(sf::RenderWindow& window) {
    window.draw(circle);
}

// Method for Click Handling
bool CustomerEntity::isClicked(float mouseX, float mouseY) {
    sf::FloatRect bounds = circle.getGlobalBounds();
    return bounds.contains(mouseX, mouseY);
}

// Get the Radius of the Customer
// to position the selected Customer's location to the middle of the selected table upon seated
float CustomerEntity::getRadius() const {
    return circle.getRadius();
}

// Method to Boost Player's Reputation
void CustomerEntity::boostPlayerReputation() {
    Player* player = Player::getInstance();  // Get the singleton instance of Player

    if (player) {
        int currentReputation = player->getPlayerReputation();
        player->setPlayerReputation(currentReputation + fReputationBoost);  // Increase reputation
        boostCount++;
        std::cout << "Customer " << fID << " boosted player reputation by " << fReputationBoost << std::endl;
        std::cout << "\n";
    }
    else {
        std::cerr << "Error: Unable to access Player instance.\n" << std::endl;
    }
}

// Method to Attack Player's Reputation
void CustomerEntity::attackPlayerReputation() {
    Player* player = Player::getInstance();  // Get the singleton instance of Player

    if (player) {
        int currentReputation = player->getPlayerReputation();
        player->setPlayerReputation(currentReputation - fReputationAttack);  // Decrease reputation
        attackCount++;
        std::cout << "Customer " << fID << " attacked player reputation by " << fReputationAttack << std::endl;
        std::cout << "\n";
    }
    else {
        std::cerr << "Error: Unable to access Player instance.\n" << std::endl;
    }
}

// This method assigns the specified table to the customer, 
// tracking which table they are seated at
void CustomerEntity::seat(Table* table) {
    assignedTable = table; // Assign the given table to the customer's assignedTable field pointer
}

// Method to order an appetizer
void CustomerEntity::orderAppetizer() {
    std::cout << fID << " has ordered an appetizer!\n" << std::endl;
    waitingForFood = true;
    appetizerOrdered = true; // Appetizer is ordered
    expectedFoodType = FoodType::Appetizer; // Set expectedFoodType to be Appetizer
    foodClock.restart(); // Start the timer for the appetizer delivery
}

// Method to order a main course
void CustomerEntity::orderMainCourse() {
    std::cout << fID << " has ordered the main course!\n" << std::endl;
    waitingForFood = true;
    mainCourseOrdered = true; // Main Course is ordered
    expectedFoodType = FoodType::MainCourse; // Set expectedFoodType to be Main Course
    foodClock.restart(); // Start the timer for the main course delivery
}

// Method to order a dessert
void CustomerEntity::orderDessert() {
    std::cout << fID << " has ordered dessert!\n" << std::endl;
    waitingForFood = true;
    dessertOrdered = true; // Dessert is ordered
    expectedFoodType = FoodType::Dessert; // Set expectedFoodType to be Dessert
    foodClock.restart(); // Start the timer for the dessert delivery
}

// Method to order a champagne
void CustomerEntity::orderChampagne() {
    std::cout << fID << " has ordered champagne!\n" << std::endl;
    waitingForFood = true;
    champagneOrdered = true; // Champagne is ordered
    expectedFoodType = FoodType::Champagne; // Set expectedFoodType to be Champagne
    foodClock.restart(); // Start the timer for the champagne delivery
}

// Method to call after customer is done with all the services 
void CustomerEntity::finishMeal() {
    std::cout << fID << " has finished their meal!\n" << std::endl;

    finishedMeal = true;  // Mark the meal as finished

    // Reset the table's availability
    if (assignedTable) {
        assignedTable->setAvailability(true); // Set table as available
    }
    else {
        std::cout << "Pointer is null " << std::endl;
    }

    // Clear the table
    seated = false;  // Mark the customer as not seated
    assignedFood = nullptr;  // Clear the assigned food
    setPosition(-1000, -1000);  // Move the customer off-screen 
}

// Method that returns a string with current fields of the Customer
std::string CustomerEntity::PrintStat() {
    // Create an ostringstream object to accumulate the formatted data.
    // Append each field of the CustomerEntity object to the string stream.
    std::ostringstream ss;
    ss << "Customer ID: " << fID << "\n"
        << "Position: (" << fPosition.x << ", " << fPosition.y << ")\n"
        << "Max Happiness: " << fMaxHappiness << "\n"
        << "Current Happiness: " << fCurrentHappiness << "\n"
        << "Reputation Boost Threshold: " << fReputationBoost << "\n"
        << "Reputation Attack Threshold: " << fReputationAttack << "\n"
        << "Message: " << fMessage << "\n";
    // Convert the ostringstream content to a string and return it.
    return ss.str();
}

// Method to get the global bounds of the customer
sf::FloatRect CustomerEntity::getGlobalBounds() const {
    return circle.getGlobalBounds();
}

// Method to reset the message printed status
void CustomerEntity::resetMessageStatus() {
    messagePrinted = false;
}

// Getter for messagePrinted status
bool CustomerEntity::isMessagePrinted() const {
    return messagePrinted;
}

// Setter for messagePrinted status
void CustomerEntity::setMessagePrinted(bool status) {
    messagePrinted = status;
}

// Getter for boostCount
int CustomerEntity::getBoostCount() const {
    return boostCount;
}

// Getter for attackCount
int CustomerEntity::getAttackCount() const {
    return attackCount;
}

// Friend operator overload for insertion | Output stream
// This operator is used to print the contents of a CustomerEntity object to an output stream (cout).
// It utilizes the PrintStat() method of CustomerEntity to provide a formatted, readable output of the object's data.
std::ostream& operator<<(std::ostream& aOstream, CustomerEntity& aCustomerEntity) {
    // Call the PrintStat() method of the CustomerEntity object.
    // This method returns a string or formatted data that represents the CustomerEntity's current stats.
    // The returned value is inserted into the output stream (aOstream).
    aOstream << aCustomerEntity.PrintStat();

    // Return the updated output stream, allowing chaining of << operators.
    return aOstream;
}

// Friend operator overload for extraction | Input stream
// This operator is used to parse and process input commands from an input stream, modifying the state of a CustomerEntity object based on the commands.
// It reads the `fMessage` field from the CustomerEntity object, contain <command> <value>
// The function processes these commands to update the customer's happiness and reputation accordingly.
std::istream &operator>>(std::istream &aIstream, CustomerEntity &aCustomerEntity) {
    std::string message = aCustomerEntity.getMessage();

    if (!message.empty()) {
        std::istringstream messageStream(message); // Create a string stream to parse the message
        std::string command; // Command extracted from the stream
        int value; // Value associated with the command

        // Extract command and value from the message
        while (messageStream >> command) { // Extract command from the stream
            // Attempt to read the next part of the stream as an integer value
            if (!(messageStream >> value)) {
                std::cerr << "Error parsing value for command: " << command << std::endl; // Error if value parsing fails
                std::cout << "\n";
                return aIstream; // Return the stream in case of parsing error
            }
            // Check if the value is negative
            if (value < 0) {
                std::cerr << "Error: Value cannot be negative for command: " << command << std::endl; // Error if value is negative
                std::cout << "\n";
                return aIstream; // Return the stream in case of invalid value
            }
            // Process commands based on the extracted command string
            if (command == "IncreaseCurrentHappiness") {
                aCustomerEntity.setCurrentHappiness(aCustomerEntity.getCurrentHappiness() + value); // Increase customer's happiness
                std::cout << "Increased " << aCustomerEntity.getCustomerID() << "'s happiness by " << value << std::endl;
                std::cout << "\n";
                aCustomerEntity.boostPlayerReputation(); // Update player's reputation
            }
            else if (command == "DecreaseCurrentHappiness") {
                aCustomerEntity.setCurrentHappiness(aCustomerEntity.getCurrentHappiness() - value); // Decrease customer's happiness
                std::cout << "Decreased " << aCustomerEntity.getCustomerID() << "'s happiness by " << value << std::endl;
                std::cout << "\n";
                aCustomerEntity.attackPlayerReputation(); // Update player's reputation
            }
            else {
                std::cerr << "Unknown command: " << command << std::endl; // Error for unknown commands
                std::cout << "\n";
            }
        }
    }
    else {
        std::cerr << "Message invalid or contains no commands\n" << std::endl; // Error if the message is empty or invalid
    }
    return aIstream;
}

// Destructor
CustomerEntity::~CustomerEntity() {
}

