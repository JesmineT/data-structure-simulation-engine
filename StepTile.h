#ifndef STEPTILE_H
#define STEPTILE_H
#include <SFML/Graphics.hpp>

// StepTile is a class that defines the walkable path for the player and the enemy
class StepTile {
private:
    sf::RectangleShape tile; // Shape to represent the tile
    sf::Vector2f position; // Position of the tile

public:
    // Constructor to initialize the step tile
    StepTile(float x, float y, float size);

    // Method to draw the tile on the window
    void draw(sf::RenderWindow& window);

    // Check if the given point is within the global bounds of the tile
    bool contains(const sf::Vector2f& point) const;

    // Destructor
    ~StepTile();
};
#endif
