#include "pch.h"
#include "LootObject.h"

#include "GameManager.h"

LootObject::LootObject(int x, int y, std::string spriteFile, std::string mapLink)
: GameObject(x, y, spriteFile, mapLink) {
	lootItem = nullptr;
}


LootObject::~LootObject()
{
}

void LootObject::OnClick() {
	SetLootItem();
	if (lootItem != nullptr) {
		GameManager::Instance().AddItemToInventory(lootItem);
	}
	GameManager::Instance().DestroyGameObject(this);
}
