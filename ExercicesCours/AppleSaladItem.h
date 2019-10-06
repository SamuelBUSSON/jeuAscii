#pragma once
#include "CraftableItem.h"
class AppleSaladItem :
	public CraftableItem
{
private:
	unsigned int heal = 4;
	unsigned int food = 8;

public:
	AppleSaladItem();
	~AppleSaladItem();

	void OnUnlock() override;
	void OnCraft() override;

	static bool isUnlocked;
};

