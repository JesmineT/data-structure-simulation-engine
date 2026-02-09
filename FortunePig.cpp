#include "FortunePig.h"

// FortunePig is a child class of ShopItem
// Default constructor
FortunePig::FortunePig() : ShopItem("Fortune Pig", 40, "Requirements to unlock this item: Purchase Fortune Cat.\nEffects: +7 Reputation Points every 10 seconds when activated.\n\n\033[3mThe Fortune Pig promises greater rewards with each snort, adding a touch of prosperity to your restaurant and boosting your reputation bit by bit.\033[0m", "fortunepig.png") {
    hasFortunePigEffectApplied = false;
}

// This method applies the effect of the FortunePig item to the player
// It boosts the player's reputation by +7 points every 10 seconds when activated
void FortunePig::applyEffect(Player* player, Enemy* enemy) {
    if (player && !hasFortunePigEffectApplied) {
        player->setHasFortunePig(true);
        hasFortunePigEffectApplied = true;
        std::cout << "Fortune Pig acquired!\n";
    }
}