#ifndef WATERBOTTLE_H
#define WATERBOTTLE_H
#include "ShopItem.h"

// WaterBottle is a child class of ShopItem
class WaterBottle : public ShopItem {
public:
    // Default constructor
    WaterBottle();

    // Function to apply the effect of using a water bottle on a Senior Customer, boosting player reputation and consuming the item.
    void applyCustomerEffect(Player* player, CustomerEntity* customer) override;
};
#endif
