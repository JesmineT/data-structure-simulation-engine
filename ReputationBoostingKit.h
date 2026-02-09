#ifndef REPUTATIONBOOSTINGKIT_H
#define REPUTATIONBOOSTINGKIT_H

#include "ShopItem.h"

class ReputationBoostingKit : public ShopItem {
public:
	ReputationBoostingKit();
	void applyCustomerEffect(Player* player, CustomerEntity* customer) override;
};
#endif
