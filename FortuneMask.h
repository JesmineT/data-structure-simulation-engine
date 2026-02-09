#ifndef FORTUNEMASK_H
#define FORTUNEMASK_H
#include "ShopItem.h"

// FortuneMask is a child class of ShopItem
class FortuneMask : public ShopItem {
private:
	bool hasReducedAttack;

public:
	// Default constructor
	FortuneMask();

	// This method applies the effects of the Fortune Mask item to both the player and the enemy
	void applyEffect(Player* player, Enemy* enemy) override;
};
#endif