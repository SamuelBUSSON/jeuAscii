#include "pch.h"
#include "StickLootObject.h"
#include "WoodItem.h"

StickLootObject::StickLootObject(int x, int y, std::string spriteFile, std::string mapLink)
	: LootObject(x, y, spriteFile, mapLink)
{
	lootItem = new WoodItem();
	description = "a stick of wood";
}


StickLootObject::~StickLootObject()
{
}