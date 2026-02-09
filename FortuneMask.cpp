#include "FortuneMask.h"

// FortuneMask is a child class of ShopItem
// Default constructor
FortuneMask::FortuneMask() : ShopItem("Fortune Mask", 40, "Requirements to unlock this item: Purchase Fortune Cat.\nEffects: +6 Reputation Points every 10 seconds when activated and -1 Reputation Attack by enemy every time when collided.\n\n\033[3mWear this mask, and enemies may just mistake you for one of their own, helping you slip by with less damage and a steady boost to your reputation.\033[0m", "fortunemask.png") {
    hasReducedAttack = false;
}

// This method applies the effects of the Fortune Mask item to both the player and the enemy
// 1. It boosts the player's reputation by +6 points every 10 seconds when activated
// 2. It reduces the enemy's attack power by 1 upon collision with the player
void FortuneMask::applyEffect(Player* player, Enemy* enemy) {
    if (player) {
        player->setHasFortuneMask(true);
        std::cout << "Fortune Mask acquired!\n";
    }

    if (enemy && !hasReducedAttack) {
        int currentAttack = enemy->getAttack();
        enemy->setAttack(currentAttack - 1);
        std::cout << "Enemy's attack decreases from 2 to " << enemy->getAttack() << " after using the Fortune Mask!" << std::endl;
        hasReducedAttack = true;
    }
}
