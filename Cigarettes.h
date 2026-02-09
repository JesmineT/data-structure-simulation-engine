#ifndef CIGARETTES_H
#define CIGARETTES_H
#include "ShopItem.h"

// Cigarettes is a child class of ShopItem
class Cigarettes : public ShopItem {
public:
    // Default constructor
    Cigarettes();

    // Function to apply the effect of using the cigarettes on a VIP Customer, boosting player reputation and consuming the item.
    void applyCustomerEffect(Player* player, CustomerEntity* customer) override;
};
#endif
