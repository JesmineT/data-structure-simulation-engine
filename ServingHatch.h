#ifndef SERVING_HATCH_H
#define SERVING_HATCH_H
#include <SFML/Graphics.hpp>

// ServingHatch class represents an area within the game where food is rendered.
// It visually renders a rectangle shape on the screen to indicate the serving hatch.
class ServingHatch {
private:
    sf::RectangleShape rectangle;
    
public:
    // Default Constructor
    ServingHatch();

    // Overloaded Constructor
    ServingHatch(float x, float y, float width, float height);

    // Method to draw the Serving Hatch on the window
    void draw(sf::RenderWindow &window);

    // Destructor
    ~ServingHatch();
};
#endif
