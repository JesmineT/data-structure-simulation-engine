#include "Heels.h"

// Heels is a child class of ShopItem
// Default constructor
Heels::Heels() : ShopItem("Heels", 40, "Requirements to unlock this item: Purchase Boots.\nEffects: +0.3 of the Player’s Speed when activated.\n\n\033[3mSleek and swift- heels take your speed to the next level with a touch of slayness~ Faster than Boots... guaranteed!\033[0m", "heels.png") {
    hasHeelsEffectApplied = false;
}

// Method that applies the heels effect to the player, increasing their speed by 0.3
void Heels::applyEffect(Player* player, Enemy* enemy) {
    if (player && !hasHeelsEffectApplied) {
        player->setPlayerSpeed(player->getPlayerSpeed() + 0.3f);
        hasHeelsEffectApplied = true;
        std::cout << "Player Speed increased to: " << player->getPlayerSpeed() << "\n";
    }
}