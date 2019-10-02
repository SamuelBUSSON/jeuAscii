#include "pch.h"
#include "LootObject.h"

#include "GameManager.h"

LootObject::LootObject(int x, int y, std::string spriteFile, std::string mapLink)
: GameObject(x, y, spriteFile, mapLink) {
}


LootObject::~LootObject()
{
}

void LootObject::OnClick() {
	GameManager::instance().AddLootToInventory(this);
	GameManager::instance().DestroyLootObject(this);
}

void LootObject::OnUse()
{
}
