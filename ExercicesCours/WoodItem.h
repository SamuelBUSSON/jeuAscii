#pragma once
#include "Item.h"
class WoodItem :
	public Item
{
public:
	WoodItem();
	~WoodItem();

	void OnUse() override;
};

