#include "Cigarettes.h"

// Cigarettes is a child class of ShopItem
Cigarettes::Cigarettes() : ShopItem("Cigarettes", 40, "Requirements to unlock this item: Purchase Water Bottle.\nEffects: +50 Reputation Points when activated and the next time player collides with a VIP Customer.\n\n\033[3mVIP Customers appreciate a fine smoke now and then... because sometimes, indulgence is the mark of true luxury.\033[0m", "cigarettes.png") {}

// Function to apply the effect of using the cigarettes on a VIP Customer, boosting player reputation and consuming the item.
void Cigarettes::applyCustomerEffect(Player* player, CustomerEntity* customer) {
    // Attempt to cast the generic CustomerEntity* to a specific VIPCustomer*.
    // If the customer is not a VIPCustomer, this cast will result in nullptr.
    VIPCustomer* vipCustomer = dynamic_cast<VIPCustomer*>(customer);

    // Check if the dynamic cast was successful (i.e., the customer is a VIPCustomer).
    if (vipCustomer) {
        int currentReputation = player->getPlayerReputation();
        player->setPlayerReputation(currentReputation + 50);
        std::cout << "Player's reputation boosted by 50 for passing some cigarettes to the VIP Customer!" << std::endl;

        // Remove the cigarettes item from the player's bag after it has been used.
        player->removeItemFromBag("Cigarettes");
    }
}