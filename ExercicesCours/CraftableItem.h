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

	virtual void OnCraft() = 0;
	virtual void OnUnlock() = 0;
	void AppendDescriptionWithNeededItems();
	inline const std::list<Item *> GetNeededItems() const { return itemsNeededToCraft; }
};

