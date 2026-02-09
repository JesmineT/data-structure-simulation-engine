#include "ServingHatch.h"

// ServingHatch class represents an area within the game where food is rendered.
// It visually renders a rectangle shape on the screen to indicate the serving hatch.
//Default Constructor
ServingHatch::ServingHatch()
    : rectangle() { // Initialize the rectangle to default values
    rectangle.setSize(sf::Vector2f(100.0f, 100.0f)); // Default size
    rectangle.setPosition(0.0f, 0.0f); // Default position
    rectangle.setFillColor(sf::Color(88, 57, 39)); // Default color
}


// Overloaded Constructor
ServingHatch::ServingHatch(float x, float y, float width, float height) {
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color(88, 57, 39));
}

// Method to draw the Serving Hatch on the window
void ServingHatch::draw(sf::RenderWindow& window) {
    window.draw(rectangle);
}

// Destructor
ServingHatch::~ServingHatch() {}