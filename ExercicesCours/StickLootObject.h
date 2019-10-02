#pragma once
#include "LootObject.h"
class StickLootObject :
	public LootObject
{
public:
	StickLootObject(int x, int y, std::string spriteFile, std::string mapLink);
	~StickLootObject();

	void OnUse() override;
	inline std::string GetName() const override { return "wood"; }
};

