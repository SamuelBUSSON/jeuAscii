#pragma once
#include "LootObject.h"
class AppleLootObject :
	public LootObject
{
private:
	int heal = 1;
	int food = 2;
public:
	AppleLootObject(int x, int y, std::string spriteFile, std::string mapLink);
	~AppleLootObject();

	void OnUse() override;
};

