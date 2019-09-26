#include "pch.h"
#include "RockLootObject.h"


RockLootObject::RockLootObject(int x, int y, std::string spriteFile, std::string mapLink)
: LootObject(x, y, spriteFile, mapLink)
{
	description = "a little rock";
}


RockLootObject::~RockLootObject()
{
}
