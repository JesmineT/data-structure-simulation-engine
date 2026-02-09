#include "Food.h"
#include "CustomerEntity.h" // Included here instead to prevent circular dependencies

// Load texture based on FoodType
void Food::loadTexture(FoodType type) {
    switch (type) {
    case FoodType::Appetizer:
        if (!appetizerTexture.loadFromFile("appetizer.png")) {
            std::cerr << "Error loading appetizer texture!" << std::endl;
        }
        foodSprite.setTexture(appetizerTexture);
        break;
    case FoodType::MainCourse:
        if (!mainCourseTexture.loadFromFile("maincourse.png")) {
            std::cerr << "Error loading main course texture!" << std::endl;
        }
        foodSprite.setTexture(mainCourseTexture);
        break;
    case FoodType::Dessert:
        if (!dessertTexture.loadFromFile("dessert.png")) {
            std::cerr << "Error loading dessert texture!" << std::endl;
        }
        foodSprite.setTexture(dessertTexture);
        break;

    case FoodType::Champagne:
        if (!champagneTexture.loadFromFile("champagne.png")) {
            std::cerr << "Error loading dessert texture!" << std::endl;
        }
        foodSprite.setTexture(champagneTexture);
        break;
    default:
        std::cerr << "Invalid food type!" << std::endl;
        break;
    }
}

// Default constructor
Food::Food()
    : foodType(FoodType::Appetizer),
    foodPosition({ 0.0f, 0.0f }),
    foodDimension({ 50.0f, 50.0f }),
    messagePrinted(false) {
    loadTexture(foodType);
    foodSprite.setPosition(foodPosition.x, foodPosition.y);
}

// Overloaded constructor
Food::Food(FoodType type, FoodPosition position, FoodDimension dimension)
    : foodType(type),
    foodPosition(position), // Set position using FoodPosition struct
    foodDimension(dimension), // Set dimension using FoodDimension struct
    messagePrinted(false) { 
    loadTexture(type); // Load texture based on type
    foodSprite.setPosition(foodPosition.x, foodPosition.y); // Use position struct to set position
}

// Method to draw the Food on the window
void Food::draw(sf::RenderWindow& window) {
    window.draw(foodSprite);
}

// Getter for Food Type
FoodType Food::getFoodType() {
    return foodType;
}

// Setter for Food Type
void Food::setFoodType(FoodType type) {
    foodType = type;
    loadTexture(type); // Load new texture when food type changes
}

// Get Food width
float Food::getWidth() const {
    return foodDimension.w; // Return the width from the dimension
}

// Get Food height
float Food::getHeight() const {
    return foodDimension.h; // Return the height from the dimension
}

// Method for Click handling
bool Food::isClicked(float mouseX, float mouseY) {
    sf::FloatRect bounds = foodSprite.getGlobalBounds();
    return bounds.contains(mouseX, mouseY);
}

// Method to get the global bounds of the food
sf::FloatRect Food::getGlobalBounds() const {
    return foodSprite.getGlobalBounds();
}

// Method to reset the message printed status
void Food::resetMessageStatus() {
    messagePrinted = false;
}

// Getter for messagePrinted status
bool Food::isMessagePrinted() const {
    return messagePrinted;
}

// Setter for messagePrinted status
void Food::setMessagePrinted(bool status) {
    messagePrinted = status;
}

// Friend operator>> for assigning food to a customer and parsing their message
// This operator allows the Food object to interact with a CustomerEntity and assign food to them
void operator>>(Food &food, CustomerEntity *customer) {
    if (customer->isSeated()) { // Check if the customer is currently seated
        
        // Call the polymorphic assignFood function on the customer.
        // The assignFood method is pure virtual/abstract in CustomerEntity and must be implemented by all derived classes.
        // The appropriate method is called based on the customer's actual type at runtime, demonstrating polymorphism.
        customer->assignFood(&food); // Assign food to customer (polymorphic behavior)

        // Parses any pending messages using the friend extraction operator
        std::istringstream stream(customer->getMessage());
        stream >> *customer; // This calls the friend operator>> for CustomerEntity (parsing logic)
    }
    else {
        std::cout << "Customer is not seated. Cannot assign food." << std::endl;
    }
}

// Destructor
Food::~Food() {
}
