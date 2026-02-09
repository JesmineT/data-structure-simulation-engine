#include "VIPCustomer.h"
#include <iostream>

// VIPCustomer is a child class of CustomerEntity
// Constructor that initializes a VIPCustomer with an ID and a specific position
VIPCustomer::VIPCustomer(std::string fID, Position position)
    : tipAmount(0),
    CustomerEntity(fID, position, 20, 2000, 150, 30, 30) { // Call the parent class (CustomerEntity) constructor to initialize common attributes
    circle.setFillColor(sf::Color(255, 215, 0));  // Golden color
}

// Method to update the Customer's ordering and behaviour over time
void VIPCustomer::update() {
    // If the customer is seated and waiting for an appetizer
    if (seated && !appetizerOrdered && !waitingForFood) {
        // Start the timer for ordering after seating
        if (seatedClock.getElapsedTime().asSeconds() >= 5) {
            orderAppetizer();
        }
    }

    // If the appetizer is received, now ask for the main course
    if (appetizerOrdered && !mainCourseOrdered && !waitingForFood && assignedFood != nullptr) {
        // Start asking for the main course after a delay
        if (seatedClock.getElapsedTime().asSeconds() >= 5) {
            orderMainCourse();
        }
    }

    // If the main course is received, now ask for the dessert
    if (mainCourseOrdered && !dessertOrdered && !waitingForFood && assignedFood != nullptr) {
        // Start asking for the dessert after a delay
        if (seatedClock.getElapsedTime().asSeconds() >= 5) {
            orderDessert();
        }
    }

    // If the dessert is received, now ask for champagne
    if (dessertOrdered && !champagneOrdered && !waitingForFood && assignedFood != nullptr) {
        // Start asking for the dessert after a delay
        if (seatedClock.getElapsedTime().asSeconds() >= 5) {
            orderChampagne();
        }
    }

    // Check if all courses are completed, mark the meal as finished
    if (appetizerOrdered && mainCourseOrdered && dessertOrdered && champagneOrdered && !waitingForFood && assignedFood != nullptr) {
        finishMeal();
    }
}

// Method to handle the assignment of Food to a Customer and to set appropriate messages
// based on the timing and correctness of the food served
void VIPCustomer::assignFood(Food* food) {
    if (food == nullptr) {
        std::cerr << "Error: Null food pointer\n" << std::endl;
        return;
    }

    float elapsedTime = foodClock.getElapsedTime().asSeconds();
    bool servedOnTime = (elapsedTime <= 5); // the 5 second timer starts when the customer orders the food

    // If served On Time && food served is Correct
    if (servedOnTime && food->getFoodType() == expectedFoodType) {
        fMessage = "IncreaseCurrentHappiness 50";
        std::cout << "Customer " << fID << " received correct food within " << elapsedTime << " seconds.\n" << std::endl;
    }

    // If served Not On Time && food served is Correct
    else if (!servedOnTime && food->getFoodType() == expectedFoodType) {
        fMessage = "IncreaseCurrentHappiness 25";
        std::cout << "Customer " << fID << " received correct food late after " << elapsedTime << " seconds.\n" << std::endl;
    }

    // If served On Time && food served is Incorrect
    else if (servedOnTime && food->getFoodType() != expectedFoodType) {
        fMessage = "DecreaseCurrentHappiness 50";
        std::cout << "Customer " << fID << " received incorrect food within " << elapsedTime << " seconds.\n" << std::endl;
    }

    // If served Not On Time && food served is Incorrect
    else if (!servedOnTime && food->getFoodType() != expectedFoodType) {
        fMessage = "DecreaseCurrentHappiness 75";
        std::cout << "Customer " << fID << " received incorrect food late after " << elapsedTime << " seconds.\n" << std::endl;
    }

    waitingForFood = false; 
    assignedFood = food;  // Assign the food to the customer
    seatedClock.restart(); 
}

// Method to call after customer is done with all the services 
void VIPCustomer::finishMeal() {
    std::cout << fID << " has finished their meal!\n" << std::endl;

    // Call the tip function once the meal is complete
    tip();

    // Mark the meal as finished
    finishedMeal = true;  

    // Reset the table's availability back to true (available)
    if (assignedTable) {
        assignedTable->setAvailability(true);
    }
    else {
        std::cout << "Pointer is null " << std::endl;
    }

    // Clear the table:
    seated = false; // Mark the customer as not seated
    assignedFood = nullptr; // Clear the assigned food
    setPosition(-1000, -1000); // Move the customer off-screen 
}

// Method to tip the player
void VIPCustomer::tip() {
    // Calculate tipAmount based on 10% of currentHappiness
    tipAmount = static_cast<int>(fCurrentHappiness * 0.10); // static_cast is basically to truncate the decimal part of the tipAmount

    // Display the tipping message
    if (tipAmount > 0) {
        std::cout << "VIPCustomer gives a tip of " << tipAmount << " points ~\n";
        
        // Increase player's reputation by the tipAmount
        Player* player = Player::getInstance();  // Get the singleton instance of Player
        if (player) {
            int currentReputation = player->getPlayerReputation();
            player->setPlayerReputation(currentReputation + tipAmount);
            std::cout << "Customer " << fID << " tipped to the player's reputation by " << tipAmount << "\n" << std::endl;
        }
        else {
            std::cerr << "Error: Unable to access Player instance.\n" << std::endl;
        }
    }
    else {
        std::cout << "VIPCustomer is unhappy and gives no tip :(\n";
    }
}

void VIPCustomer::complain() {
    // VIPCustomer doesn't use this method
}

void VIPCustomer::chitChat() {
    // VIPCustomer doesn't use this method
}
