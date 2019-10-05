#include "pch.h"
#include "StickLootObject.h"


StickLootObject::StickLootObject(int x, int y, std::string spriteFile, std::string mapLink)
	: LootObject(x, y, spriteFile, mapLink)
{
	name = "wood";
	description = "a stick of wood";
}


StickLootObject::~StickLootObject()
{
}

void StickLootObject::OnUse()
{

}