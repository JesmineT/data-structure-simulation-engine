#include "Butter.h"

// Butter is a child class of ShopItem
// Default constructor
Butter::Butter() : ShopItem("Butter", 35, "Requirements to unlock this item: Purchase Speed Boosting Kit.\nEffects: -0.01 of the Enemy's Speed when activated.\n\n\033[3mSlather this slippery treat on your enemy’s feet, and watch them struggle to catch up as they slide around in confusion.\033[0m", "butter.png") {
    hasButterEffectApplied = false;
}

// Method that applies the butter effect to the enemy, reducing their speed by 0.01
void Butter::applyEffect(Player* player, Enemy* enemy) {
    if (enemy && !hasButterEffectApplied) {
        enemy->setEnemySpeed(enemy->getEnemySpeed() - 0.01f);
        hasButterEffectApplied = true;
        std::cout << "Enemy Speed decreased to: " << enemy->getEnemySpeed() << "\n";
    }
}
