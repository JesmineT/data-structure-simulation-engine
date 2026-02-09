#include "Axolotl.h"

// Axolotl is a child class of ShopItem
// Default constructor
Axolotl::Axolotl() : ShopItem("Axolotl", 40, "Requirements to unlock this item: Purchase Butter.\nEffects: -0.02 of the Enemy’s Speed when activated .\n\n\033[3mThe enemy can't resist the charm of this cute little critter. Equip it to distract and slow them down with sheer adorableness!\033[0m", "axolotl.png") {
    hasAxolotlEffectApplied = false;
}

// Method that applies the axolotl effect to the enemy, reducing their speed by 0.02
void Axolotl::applyEffect(Player* player, Enemy* enemy) {
    if (enemy && !hasAxolotlEffectApplied) {
        enemy->setEnemySpeed(enemy->getEnemySpeed() - 0.02f);
        hasAxolotlEffectApplied = true;
        std::cout << "Enemy Speed decreased to: " << enemy->getEnemySpeed() << "\n";
    }
}
