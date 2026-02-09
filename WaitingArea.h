#ifndef WAITING_AREA_H
#define WAITING_AREA_H
#include <SFML/Graphics.hpp>

// WaitingArea class represents an area within the game where customers can wait before being served.
// It visually renders a rectangle shape on the screen to indicate the waiting area.
class WaitingArea {
private:
    sf::RectangleShape rectangle;

public:
    // Default Constructor
    WaitingArea();

    // Overloaded Constructor
    WaitingArea(float x, float y, float width, float height);

    // Method to draw the Waiting Area
    void draw(sf::RenderWindow &window);

    // Destructor
    ~WaitingArea();
};
#endif
