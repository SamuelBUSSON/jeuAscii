#pragma once
#include "LootObject.h"
class StickLootObject :
	public LootObject
{
public:
	StickLootObject(int x, int y, std::string spriteFile, std::string mapLink);
	~StickLootObject();

	inline std::string GetDescription() const override { return "a stick of wood"; }
	inline std::string GetName() const override { return "wood"; }
};

