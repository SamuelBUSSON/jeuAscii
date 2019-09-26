#include "pch.h"
#include "StoneObject.h"

#include "GameManager.h"
#include "RockLootObject.h"


StoneObject::StoneObject(int x, int y, std::string spriteFile)
: BreakableObject(x, y, spriteFile, STONE_HEALTH) {
}

StoneObject::StoneObject(int x, int y, std::string spriteFile, std::string mapName)
: BreakableObject(x, y, spriteFile, STONE_HEALTH, mapName) {
}



StoneObject::~StoneObject() {
}

void StoneObject::OnClick() {
	BreakableObject::OnClick();
	//ici peut etre de l'animation
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