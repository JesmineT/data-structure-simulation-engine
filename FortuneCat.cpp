#include "FortuneCat.h"

// FortuneCat is a child class of ShopItem
// Default constructor
FortuneCat::FortuneCat() : ShopItem("Fortune Cat", 35, "Requirements to unlock this item: Purchase Reputation Boosting Kit.\nEffects: +5 Reputation Points every 10 seconds when activated.\n\n\033[3mThe Fortune Cat brings a steady stream of luck to your establishment, attracting good fortune and raising your reputation, one paw at a time.\033[0m", "fortunecat.png") {
    hasFortuneCatEffectApplied = false;
}

// This method applies the effect of the FortuneCat item to the player
// It boosts the player's reputation by +5 points every 10 seconds when activated
void FortuneCat::applyEffect(Player* player, Enemy* enemy) {
    if (player && !hasFortuneCatEffectApplied) {
        player->setHasFortuneCat(true);
        hasFortuneCatEffectApplied = true;
        std::cout << "Fortune Cat acquired!\n";
    }
}