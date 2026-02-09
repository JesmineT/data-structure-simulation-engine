#ifndef CUSTOMERENTITY_H
#define CUSTOMERENTITY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "Food.h"
#include "Player.h"
#include "Table.h"

// Struct to group x and y coordinates, improving clarity and organization
struct Position {
    float x; 
    float y;
};

class CustomerEntity {
protected:  // Make `protected` so child classes can access them
    std::string fID;
    Position fPosition;  
    int fMaxHappiness;  
    int fCurrentHappiness;  
    int fReputationBoost; 
    int fReputationAttack; 
    std::string fMessage; 
    bool seated;  
    bool waitingForFood;
    Food *assignedFood; // Pointer to the assigned food
    bool appetizerOrdered;  
    bool mainCourseOrdered; 
    bool dessertOrdered;
    bool champagneOrdered;
    sf::Clock seatedClock;  // Timer to handle seating logic
    sf::Clock foodClock; // Timer for waiting for food logic
    FoodType expectedFoodType;  
    bool finishedMeal;
    Table* assignedTable; // Pointer to the assigned table
    bool messagePrinted;
    int boostCount; // Count the number of times the Customer calls boostPlayerReputation()
    int attackCount; // Count the number of times the Customer calls attackPlayerReputation()
    sf::CircleShape circle; // Circle to represent the Customer object

public:
    // Default Constructor
    CustomerEntity();

    // Overloaded Constructor
    CustomerEntity(std::string id, Position position, float radius, int maxHappiness, int currentHappiness, int reputationBoost, int reputationAttack);

    // Get & Set fID
    std::string getCustomerID();
    void setCustomerID(std::string &id);

    // Get & Set fPosition
    Position getPosition();
    void setPosition(float x, float y);
    
    // Get & Set fMaxHappiness
    int getMaxHappiness();
    void setMaxHappiness(int maxHappiness);

    // Get & Set fCurrentHappiness
    int getCurrentHappiness();
    void setCurrentHappiness(int currentHappiness);

    // Get & Set fReputationBoost
    int getReputationBoost();
    void setReputationBoost(int reputationBoost);

    // Get & Set fReputationAttack
    int getReputationAttack();
    void setReputationAttack(int reputationAttack);

    // Get & Set fMessage
    std::string getMessage();
    void setMessage(std::string message);

    // Get & Set seated status
    bool isSeated();
    void setSeated(bool status);

    // Status if Customer has finished their meal
    bool hasFinishedMeal();

    // Draw the Customer
    void draw(sf::RenderWindow &window);

    // Method for Click handling
    bool isClicked(float mouseX, float mouseY);

    // Get the Radius of the Customer
    // to position the selected Customer's location to the middle of the selected table upon seated
    float getRadius() const;

    // Method to Boost Player's Reputation
    void boostPlayerReputation();

    // Method to Attack Player's Reputation
    void attackPlayerReputation();

    // This method assigns the specified table to the customer, 
    // tracking which table they are seated at.
    void seat(Table* table);

    // Method to order an Appetizer
    void orderAppetizer();

    // Method to order a Main Course
    void orderMainCourse();

    // Method to order a Dessert
    virtual void orderDessert(); // virtual for PrincessCustomer

    // Method to order a Champagne
    void orderChampagne();

    // Method to call after customer is done with all the services 
    virtual void finishMeal(); // virtual for VIPCustomer

    // Method that returns a string with current fields of the Customer
    std::string PrintStat();    

    // Method to get the global bounds of the customer
    sf::FloatRect getGlobalBounds() const;

    // Method to reset the message printed status
    void resetMessageStatus();

    // Getter & Setter for messagePrinted status
    bool isMessagePrinted() const;
    void setMessagePrinted(bool status);

    // Getters for boost and attack counts
    int getBoostCount() const;
    int getAttackCount() const;

    // Friend operator overload for insertion | output
    // Output the contents of an object to an output stream (e.g., std::cout)
    friend std::ostream &operator<<(std::ostream &aOstream, CustomerEntity &aCustomerEntity);

    // Friend operator overload for extraction | input
    // Input the contents of an object from an input stream (e.g., std::cin)
    friend std::istream &operator>>(std::istream &aIstream, CustomerEntity &aCustomerEntity);

    // Method to Update the Customer's Ordering and behaviour over time
    virtual void update() = 0;  // Mark as virtual for child-specific updates

    // Method to handle the assignment of Food to a Customer and to set appropriate messages
    // based on the timing and correctness of the food served
    virtual void assignFood(Food* food) = 0;

    // Abstract methods to be implemented by child classes
    virtual void tip() = 0; // VIPCustomer
    virtual void chitChat() = 0; // SeniorCustomer
    virtual void complain() = 0; // PrincessCustomer

    // Destructor
    ~CustomerEntity();
};
#endif