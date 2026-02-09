#ifndef BUTTER_H
#define BUTTER_H
#include "ShopItem.h"

// Butter is a child class of ShopItem
class Butter : public ShopItem {
private: 
    bool hasButterEffectApplied;

public:
    // Default constructor
    Butter();

    // Method that applies the butter effect to the enemy, reducing their speed
    void applyEffect(Player* player, Enemy* enemy) override;
};
#endif
