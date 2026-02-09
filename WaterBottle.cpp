#include "WaterBottle.h"

// WaterBottle is a child class of ShopItem
// Default constructor
WaterBottle::WaterBottle() : ShopItem("Water Bottle", 35, "Requirements to unlock this item: Purchase Reputation Boosting Kit.\nEffects: +40 Reputation Points when activated and the next time player collides with a Senior Customer.\n\n\033[3mSenior Customers appreciate a complimentary drink that lets them refresh without any health concerns...\033[0m", "waterbottle.png") {}

// Function to apply the effect of using a water bottle on a Senior Customer, boosting player reputation and consuming the item.
void WaterBottle::applyCustomerEffect(Player* player, CustomerEntity* customer) {
    // Attempt to cast the generic CustomerEntity* to a specific SeniorCustomer*.
    // If the customer is not a SeniorCustomer, this cast will result in nullptr.
    SeniorCustomer* seniorCustomer = dynamic_cast<SeniorCustomer*>(customer);
    
    // Check if the dynamic cast was successful (i.e., the customer is a SeniorCustomer).
    if (seniorCustomer) {
        int currentReputation = player->getPlayerReputation();
        player->setPlayerReputation(currentReputation + 40);
        std::cout << "Player's reputation boosted by 40 for giving a water bottle to the Senior Customer!" << std::endl;

        // Remove the water bottle item from the player's bag after it has been used.
        player->removeItemFromBag("Water Bottle");
    }
}