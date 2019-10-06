#pragma once
#include "Item.h"
class AppleItem :
	public Item
{
private:
	unsigned int heal = 1;
	unsigned int food = 2;

public:
	AppleItem();
	~AppleItem();

	void OnUse() override;
};

