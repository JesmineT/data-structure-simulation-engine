#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// Included this to prevent circular dependencies
// Forward declaration of Restaurant class
class Restaurant;

// Included this to prevent circular dependencies
// Forward declaration of Player class
class Player;

// Struct to group x and y coordinates, improving clarity and organization
struct EnemyPosition {
	float x;
	float y;
};

class Enemy {
private:
	std::string fID; // Enemy ID
	EnemyPosition fPosition; // Position struct
	int fAttack; // Attack power
	sf::CircleShape circle; // Circle shape to represent the enemy
    float fSpeed;  // Speed at which the enemy moves

public:
    // Default constructor
	Enemy();

    // Overloaded constructor
	Enemy(std::string id, EnemyPosition position, float radius, int attack);
	
    // Get & Set for fID
    std::string getID();
    void setID(std::string& id);

    // Get & Set for fPosition
    EnemyPosition getPosition();
    void setPosition(EnemyPosition& position);

    // Get & Set for fAttack
    int getAttack();
    void setAttack(int attack);

    // Get Enemy's cirlce
    sf::CircleShape getCircle();

    // Get & Set for speed
    float getEnemySpeed() const;
    void setEnemySpeed(float speed);

    // Draw the enemy to the SFML window
    void draw(sf::RenderWindow& window);

    // Method to chase player
    void chase(Player *player, const Restaurant &restaurant);

    // Method to attack the player reputation
    void attackPlayerReputation();

    // Method to get the global bounds of the enemy
    sf::FloatRect getGlobalBounds() const;

    // Destructor
    ~Enemy();
};
#endif

