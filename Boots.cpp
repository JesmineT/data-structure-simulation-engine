#include "Boots.h"

// Boots is a child class of ShopItem
// Default constructor
Boots::Boots() : ShopItem("Boots", 35, "Requirements to unlock this item: Purchase Speed Boosting Kit.\nEffects: +0.2 of the Player's Speed when activated.\n\n\033[3mThese rugged boots give you a solid speed boost, letting you charge forward with confidence!\033[0m", "boots.png") {
    hasBootsEffectApplied = false;
}

// Method that applies the boots effect to the player, increasing their speed by 0.2
void Boots::applyEffect(Player* player, Enemy* enemy) {
    if (player && !hasBootsEffectApplied) {
        player->setPlayerSpeed(player->getPlayerSpeed() + 0.2f);
        hasBootsEffectApplied = true;
        std::cout << "Player Speed increased to: " << player->getPlayerSpeed() << "\n";
    }
}