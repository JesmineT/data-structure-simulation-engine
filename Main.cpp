#include "Storyline.h"
#include "StoryIterator1D.h"
#include "Restaurant.h"
#include "Player.h"
#include "AudioManager.h"
#include <iostream>
#include <conio.h> // For _getch()

int main() {
    AudioManager audioManager;
    
    // Create Storyline objects
    Storyline stories[] = {
        Storyline("- Part 1: Financially Challenged and Loving It -\nYou find yourself in dire need of cash, wandering the rainy streets with a heavy heart. Suddenly, a gust of wind whips through, sending a small paper card slapping against your face, leaving behind a sharp papercut. You curse the universe for this cruel twist of fate.\n"),
        Storyline("- Part 2: The Business Card -\n"
        "============================================\n"
        "|                BLOOD DINER                |\n"
        "|                                           |\n"
        "|               Jobs available!             |\n"
        "|   One sexy waitstaff that won't crumble   |\n"
        "|               under pressure~             |\n"
        "|                                           |\n"
        "|-------------------------------------------|\n"
        "| Contact Information:                      |\n"
        "| Phone: 082-415 353                        |\n"
        "| Email: 102773605@students.swinburne.edu.my|\n"
        "| Jesmine Ting Zi Ching                     |\n"
        "============================================\n"
        "\n"),

        Storyline("- Part 3: Dirt Poor but Dreaming Big -\nYou read the card again, and a dark thought crosses your mind. Should you really go? You're feeling kinda suicidal, but what if this job could change everything? What if it's your last chance to escape this hell? Cashless and clueless, you decide to go for it, fueled by a flicker of hope.\n"),
    };

    // Create a StoryIterator1D
    StoryIterator1D iterator(stories, 3);

    // Main loop for navigating through the storylines
    bool running = true;

    while (running) {
        // Display the current storyline
        (*iterator).display();

        // Check if the iterator is at the last storyline before proceeding
        if (iterator.getIndex() == iterator.getSize() - 1) {
            running = false; // Exit the storyline loop to proceed to the game
        } else {
            // Handle user input with _getch()
            int input = _getch();

    
        if (input == 224) { // Special key prefix (arrow keys)
                input = _getch(); // Get the actual key code
                if (input == 75) {
                    // Left arrow key (ASCII code 75)
                    // Check if the iterator is not at the beginning before moving left
                    if (iterator != iterator.begin()) {
                        --iterator; // Move to the previous storyline
                    } else {
                        std::cout << "Already at the beginning of the story." << std::endl;
                    }
                } else if (input == 77) {
                    // Right arrow key (ASCII code 77)
                    // Check if the iterator is not at the end before moving right
                    if (iterator != iterator.end()) {
                        ++iterator; // Move to the next storyline
                    } else {
                        std::cout << "(Already at the end of the story.)" << std::endl;
                    }
                }
            } else if (input == 27) {
                // Escape key (ASCII code 27)
                running = false; // Exit the loop
                std::cout << "Exiting the storyline navigator." << std::endl;
                return 0; // Exit the program if the user presses 'Esc'
            } else {
                std::cout << "Invalid input. Use the arrow keys or 'Esc'." << std::endl;
            }
        }
    }

    // Retrieve the singleton instance of the Player class using getInstance()
    Player *player = Player::getInstance();

    // Prompt the player to input name & reputation using the overloaded extraction (>>) operator
    std::cin >> *player;

    // Create a Restaurant instance with custom width, height, and title
    Restaurant myRestaurant(1500, 800, "Blood Diner");

    // Run the restaurant game
    myRestaurant.run();

    // After the game loop exits
    audioManager.stopMusic();
    audioManager.stopJumpscareSound();
    std::cout << "Exiting the game." << std::endl;

    return 0;
}