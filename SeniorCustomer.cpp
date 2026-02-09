#include "SeniorCustomer.h"
#include <iostream>

// SeniorCustomer is a child class of CustomerEntity
// Constructor that initializes a SeniorCustomer with an ID and a specific position
SeniorCustomer::SeniorCustomer(std::string fID, Position position)
    : CustomerEntity(fID, position, 20, 1500, 100, 20, 10) { // Call the parent class (CustomerEntity) constructor to initialize common attributes
    circle.setFillColor(sf::Color::Blue);  // Blue color
}

// Method to update the Customer's Ordering over time
void SeniorCustomer::update() {
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

    // Check if all courses are completed, mark the meal as finished and clear the table
    if (appetizerOrdered && mainCourseOrdered && !waitingForFood && assignedFood != nullptr) {
        chitChat(); // Call the chitChat() method
        finishMeal(); // Call the method to handle finishing the meal
    }
}

// Method to handle the assignment of Food to a Customer and to set appropriate messages
// based on the timing and correctness of the food served
void SeniorCustomer::assignFood(Food* food) {
    if (food == nullptr) {
        std::cerr << "Error: Null food pointer\n" << std::endl;
        return;
    }

    float elapsedTime = foodClock.getElapsedTime().asSeconds();
    bool servedOnTime = (elapsedTime <= 6); // the 6 second timer starts when the customer orders the food

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

// Method to have a chit-chat with the Player after finishing their meal
void SeniorCustomer::chitChat() {
    char playerChoice;

    // Start conversation
    std::cout << "SeniorCustomer: \"Hope you don't mind a little chitchat. It's been a while since I've held a conversation with someone.\"\n";

    // Loop until valid input is received
    while (true) {
        std::cout << "Player: Press 'A' to say \"Sure\" or 'B' to say \"Goodbye\"\n";

        // Capture player's response
        std::cin >> playerChoice;

        // Handle the player's choice
        if (playerChoice == 'A' || playerChoice == 'a') {
            std::cout << "Player: \"Sure.\"\n";
            std::cout << "SeniorCustomer: \"How long have you been working here?\"\n";

            // Loop until valid input for the follow-up question
            while (true) {
                std::cout << "Player: Press 'A' to say \"Yesterday.\" or 'B' to say \"I wanna get fired...\"\n";
                std::cin >> playerChoice;

                if (playerChoice == 'A' || playerChoice == 'a') {
                    std::cout << "Player: \"Yesterday.\"\n";
                    std::cout << "SeniorCustomer: \"All the best! Starting a new job can be tough, but you'll get the hang of it.\"\n";
                    boostPlayerReputation();
                    break; // Exit the inner loop after valid input
                }
                else if (playerChoice == 'B' || playerChoice == 'b') {
                    std::cout << "Player: \"I wanna get fired...\"\n";
                    std::cout << "SeniorCustomer: \"Haha, tough day, huh? Well, hang in there, kid. All the best!\"\n";
                    boostPlayerReputation();
                    break; // Exit the inner loop after valid input
                }
                else {
                    std::cout << "Invalid choice! Please press 'A' or 'B'.\n";
                }
            }

            break; // Exit the outer loop after handling the follow-up conversation
        }
        else if (playerChoice == 'B' || playerChoice == 'b') {
            std::cout << "Player: \"Goodbye.\"\n";
            std::cout << "SeniorCustomer: \"Okay, that's alright.\"\n";
            break; // Exit the outer loop after valid input
        }
        else {
            std::cout << "Invalid choice! Please press 'A' or 'B'.\n";
        }
    }
}

void SeniorCustomer::tip() {
    // SeniorCustomer doesn't use this method
}

void SeniorCustomer::complain() {
    // SeniorCustomer doesn't use this method
}