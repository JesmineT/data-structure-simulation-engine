#ifndef HEELS_H
#define HEELS_H
#include "ShopItem.h"

// Heels is a child class of ShopItem
class Heels : public ShopItem {
private:
	bool hasHeelsEffectApplied;

public:
	// Default constructor
	Heels();

	// Method that applies the heels effect to the player, increasing their speed
	void applyEffect(Player* player, Enemy* enemy) override;
};
#endif
