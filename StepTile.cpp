#include "StepTile.h"

// Constructor to initialize the step tile
StepTile::StepTile(float x, float y, float size)
    : position(x, y) {
    tile.setSize(sf::Vector2f(size, size));
    tile.setPosition(position);
    tile.setFillColor(sf::Color(150, 150, 150, 255)); // Grey color
}

// Method to draw the tile on the window
void StepTile::draw(sf::RenderWindow& window) {
    window.draw(tile);
}

// Check if the given point is within the global bounds of the tile
bool StepTile::contains(const sf::Vector2f& point) const {
    return tile.getGlobalBounds().contains(point);
}

// Destructor
StepTile::~StepTile() {}