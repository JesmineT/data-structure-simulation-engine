#ifndef BOOTS_H
#define BOOTS_H
#include "ShopItem.h"

// Boots is a child class of ShopItem
class Boots : public ShopItem {
private:
    bool hasBootsEffectApplied;

public:
    // Default constructor
    Boots();

    // Method that applies the boots effect to the player, increasing their speed
    void applyEffect(Player* player, Enemy* enemy) override;
};
#endif
