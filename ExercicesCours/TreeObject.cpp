#include "pch.h"
#include "TreeObject.h"
#include "GameManager.h"
#include "Item.h"
#include "AppleLootObject.h"
#include "StickLootObject.h"

#include <iostream>
#include <time.h>


TreeObject::TreeObject(int x, int y, std::string spriteFile)
: BreakableObject(x, y, spriteFile, TREE_HEALTH) {
	description = "a huge tree";
}

TreeObject::TreeObject(int x, int y, std::string spriteFile, std::string mapName)
	: BreakableObject(x, y, spriteFile, TREE_HEALTH, mapName) {
	description = "a huge tree";
}


TreeObject::~TreeObject() {
}

void TreeObject::OnClick() {
	BreakableObject::OnClick();
}

void TreeObject::UpdateDescription() {
	if (health == 1) {
		description = "a nearly-completely destroyed tree";
	}
	else if (health < 3) {
		description = "a broken tree";
	}
	else if (health < TREE_HEALTH) {
		description = "a huge tree with some cracks";
	}
}

void TreeObject::OnBreak() {
	srand(time(NULL));

	int randPadding1 = (rand() % 5 + 1) - 3;
	int randPadding2 = (rand() % 5 + 1) - 3;
	int randPadding3 = (rand() % 5 + 1) - 3;

	GameManager::Instance().AddGameObject(new AppleLootObject(sprite.width / 2 + posX + randPadding1, sprite.height / 2 + posY - 1, "Sprite/Loot.txt", map_link));
	GameManager::Instance().AddGameObject(new StickLootObject(sprite.width / 2 + posX + randPadding2, sprite.height / 2 + posY, "Sprite/Loot.txt", map_link));
	GameManager::Instance().AddGameObject(new StickLootObject(sprite.width / 2 + posX + randPadding3, sprite.height / 2 + posY + 1, "Sprite/Loot.txt", map_link));
	GameManager::Instance().DestroyGameObject(this);
}