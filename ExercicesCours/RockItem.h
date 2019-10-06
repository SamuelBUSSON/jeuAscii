#pragma once
#include "Item.h"
class RockItem :
	public Item
{
public:
	RockItem();
	~RockItem();

	void OnUse() override;
};

