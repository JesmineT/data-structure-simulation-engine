# BloodDiner
BloodDiner is a C++14 project simulating a restaurant management game with RPG elements. The player manages a restaurant, interacts with various customer types, purchases items, and faces challenges from enemies.

## Features
- **Restaurant Simulation**: Manage tables, waiting areas, serving hatches, and food preparation.
- **Customer Types**: Includes VIP, Princess, Senior, and regular customers, each with unique behaviors.
- **Player and Enemy Mechanics**: Control a player character and interact with enemies.
- **Shop System**: Purchase items (e.g., Butter, Boots, FortuneCat) to gain advantages.
- **Item Effects**: Items like Butter can apply effects to enemies (e.g., reduce speed).
- **Game Progression**: Advance through levels, manage reputation, and boost player abilities.
- **Audio Management**: Integrated music and sound effects.
- **Storyline and Events**: Experience a storyline with event-driven gameplay.

## Installation
1. Clone the repository.
2. Open the solution in Visual Studio 2022.
3. Ensure your environment supports C++14.
4. Build the project using the default configuration.

## Usage
- Run the executable from Visual Studio or the build output directory.
- Use mouse and keyboard to interact with the restaurant, customers, and shop.
- Purchase items in the shop to enhance gameplay.
- Progress through levels and manage your restaurant efficiently.

## File Structure
- `Main.cpp`: Entry point and main game loop.
- `Restaurant.cpp/h`: Core restaurant logic.
- `Player.cpp/h`, `Enemy.cpp/h`: Player and enemy classes.
- `Shop.cpp/h`, `ShopItem.cpp/h`: Shop and item management.
- `Butter.cpp/h`: Example item with effect logic.
- Additional files for customer types, items, and utilities.

## Dependencies
- Standard C++14 libraries.
- SFML (Simple and Fast Multimedia Library) for graphics and audio (if referenced in code).
