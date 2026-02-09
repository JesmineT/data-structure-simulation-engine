#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Player.h"
#include "Table.h"
#include "WaitingArea.h"
#include "ServingHatch.h"
#include "Food.h"
#include "CustomerEntity.h"
#include "VIPCustomer.h"
#include "PrincessCustomer.h"
#include "SeniorCustomer.h"

int main() {    
    // Retrieves singleton instance of the Player class using getInstance()
    Player* player = Player::getInstance();

    // Prompts player to input name & reputation using the overloaded extraction (>>) operator
    std::cin >> *player;

    // Outputs the player's name and reputation using the overloaded insertion (<<) operator.
    std::cout << *player;

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(1500, 800), "Blood Diner");

    // Create waiting area object ( x, y, w, h )
    WaitingArea waitingArea(1200, 600, 290, 150);

    // Create serving hatch object ( x, y, w, h )
    ServingHatch servingHatch(0, 50, 1500, 100);

    // Create TablePosition structs for each table { x, y }
    TablePosition position1 = { 250, 300 };
    TablePosition position2 = { 550, 300 };
    TablePosition position3 = { 850, 300 };
    TablePosition position4 = { 250, 500 };
    TablePosition position5 = { 550, 500 };
    TablePosition position6 = { 850, 500 };

    // Create TableDimension struct for all tables { w, h }
    TableDimension commonTableDimension = { 130, 80 };

    // Create Table objects using the structs
    Table table1(position1, commonTableDimension); // 1st table in the 1st row from the left
    Table table2(position2, commonTableDimension); 
    Table table3(position3, commonTableDimension); 

    Table table4(position4, commonTableDimension); // 1st table in the 2nd row from the left
    Table table5(position5, commonTableDimension); 
    Table table6(position6, commonTableDimension);


    // Create FoodPosition structs for each food { x, y }
    FoodPosition appetizerPosition = { 100, 70 };
    FoodPosition mainCoursePosition = { 200, 70 };
    FoodPosition dessertPosition = { 300, 70 };

    // Create FoodDimension structs for all food { w, h }
    FoodDimension commonFoodDimension = { 40, 40 };

    // Create food objects (foodType, foodPosition, foodDimension)
    Food appetizer(FoodType::Appetizer, appetizerPosition, commonFoodDimension);
    Food mainCourse(FoodType::MainCourse, mainCoursePosition, commonFoodDimension); 
    Food dessert(FoodType::Dessert, dessertPosition, commonFoodDimension);


    // Create Position structs for each customer { x, y }
    Position vipPosition = { 1250, 605 };
    Position princessPosition = { 1300, 605 };
    Position seniorPosition = { 1350, 605 };

    // Create customer objects (fID, position)
    VIPCustomer customer1("VIP Sam", vipPosition);
    PrincessCustomer customer2("Princess Babygirl", princessPosition);
    SeniorCustomer customer3("Senior Steven", seniorPosition);

    // Create a vector of customer pointers
    //std::vector<CustomerEntity*> customersVector = { &customer1, &customer2, &customer3 };

    // Pointer to keep track of currently selected customer
    CustomerEntity* selectedCustomer = nullptr;

    // Create an array of customer pointers
    CustomerEntity* customers[] = { &customer1, &customer2, &customer3 };

    // Pointer to keep track of currently selected food
    Food* selectedFood = nullptr;

    // Create an array of Table pointers
    Table* tables[] = { &table1, &table2, &table3, &table4, &table5, &table6 };

    // Pointer to keep track of currently selected table
    Table* selectedTable = nullptr;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            // Check for key pressed
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    if (player) {
                        std::cout << "Player Reputation: " << player->getPlayerReputation() << std::endl;
                        std::cout << "\n";
                    }
                    else {
                        std::cout << "Player instance is null\n" << std::endl; // Debugging output
                    }
                }
            }

            // Check for mouse button pressed
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    float mouseX = event.mouseButton.x;
                    float mouseY = event.mouseButton.y;

                    // Check if a food is clicked
                    if (appetizer.isClicked(mouseX, mouseY)) {
                        std::cout << "Appetizer has been selected\n" << std::endl;
                        selectedFood = &appetizer;
                    }

                    else if (mainCourse.isClicked(mouseX, mouseY)) {
                        std::cout << "MainCourse has been selected\n" << std::endl;
                        selectedFood = &mainCourse;
                    }
                    else if (dessert.isClicked(mouseX, mouseY)) {
                        std::cout << "Dessert has been selected\n" << std::endl;
                        selectedFood = &dessert;
                    }

                    // Check if a customer is clicked
                    if (customer1.isClicked(mouseX, mouseY)) {
                        std::cout << customer1.getCustomerID() << " is selected\n" << std::endl;
                        selectedCustomer = &customer1; // Selecting customer
                    }
                    else if (customer2.isClicked(mouseX, mouseY)) {
                        std::cout << customer2.getCustomerID() << " is selected\n" << std::endl;
                        selectedCustomer = &customer2;
                    }
                    else if (customer3.isClicked(mouseX, mouseY)) {
                        std::cout << customer3.getCustomerID() << " is selected\n" << std::endl;
                        selectedCustomer = &customer3;
                    }

                    // Check if each table is clicked
                    if (table1.isClicked(mouseX, mouseY)) {
                        std::cout << "Table 1 is " << (table1.isAvailable() ? "vacant\n" : "occupied\n") << std::endl;
                    }
                    if (table2.isClicked(mouseX, mouseY)) {
                        std::cout << "Table 2 is " << (table2.isAvailable() ? "vacant\n" : "occupied\n") << std::endl;
                    }
                    if (table3.isClicked(mouseX, mouseY)) {
                        std::cout << "Table 3 is " << (table3.isAvailable() ? "vacant\n" : "occupied\n") << std::endl;
                    }
                    if (table4.isClicked(mouseX, mouseY)) {
                        std::cout << "Table 4 is " << (table4.isAvailable() ? "vacant\n" : "occupied\n") << std::endl;
                    }
                    if (table5.isClicked(mouseX, mouseY)) {
                        std::cout << "Table 5 is " << (table5.isAvailable() ? "vacant\n" : "occupied\n") << std::endl;
                    }
                    if (table6.isClicked(mouseX, mouseY)) {
                        std::cout << "Table 6 is " << (table6.isAvailable() ? "vacant\n" : "occupied\n") << std::endl;
                    }


                    // Iterate through the array of tables to check which table is clicked
                    for (Table* table : tables) {
                        if (table->isClicked(mouseX, mouseY)) {
                            selectedTable = table;
                            break; // Exit loop once the table is found
                        }
                    }

                    // Check if a customer is selected and if a table is clicked (to assign a customer to a table)
                    if (selectedCustomer != nullptr && !selectedCustomer->isSeated() && selectedTable != nullptr && selectedTable->isAvailable()) {
                        std::cout << "Customer " << selectedCustomer->getCustomerID() << " assigned to Table "
                            << (selectedTable == &table1 ? "1\n" :
                                selectedTable == &table2 ? "2\n" :
                                selectedTable == &table3 ? "3\n" :
                                selectedTable == &table4 ? "4\n" :
                                selectedTable == &table5 ? "5\n" :
                                selectedTable == &table6 ? "6\n" : "Unknown") << std::endl;

                        selectedTable->setAvailability(false);
                        selectedCustomer->setSeated(true);
                        // Position the customer at the center of the selected table.
                        selectedCustomer->setPosition(selectedTable->getPosition().x + selectedTable->getWidth() / 2 - selectedCustomer->getRadius(),
                            selectedTable->getPosition().y + selectedTable->getHeight() / 2 - selectedCustomer->getRadius());
                        selectedCustomer = nullptr; // Deselect the selectedCustomer pointer after processing
                    }

                    // Deselect the selectedTable pointer after processing
                    selectedTable = nullptr;
                  

                    //// If a food is selected and a customer is selected
                    //if (selectedFood != nullptr && selectedCustomer != nullptr) {
                    //    if (selectedCustomer->isSeated())
                    //    {
                    //        selectedCustomer->assignFood(selectedFood);
                    //    }
                    //    selectedFood = nullptr; // Deselect the food after assignment
                    //    selectedCustomer = nullptr;
                    //}

                    if (selectedFood != nullptr && selectedCustomer != nullptr) {

                        *selectedFood >> selectedCustomer; // Use the overloaded operator

                        selectedFood = nullptr; // Deselect the food after assignment
                        selectedCustomer = nullptr;
                    }
                }


                //// Handle right mouse click (for stats display)
                //else if (event.mouseButton.button == sf::Mouse::Right) {
                //    float mouseX = event.mouseButton.x;
                //    float mouseY = event.mouseButton.y;

                //    // Iterate through the array of customers to check which customer is clicked
                //    for (CustomerEntity* customer : customers) {
                //        if (customer->isClicked(mouseX, mouseY)) {
                //            std::cout << *customer << std::endl; // Output customer stats

                //            if (!customer->isSeated()) {
                //                std::cout << "Would you like to amend this customer's information? (y/n): ";
                //                char response;
                //                std::cin >> response;

                //                if (response == 'y' || response == 'Y') {
                //                    std::cin >> *customer;
                //                }
                //            }
                //            else {
                //                std::cout << "Customer is already seated. Cannot amend information." << std::endl;
                //            }

                //            // Exit the loop once the clicked customer is handled
                //            break;
                //        }
                //    }
                //}


                // Handle right mouse click (for stats display)
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    float mouseX = event.mouseButton.x;
                    float mouseY = event.mouseButton.y;

                    for (CustomerEntity* customer : customers) {
                        if (customer->isClicked(mouseX, mouseY)) {
                            std::cout << *customer << std::endl; // Output customer stats

                            //// Check if the customer has any pending message
                            //std::string message = customer->getMessage();
                            //if (!message.empty()) {
                            //    std::cout << "Message for " << customer->getCustomerID() << ": " << message << std::endl;

                            //    // Call the parseMessages function to apply message changes to the customer
                            //    customer->parseMessages();

                            //    // After processing, clear the message
                            //    customer->setMessage(std::string(""));
                            //}
                            //else {
                            //    std::cout << "No pending commands for " << customer->getCustomerID() << std::endl;
                            //}
                        }
                    }
                }
            }
        }

        window.clear(); // Clear the window

        // Draw waiting area
        waitingArea.draw(window);

        // Draw serving hatch
        servingHatch.draw(window);

        // Draw tables
        table1.draw(window);
        table2.draw(window);
        table3.draw(window);
        table4.draw(window);
        table5.draw(window);
        table6.draw(window);

        // Draw food
        appetizer.draw(window);
        mainCourse.draw(window);
        dessert.draw(window);

        // Draw customers
        customer1.draw(window);
        customer2.draw(window);
        customer3.draw(window);

        // Update customers
        customer1.update();
        customer2.update();
        customer3.update();

        window.display(); // Display the content
    }

    return 0;
}