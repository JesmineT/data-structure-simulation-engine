#include "Scrap.h"

// Define the fixed size for all scraps
const sf::Vector2f Scrap::fixedSize(50, 20); // Set the fixed size

// Constructor to initialize the scrap with a name and position
Scrap::Scrap(const std::string& scrapName, const ScrapPosition& position)
    : name(scrapName), shape(fixedSize) {
    shape.setFillColor(sf::Color::Cyan); // Set color for the scrap item
    setPosition(position.x, position.y); // Set the position using the ScrapPosition struct
}

// Get the name of the scrap
std::string Scrap::getName() const {
    return name;
}

// Display scrap information in the console
void Scrap::displayInfo() const {
    std::cout << "Scrap Name: " << name << std::endl;
}

// Set the position of the scrap's SFML shape
void Scrap::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

// Render the scrap on the provided SFML window
void Scrap::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

// Get the global bounds of the scrap
sf::FloatRect Scrap::getGlobalBounds() const {
    return shape.getGlobalBounds(); // Return the global bounds of the shape
}