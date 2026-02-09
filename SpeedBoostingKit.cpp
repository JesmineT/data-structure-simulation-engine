#include "SpeedBoostingKit.h"

// SpeedBoostingKit is a child class of ShopItem
// Default constructor
SpeedBoostingKit::SpeedBoostingKit() : ShopItem("Speed Boosting Kit", 30, "Requirements to unlock this item: None.\nEffects: +0.005 of the Player's Speed and -0.005 of the Enemy's Speed when activated.\n\n\033[3mA crucial starter item designed to give you a competitive edge. Use it to boost your speed while reducing your enemy's speed, ensuring a faster and more efficient gameplay experience.\033[0m", "speedboostingkit.png") {
    hasSpeedBoostingKitEffectApplied = false;
}
 
// Function to apply the effect to the player's and enemy's speed, increasing the player's speed by 0.005 and reducing the enemy's speed by 0.005
void SpeedBoostingKit::applyEffect(Player* player, Enemy* enemy) {
    if (player && !hasSpeedBoostingKitEffectApplied) {
        player->setPlayerSpeed(player->getPlayerSpeed() + 0.005f);
        std::cout << "Player Speed increased to: " << player->getPlayerSpeed() << "\n";
    }
    if (enemy && !hasSpeedBoostingKitEffectApplied) {
        enemy->setEnemySpeed(enemy->getEnemySpeed() - 0.005f);
        std::cout << "Enemy Speed decreased to: " << enemy->getEnemySpeed() << "\n";
    }
    hasSpeedBoostingKitEffectApplied = true;
}