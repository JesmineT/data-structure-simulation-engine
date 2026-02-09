#include "Enemy.h"
#include "Player.h" // Included here instead to prevent circular dependencies
#include "Restaurant.h" // Included here instead to prevent circular dependencies

// Default constructor
Enemy::Enemy()
    : fID(""),
    fPosition({ 460.0f, 100.0f }), // Initialize fPosition using struct
    fAttack(2),
    fSpeed(0.03) {
    circle.setRadius(20);
    circle.setFillColor(sf::Color::Magenta);
    circle.setPosition(fPosition.x, fPosition.y); // Use fPosition for setting position
}


// Overloaded constructor
Enemy::Enemy(std::string id, EnemyPosition position, float radius, int attack)
    : fID(id), 
    fPosition(position), 
    fAttack(attack),
    fSpeed(0.03) {
    circle.setRadius(radius);
    circle.setFillColor(sf::Color::Magenta);
    circle.setPosition(fPosition.x, fPosition.y); // Use fPosition for setting position
}

// Get for fID
std::string Enemy::getID() {
    return fID;
}

// Set for fID
void Enemy::setID(std::string& id) {
    fID = id;
}

// Get for fPosition
EnemyPosition Enemy::getPosition() {
    return fPosition;
}

// Set for fPosition
void Enemy::setPosition(EnemyPosition& position) {
    fPosition = position;
    circle.setPosition(fPosition.x, fPosition.y);  // Update the circle's position too
}

// Get for fAttack
int Enemy::getAttack() {
    return fAttack;
}

// Set for fAttack
void Enemy::setAttack(int attack) {
    fAttack = attack;
}

// Get Enemy's circle
sf::CircleShape Enemy::getCircle() {
    return circle;
}

// Getter for speed
float Enemy::getEnemySpeed() const {
    return fSpeed;
}

// Setter for speed
void Enemy::setEnemySpeed(float speed) {
    fSpeed = speed;
}

// Method to Draw the Player
void Enemy::draw(sf::RenderWindow& window) {
    window.draw(circle);
}

// Method to chase player
void Enemy::chase(Player* player, const Restaurant& restaurant) {
    // Get the player's position
    sf::Vector2f playerPosition = player->getCircle().getPosition();
    sf::Vector2f enemyPosition = circle.getPosition();

    // Calculate the differences
    float deltaX = playerPosition.x - enemyPosition.x;
    float deltaY = playerPosition.y - enemyPosition.y;

    // Create a new position for potential movement
    sf::Vector2f newPosition = enemyPosition;

    // Move horizontally or vertically depending on which axis has the larger difference
    if (std::abs(deltaX) > std::abs(deltaY)) {
        // Move horizontally
        newPosition.x += (deltaX > 0 ? fSpeed : -fSpeed);
    } 
    else {
        // Move vertically
        newPosition.y += (deltaY > 0 ? fSpeed : -fSpeed);
    }

    // Check if the new position is within the StepTile boundaries
    if (restaurant.isWithinStepTileBoundaries(newPosition)) {
        // Valid move, update position
        circle.setPosition(newPosition);
    } 
    else {
        // Invalid move, try to "push" the enemy closer to the valid area
        // Fine-tune the movement by trying to nudge closer to valid position
        // Move slightly in the opposite direction (backward nudge)
        sf::Vector2f slightAdjustment = newPosition;
        
        if (!restaurant.isWithinStepTileBoundaries(slightAdjustment)) {
            // Adjust horizontally
            slightAdjustment.x = enemyPosition.x + (deltaX > 0 ? -0.1f : 0.1f);
            if (restaurant.isWithinStepTileBoundaries(slightAdjustment)) {
                circle.setPosition(slightAdjustment);
            } 
            else {
                // Adjust vertically if horizontal adjustment doesn't work
                slightAdjustment.x = enemyPosition.x;
                slightAdjustment.y = enemyPosition.y + (deltaY > 0 ? -0.1f : 0.1f);
                if (restaurant.isWithinStepTileBoundaries(slightAdjustment)) {
                    circle.setPosition(slightAdjustment);
                }
            }
        }
    }
}

// Method to attack the player reputation
void Enemy::attackPlayerReputation() {
    Player* player = Player::getInstance();

    if (player) {
        int currentReputation = player->getPlayerReputation();
        player->setPlayerReputation(currentReputation - getAttack());
        std::cout << "Player's reputation is attacked by the Enemy by " << getAttack() << std::endl;
        std::cout << "\n";
    }
}

// Method to get the global bounds of the enemy
sf::FloatRect Enemy::getGlobalBounds() const {
    return circle.getGlobalBounds();
}

// Destructor
Enemy::~Enemy() {}