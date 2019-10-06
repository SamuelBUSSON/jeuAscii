#pragma once
#include "CraftableItem.h"
class AppleSaladCraftableItem :
	public CraftableItem
{
public:
	AppleSaladCraftableItem();
	~AppleSaladCraftableItem();

	void OnUse() override;
	void OnUnlock() override;

	std::list<Item *> GetItemsToCraft() override;
};

