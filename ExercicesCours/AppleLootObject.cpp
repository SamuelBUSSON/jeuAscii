#include "pch.h"
#include "AppleLootObject.h"
#include "GameManager.h"
#include "AppleItem.h"


AppleLootObject::AppleLootObject(int x, int y, std::string spriteFile, std::string mapLink)
	: LootObject(x, y, spriteFile, mapLink)
{
	description = "a red apple";
}


AppleLootObject::~AppleLootObject()
{
}

void AppleLootObject::SetLootItem()
{
	lootItem = new AppleItem();
}