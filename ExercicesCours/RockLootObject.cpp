#include "pch.h"
#include "RockLootObject.h"
#include "RockItem.h"

RockLootObject::RockLootObject(int x, int y, std::string spriteFile, std::string mapLink)
: LootObject(x, y, spriteFile, mapLink)
{
	lootItem = new RockItem();
	description = "a little rock";
}


RockLootObject::~RockLootObject()
{
}