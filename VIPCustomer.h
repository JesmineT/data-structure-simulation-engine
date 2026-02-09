#ifndef VIPCUSTOMER_H
#define VIPCUSTOMER_H
#include "CustomerEntity.h"

// VIPCustomer is a child class of CustomerEntity
class VIPCustomer : public CustomerEntity {
private:
    int tipAmount;

public:
    // Constructor that initializes a VIPCustomer with an ID and a specific position
    VIPCustomer(std::string fID, Position position);
    
    // Method to update the Customer's ordering and behaviour over time
    void update() override;

    // Method to handle the assignment of Food to a Customer and to set appropriate messages
    // based on the timing and correctness of the food served
    void assignFood(Food* food) override;

    // Method to call after customer is done with all the services 
    void finishMeal() override;

    // Method to tip the player
    void tip() override;

    // VIPCustomer doesn't use this method
    void complain() override;

    // VIPCustomer doesn't use this method
    void chitChat() override;
};
#endif
