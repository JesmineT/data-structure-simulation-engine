#ifndef SPEEDBOOSTINGKIT_H
#define SPEEDBOOSTINGKIT_H
#include "ShopItem.h"

// SpeedBoostingKit is a child class of ShopItem
class SpeedBoostingKit : public ShopItem {
private:
	bool hasSpeedBoostingKitEffectApplied;
public: 
	// Default constructor
	SpeedBoostingKit();

	// Function to apply the effect to the player's and enemy's speed
	void applyEffect(Player* player, Enemy* enemy);
};
#endif