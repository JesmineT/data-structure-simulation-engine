#include "Table.h"

// Default Constructor
Table::Table()
  : tableID(""),
    availability(true),
    messagePrinted(false){ 
    // Initialize the rectangle with default values
    rectangle.setSize(sf::Vector2f(100.0f, 50.0f)); // Default size
    rectangle.setPosition(0.0f, 0.0f); // Default position
    rectangle.setFillColor(sf::Color(250, 248, 199)); // Default color (light beige)
}

// Overloaded Constructor using TablePosition and TableDimension structs
Table::Table(std::string tableID, TablePosition position, TableDimension dimension)
    : tableID(tableID),
    availability(true),
    messagePrinted(false) {
    rectangle.setSize(sf::Vector2f(dimension.w, dimension.h));
    rectangle.setPosition(position.x, position.y);
    rectangle.setFillColor(sf::Color(250, 248, 199)); // Default color (light beige)
}

// Method to draw the Table on the window
void Table::draw(sf::RenderWindow& window) {
    window.draw(rectangle);
}

// Method for Click Handling
bool Table::isClicked(float mouseX, float mouseY) {
    sf::FloatRect bounds = rectangle.getGlobalBounds();
    return bounds.contains(mouseX, mouseY);
}

// Getter for tableID
std::string Table::getTableID() {
    return tableID;
}

// Setter for tableID
void Table::setTableID(std::string& id) {
    tableID = id;
}

// Getter for availability status
bool Table::isAvailable() {
    return availability;
}

// Setter for availability status
void Table::setAvailability(bool status) {
    // If the status is changing
    if (availability != status) {
        availability = status;

        // If the table is now vacant, change the color back to light pale yellow
        if (availability) {
            rectangle.setFillColor(sf::Color(250, 248, 199)); // Light pale yellow
        }
        // If the table is occupied, change the color to red
        else {
            rectangle.setFillColor(sf::Color(200, 100, 100)); // Muted red
        }
    }
}

// Getter for the Position of the Table
sf::Vector2f Table::getPosition() const {
    return rectangle.getPosition();
}

// Getter for Table width
float Table::getWidth() const {
    return rectangle.getSize().x;
}

// Getter for Table height
float Table::getHeight() const {
    return rectangle.getSize().y;
}

// Method to get the Global Bounds of the table
sf::FloatRect Table::getGlobalBounds() const {
    return rectangle.getGlobalBounds();
}

// Method to reset the message printed status
void Table::resetMessageStatus() {
    messagePrinted = false;
}

// Getter for messagePrinted status
bool Table::isMessagePrinted() const {
    return messagePrinted;
}

// Setter for messagePrinted status
void Table:: setMessagePrinted(bool status) {
    messagePrinted = status;
}

// Destructor
Table::~Table() {
}
