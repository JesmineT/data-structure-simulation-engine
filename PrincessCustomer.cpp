#include "PrincessCustomer.h"
#include <iostream>

// PrincessCustomer is a child class of CustomerEntity
// Constructor that initializes a PrincessCustomer with an ID and a specific position
PrincessCustomer::PrincessCustomer(std::string fID, Position position)
    : dessertsEaten(0),
    complainTriggered(false),
    CustomerEntity(fID, position, 20, 1000, 50, 5, 25) { // Call the parent class (CustomerEntity) constructor to initialize common attributes
    circle.setFillColor(sf::Color(255, 192, 203));  // Pink color
}

// Method to update the Customer's ordering and behaviour over time
void PrincessCustomer::update() {
    // If happiness drops below 25, trigger complain()
    if (fCurrentHappiness < 25 && !complainTriggered) {
        complain();
        complainTriggered = true;
    }

    // If the customer is seated and waiting for the first dessert
    if (seated && dessertsEaten == 0 && !dessertOrdered && !waitingForFood) {
        // Start the timer for ordering the first dessert after seating
        if (seatedClock.getElapsedTime().asSeconds() >= 5) {
            orderDessert(); // Order the first dessert
        }
    }

    // If the first dessert is received, now ask for the second dessert
    if (dessertsEaten == 1 && !dessertOrdered && !waitingForFood && assignedFood != nullptr) {
        // Start the timer for ordering the second dessert after the first one is received
        if (seatedClock.getElapsedTime().asSeconds() >= 5) {
            orderDessert(); // Order the second dessert
        }
    }

    // If the second dessert is received, now ask for the third dessert
    if (dessertsEaten == 2 && !dessertOrdered && !waitingForFood && assignedFood != nullptr) {
        // Start the timer for ordering the third dessert after the second one is received
        if (seatedClock.getElapsedTime().asSeconds() >= 5) {
            orderDessert(); // Order the third dessert
        }
    }

    // If the third dessert is received, now ask for the fourth dessert
    if (dessertsEaten == 3 && !dessertOrdered && !waitingForFood && assignedFood != nullptr) {
        // Start the timer for ordering the fourth dessert after the third one is received
        if (seatedClock.getElapsedTime().asSeconds() >= 5) {
            orderDessert(); // Order the fourth dessert
        }
    }

    // After the fourth dessert is received, finish the meal
    if (dessertsEaten == 4 && !waitingForFood && assignedFood != nullptr) {
        finishMeal(); // Call the method to handle finishing the meal
    }
}

// Method to handle the assignment of Food to a Customer and to set appropriate messages
// based on the timing and correctness of the food served
void PrincessCustomer::assignFood(Food* food) {
    if (food == nullptr) {
        std::cerr << "Error: Null food pointer\n" << std::endl;
        return;
    }

    float elapsedTime = foodClock.getElapsedTime().asSeconds();
    bool servedOnTime = (elapsedTime <= 4); // the 4 second timer starts when the customer orders the food

    // If served On Time && food served is Correct
    if (servedOnTime && food->getFoodType() == expectedFoodType) {
        dessertsEaten++;
        fMessage = "IncreaseCurrentHappiness 50";
        std::cout << "Customer " << fID << " received correct food within " << elapsedTime << " seconds.\n" << std::endl;
    }

    // If served Not On Time && food served is Correct
    else if (!servedOnTime && food->getFoodType() == expectedFoodType) {
        dessertsEaten++;
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
    dessertOrdered = false;
    seatedClock.restart();
}

// Method to order a Dessert
void PrincessCustomer::orderDessert() {
    std::cout << fID << " has ordered dessert number " << (dessertsEaten + 1) << "!\n" << std::endl;
    waitingForFood = true; // Mark waiting for food to be true
    dessertOrdered = true; // Mark that dessert as ordered
    expectedFoodType = FoodType::Dessert; // Set expectedFoodType to be Dessert
    seatedClock.restart();
    foodClock.restart();
}

// Method for the PrincessCustomer to complain
void PrincessCustomer::complain() {
    char playerChoice;

    // Start conversation
    std::cout << "Princess: \"The food and service is bad! You deserved to get fired!\"\n";

    // Loop until valid input is received
    while (true) {
        std::cout << "Player: Press 'A' to say \"I know. But you eat any dessert cuz u fatty\" or 'B' to say \"Sorry.\"\n";

        // Capture player's response
        std::cin >> playerChoice;

        // Handle the player's choice
        if (playerChoice == 'A' || playerChoice == 'a') {
            std::cout << "Player: \"I know. But you eat any dessert cause you a fatty\"\n";
            std::cout << "Princess: \"*gasp* How dare you!\"\n";
            attackPlayerReputation();
            break;  // Exit loop after valid input
        }
        else if (playerChoice == 'B' || playerChoice == 'b') {
            std::cout << "Player: \"Sorry.\"\n";
            std::cout << "Princess: \"Hmm.. at least fight back a little..\"\n";
            boostPlayerReputation();
            break;  // Exit loop after valid input
        }
        else {
            std::cout << "Invalid choice! Please press 'A' or 'B'.\n";
        }
    }
}

void PrincessCustomer::tip() {
    // PrincessCustomer doesn't use this method
}

void PrincessCustomer::chitChat() {
    //PrincessCustomer doesn't use this method
}