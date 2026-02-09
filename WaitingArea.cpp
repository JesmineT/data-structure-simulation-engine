#include "WaitingArea.h"

// WaitingArea class represents an area within the game where customers can wait before being served.
// It visually renders a rectangle shape on the screen to indicate the waiting area.
// Default Constructor
WaitingArea::WaitingArea()
    : rectangle() { // Initialize the rectangle to default values
    rectangle.setSize(sf::Vector2f(100.0f, 100.0f)); // Default size
    rectangle.setPosition(0.0f, 0.0f); // Default position
    rectangle.setFillColor(sf::Color(81, 8, 4)); // Default color
}

// Overloaded Constructor
WaitingArea::WaitingArea(float x, float y, float width, float height) {
    rectangle.setSize(sf::Vector2f(width, height)); // Set the size of the rectangle
    rectangle.setPosition(x, y); // Set the position of the rectangle within the window
    rectangle.setFillColor(sf::Color(81, 8, 4)); // Set the fill color of the rectangle. The color is a dark reddish-brown.
}

// Method to draw the Waiting Area
void WaitingArea::draw(sf::RenderWindow& window) {
    window.draw(rectangle);
}

// Destructor
WaitingArea::~WaitingArea() {
}