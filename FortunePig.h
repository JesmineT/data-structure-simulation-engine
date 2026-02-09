#ifndef FORTUNEPIG_H
#define FORTUNEPIG_H
#include "ShopItem.h"

// FortunePig is a child class of ShopItem
class FortunePig : public ShopItem {
private:
	bool hasFortunePigEffectApplied;

public:
	// Default constructor
	FortunePig();

	// This method applies the effect of the FortunePig item to the player
	void applyEffect(Player* player, Enemy* enemy) override;
};
#endif