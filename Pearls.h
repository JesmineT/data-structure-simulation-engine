#ifndef PEARLS_H
#define PEARLS_H
#include "ShopItem.h"

// Pearls is a child class of ShopItem
class Pearls : public ShopItem {
public:
    // Default constructor
    Pearls();

    // Function to apply the effect of using the pearls on a Princess Customer, boosting player reputation and consuming the item.
    void applyCustomerEffect(Player* player, CustomerEntity* customer) override;
};
#endif