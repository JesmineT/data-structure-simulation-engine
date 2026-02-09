#ifndef TABLE_H
#define TABLE_H
#include <SFML/Graphics.hpp>

// Struct for TablePosition to group width and height
struct TablePosition {
    float x;
    float y;
};

// Struct for TableDimension to group width and height
struct TableDimension {
    float w;
    float h;
};

class Table {
private:
    sf::RectangleShape rectangle;
    std::string tableID;
    bool availability;
    bool messagePrinted;

public:
    // Default Constructor
    Table();

    // Overloaded Constructor
    Table(std::string tableID, TablePosition tablePosition, TableDimension tableDimension);

    // Method to draw the Table on the window
    void draw(sf::RenderWindow &window);

    // Method for Click Handling
    bool isClicked(float mouseX, float mouseY);

    // Get & Set tableID
    std::string getTableID();
    void setTableID(std::string &id);

    // Getter & Setter for availability status
    bool isAvailable();
    void setAvailability(bool status);
    
    // Getter for the Position of the Table
    sf::Vector2f getPosition() const;

    // Get Table width
    float getWidth() const;

    // Get Table height
    float getHeight() const;

    // Get Table Global Bounds
    sf::FloatRect getGlobalBounds() const;

    // Method to reset the message printed status
    void resetMessageStatus();

    // Getter for messagePrinted status
    bool isMessagePrinted() const;

    // Setter for messagePrinted status
    void setMessagePrinted(bool status);

    // Destructor 
    ~Table();
};
#endif
