#pragma once
#include "GameObject.h"
#include "Item.h"
class LootObject : public GameObject
{
protected:
	std::string name;
	Item *lootItem;

public:
	LootObject(int x, int y, std::string spriteFile, std::string mapLink);
	~LootObject();
	void OnClick() override;
	const std::string GetName() const { return name; }

	virtual void SetLootItem() = 0;
};