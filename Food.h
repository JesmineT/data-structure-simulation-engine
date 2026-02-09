#ifndef FOOD_H
#define FOOD_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

// Included this to prevent circular dependencies
// Forward declaration of CustomerEntity class
class CustomerEntity;

// Struct for FoodPosition to group x and y coordinates
struct FoodPosition {
    float x;
    float y;
};

// Struct for FoodDimension to group width and height
struct FoodDimension {
    float w;
    float h;
};

// Enumeration for FoodType
enum class FoodType {
    Appetizer,
    MainCourse,
    Dessert,
    Champagne,
    None,
};

class Food {
private:
    sf::Sprite foodSprite; // Sprite to represent the food
    sf::Texture appetizerTexture; // Texture for appetizer
    sf::Texture mainCourseTexture; // Texture for main course
    sf::Texture dessertTexture; // Texture for dessert
    sf::Texture champagneTexture; // Texture for champagne
    FoodType foodType; // Type of food
    FoodPosition foodPosition; // Position of the food (x & y)
    FoodDimension foodDimension; // Dimension of the food (w & h)
    bool messagePrinted;

    // Method to load the textures of different food types 
    // Private method as it is intended for internal use only
    void loadTexture(FoodType type);

public:
    // Default Constructor
    Food();

    // Overloaded Constructor
    Food(FoodType foodType, FoodPosition foodPosition, FoodDimension foodDimension);

    // Method to draw the Food on the window
    void draw(sf::RenderWindow &window);

    // Getter & Setter for Food Type
    FoodType getFoodType();
    void setFoodType(FoodType foodType);

    // Getter for Food width
    float getWidth() const;

    // Getter for Food height
    float getHeight() const;

    // Method for Click handling
    bool isClicked(float mouseX, float mouseY);

    // Get Food Global Bounds
    sf::FloatRect getGlobalBounds() const;

    // Method to reset the message printed status
    void resetMessageStatus();

    // Getter for messagePrinted status
    bool isMessagePrinted() const;

    // Setter for messagePrinted status
    void setMessagePrinted(bool status);

    // Friend operator>> for assigning food to a customer and parsing their message
    // This operator allows the Food object to interact with a CustomerEntity and assign food to them
    friend void operator>>(Food &food, CustomerEntity *customer);

    // Destructor
    ~Food();
};
#endif