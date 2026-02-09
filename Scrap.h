#ifndef SCRAP_H
#define SCRAP_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

// Struct for ScrapPosition to group x and y coordinates
struct ScrapPosition {
    float x;
    float y;
};

class Scrap {
private:
    std::string name;
    sf::RectangleShape shape;
    static const sf::Vector2f fixedSize; // Fixed size for all scraps

public:
    // Constructor to initialize the scrap with a name and position
    Scrap(const std::string& scrapName, const ScrapPosition& position);

    // Get the name of the scrap
    std::string getName() const;

    // Display scrap information in the console
    void displayInfo() const;

    // Set the position of the scrap's SFML shape
    void setPosition(float x, float y);

    // Render the scrap on the provided SFML window
    void draw(sf::RenderWindow& window) const;

    // Get the global bounds of the scrap
    sf::FloatRect getGlobalBounds() const;
};
#endif