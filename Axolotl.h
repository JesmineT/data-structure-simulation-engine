#ifndef AXOLOTL_H
#define AXOLOTL_H
#include "ShopItem.h"

// Axolotl is a child class of ShopItem
class Axolotl : public ShopItem {
private:
	bool hasAxolotlEffectApplied;

public:
	// Default constructor
	Axolotl();

	// Method that applies the axolotl effect to the enemy, reducing their speed
	void applyEffect(Player* player, Enemy* enemy) override;
};
#endif
