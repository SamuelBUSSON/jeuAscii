#pragma once
#include "LootObject.h"
class AppleLootObject :
	public LootObject
{
private:
	int heal = 2;
public:
	AppleLootObject(int x, int y, std::string spriteFile, std::string mapLink);
	~AppleLootObject();

	void OnUse() override;
	inline std::string GetName() const override { return "apple"; }
};

