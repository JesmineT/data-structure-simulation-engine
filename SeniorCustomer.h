#ifndef SENIORCUSTOMER_H
#define SENIORCUSTOMER_H
#include "CustomerEntity.h"

// SeniorCustomer is a child class of CustomerEntity
class SeniorCustomer : public CustomerEntity {
public:
    // Constructor that initializes a SeniorCustomer with an ID and a specific position
    SeniorCustomer(std::string fID, Position position);
   
    // Method to update the Customer's ordering and behaviour over time
    void update() override;

    // Method to handle the assignment of Food to a Customer and to set appropriate messages
    // based on the timing and correctness of the food served
    void assignFood(Food* food) override;

    // Method to have a chit-chat with the Player after finishing their meal
    void chitChat() override;

    // SeniorCustomer doesn't use this method
    void tip() override;

    // SeniorCustomer doesn't use this method
    void complain() override;
};
#endif
