#pragma once
#include "LootObject.h"
class RockLootObject :
	public LootObject
{
public:
	RockLootObject(int x, int y, std::string spriteFile, std::string mapLink);
	~RockLootObject();

	inline std::string GetDescription() const override { return "a small piece of rock"; }
	inline std::string GetName() const override { return "rock"; }
};

