#pragma once
#include "Item.h"
class AppleItem :
	public Item
{
private:
	int heal = 1;
	int food = 2;

public:
	AppleItem();
	~AppleItem();

	void OnUse() override;
};

