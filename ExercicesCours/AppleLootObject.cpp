#include "pch.h"
#include "AppleLootObject.h"
#include "GameManager.h"
#include "AppleItem.h"


AppleLootObject::AppleLootObject(int x, int y, std::string spriteFile, std::string mapLink)
	: LootObject(x, y, spriteFile, mapLink)
{
	lootItem = new AppleItem();
	description = "a red apple";
}


AppleLootObject::~AppleLootObject()
{
}