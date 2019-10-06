#pragma once
#include "Item.h"
class CraftableItem :
	public Item
{
public:
	CraftableItem();
	~CraftableItem();

	virtual void OnCraft() = 0;
};

