#include "Pearls.h"

// Pearls is a child class of ShopItem
Pearls::Pearls() : ShopItem("Pearls", 40, "Requirements to unlock this item: Purchase Water Bottle.\nEffects: +50 Reputation Points when activated and the next time player collides with a Princess Customer.\n\n\033[3mOther than only indulging in desserts, princesses enjoy pearls too!\033[0m", "pearls.png") {}

// Function to apply the effect of using the pearls on a Princess Customer, boosting player reputation and consuming the item.
void Pearls::applyCustomerEffect(Player* player, CustomerEntity* customer) {
    // Attempt to cast the generic CustomerEntity* to a specific PrincessCustomer*.
    // If the customer is not a PrincessCustomer, this cast will result in nullptr.
    PrincessCustomer* princessCustomer = dynamic_cast<PrincessCustomer*>(customer);
    
    // Check if the dynamic cast was successful (i.e., the customer is a PrincessCustomer).
    if (princessCustomer) {
        int currentReputation = player->getPlayerReputation();
        player->setPlayerReputation(currentReputation + 50);
        std::cout << "Player's reputation boosted by 50 for gifting a pearl to the Princess Customer!" << std::endl;

        // Remove the pearls item from the player's bag after it has been used.
        player->removeItemFromBag("Pearls");
    }
}