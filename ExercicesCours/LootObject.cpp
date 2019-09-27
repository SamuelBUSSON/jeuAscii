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
	GameManager::Instance().AddLootToInventory(this);
	GameManager::Instance().DestroyLootObject(this);
}
