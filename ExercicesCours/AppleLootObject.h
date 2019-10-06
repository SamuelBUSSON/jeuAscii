#pragma once
#include "LootObject.h"
class AppleLootObject :
	public LootObject
{
public:
	AppleLootObject(int x, int y, std::string spriteFile, std::string mapLink);
	~AppleLootObject();
};

