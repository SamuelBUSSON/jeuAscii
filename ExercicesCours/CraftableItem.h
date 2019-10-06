#pragma once
#include "Item.h"
class CraftableItem :
	public Item
{
protected:
	std::list<Item *> itemsNeededToCraft;

public:
	CraftableItem();
	~CraftableItem();

	virtual void OnUnlock() = 0;

	void AppendDescriptionWithNeededItems();

	inline const std::list<Item *> GetNeededItems() const { return itemsNeededToCraft; }
	virtual std::list<Item *> GetItemsToCraft() = 0;
};

