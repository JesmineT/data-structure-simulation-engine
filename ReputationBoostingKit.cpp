#include "ReputationBoostingKit.h"

ReputationBoostingKit::ReputationBoostingKit() : ShopItem("Reputation Boosting Kit", 30, "Requirements to unlock this item: None.\nEffects: +25 Reputation Points when activated and the next time player collides with any Customer.\n\n\033[3mA starter essential for earning goodwill-gain an instant boost in reputation to make a great impression on every customer you meet.\033[0m", "reputationboostingkit.png") {}

void ReputationBoostingKit::applyCustomerEffect(Player* player, CustomerEntity* customer) {
    // Boost the player's reputation regardless of customer type
    int currentReputation = player->getPlayerReputation();
    player->setPlayerReputation(currentReputation + 25);

    std::cout << "Player's reputation boosted by 25 for using the Reputation Boosting Kit on a customer!" << std::endl;

    // Remove the cigarettes item from the player's bag after it has been used.
    player->removeItemFromBag("Reputation Boosting Kit");
}