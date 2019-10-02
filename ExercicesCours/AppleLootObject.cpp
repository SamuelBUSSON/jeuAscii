#include "pch.h"
#include "AppleLootObject.h"
#include "GameManager.h"


AppleLootObject::AppleLootObject(int x, int y, std::string spriteFile, std::string mapLink)
	: LootObject(x, y, spriteFile, mapLink)
{
	description = "a red apple";
}


AppleLootObject::~AppleLootObject()
{
}

void AppleLootObject::OnUse()
{
	if (GameManager::instance().Heal(heal)) {
		GameManager::instance().RemoveLootFromInventory(this);
	}
}