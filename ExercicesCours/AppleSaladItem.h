#pragma once
#include "Item.h"
class AppleSaladItem :
	public Item
{
public:
	AppleSaladItem();
	~AppleSaladItem();

	void OnUse() override;

	static const unsigned int heal = 4;
	static const unsigned int food = 8;
};

