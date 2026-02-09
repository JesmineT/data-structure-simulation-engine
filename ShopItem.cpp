#include "ShopItem.h"

// Constructor to initialize a shop item
ShopItem::ShopItem(const std::string& itemName, int itemCost, const std::string& itemDescription, const std::string& textureFile)
    : name(itemName), cost(itemCost), description(itemDescription) {

    // Load texture from file
    if (!itemTexture.loadFromFile(textureFile)) {
        std::cerr << "Error loading texture for " << itemName << " from " << textureFile << "\n";
    }
    else {
        itemSprite.setTexture(itemTexture);
    }
}

// Getter for item name
std::string ShopItem::getName() const { 
	return name; 
}

// Getter for item cost
int ShopItem::getCost() const { 
	return cost; 
}

// Getter for item description
std::string ShopItem::getDescription() const {
    return description;
}

// Draw method to render item image
void ShopItem::draw(sf::RenderWindow& window, float x, float y) {
    itemSprite.setPosition(x, y); // Set position
    window.draw(itemSprite); // Draw sprite
}

// Virtual function for applying an item's effect on player and enemy
void ShopItem::applyEffect(Player* player, Enemy* enemy) {
    // (to be overridden in child classes)
}

// Virtual function for applying an item's effect to a customer
void ShopItem::applyCustomerEffect(Player* player, CustomerEntity* customer) {
    // (to be overridden in child classes)
}
