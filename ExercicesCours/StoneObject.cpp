#include "pch.h"
#include "StoneObject.h"

#include "GameManager.h"
#include "RockLootObject.h"


StoneObject::StoneObject(int x, int y, std::string spriteFile)
: BreakableObject(x, y, spriteFile, STONE_HEALTH) {
	description = "a big stone";
}

StoneObject::StoneObject(int x, int y, std::string spriteFile, std::string mapName)
: BreakableObject(x, y, spriteFile, STONE_HEALTH, mapName) {
	description = "a big stone";
}

StoneObject::~StoneObject() {
}

void StoneObject::OnClick() {
	BreakableObject::OnClick();
}

void StoneObject::UpdateDescription() {
	if (health == 1) {
		description = "a stone. it is about to explode";
	}
	else if (health < 3) {
		description = "a miserable stone";
	}
	else if (health < 5) {
		description = "a big stone with cracks";
	}
	else if (health < STONE_HEALTH) {
		description = "a big stone with fingerprints";
	}
}

void StoneObject::OnBreak() {
	srand(time(NULL));

	int randPadding1 = (rand() % 5 + 1) - 3;
	int randPadding2 = (rand() % 5 + 1) - 3;
	int randPadding3 = (rand() % 5 + 1) - 3;

	GameManager::instance().AddGameObject(new RockLootObject(sprite.width / 2 + posX + randPadding1, sprite.height / 2 + posY - 1, "Sprite/Loot.txt", map_link));
	GameManager::instance().AddGameObject(new RockLootObject(sprite.width / 2 + posX + randPadding2, sprite.height / 2 + posY, "Sprite/Loot.txt", map_link));
	GameManager::instance().AddGameObject(new RockLootObject(sprite.width / 2 + posX + randPadding3, sprite.height / 2 + posY + 1, "Sprite/Loot.txt", map_link));
	GameManager::instance().AddGameObject(new RockLootObject(sprite.width / 2 + posX + randPadding3, sprite.height / 2 + posY + 2, "Sprite/Loot.txt", map_link));
	GameManager::instance().DestroyGameObject(this);
}