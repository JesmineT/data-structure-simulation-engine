#ifndef SHOPITEM_H
#define SHOPITEM_H
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"  
#include "Enemy.h"   
#include "CustomerEntity.h"
#include "VIPCustomer.h"
#include "SeniorCustomer.h"
#include "PrincessCustomer.h"

class ShopItem {
protected:
    std::string name;
    int cost;
    std::string description;
    sf::Texture itemTexture; // Texture for item image
    sf::Sprite itemSprite; // Sprite to display item image

public:
    // Constructor to initialize a shop item
    ShopItem(const std::string& itemName, int itemCost, const std::string& itemDescription, const std::string& textureFile);

    // Getter for item name
    std::string getName() const;

    // Getter for item cost
    int getCost() const;

    // Getter for item description
    std::string getDescription() const;

    // Draw method to render item image
    void draw(sf::RenderWindow& window, float x, float y);

    // Virtual function for applying an item's effect on player and enemy
    virtual void applyEffect(Player* player, Enemy* enemy);

    // Virtual function for applying an item's effect to a customer
    virtual void applyCustomerEffect(Player* player, CustomerEntity* customer);

    // Virtual destructor
    virtual ~ShopItem() = default;
};
#endif
