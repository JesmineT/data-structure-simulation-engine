#ifndef FORTUNECAT_H
#define FORTUNECAT_H
#include "ShopItem.h"

// FortuneCat is a child class of ShopItem
class FortuneCat : public ShopItem {
private:
    bool hasFortuneCatEffectApplied;

public:
    // Default constructor
    FortuneCat();

    // This method applies the effect of the FortuneCat item to the player
    void applyEffect(Player* player, Enemy* enemy) override;
};
#endif
