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
	if (lootItem != nullptr) {
		GameManager::instance().AddItemToInventory(lootItem);
	}
	GameManager::instance().DestroyGameObject(this);
}