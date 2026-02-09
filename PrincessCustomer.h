#ifndef PRINCESSCUSTOMER_H
#define PRINCESSCUSTOMER_H
#include "CustomerEntity.h"

// PrincessCustomer is a child class of CustomerEntity
class PrincessCustomer : public CustomerEntity {
private:
    int dessertsEaten;
    bool complainTriggered;

public:
    // Constructor that initializes a PrincessCustomer with an ID and a specific position
    PrincessCustomer(std::string fID, Position position);

    // Method to update the Customer's ordering and behaviour over time
    void update() override;

    // Method to handle the assignment of Food to a Customer and to set appropriate messages
    // based on the timing and correctness of the food served
    void assignFood(Food* food) override;

    // Method to order a Dessert
    void orderDessert() override;

    // Method for the PrincessCustomer to complain
    void complain() override;

    // PrincessCustomer doesn't use this method
    void tip() override; 

    // PrincessCustomer doesn't use this method
    void chitChat() override; 
};
#endif