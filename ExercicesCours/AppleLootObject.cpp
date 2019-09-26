#include "pch.h"
#include "AppleLootObject.h"


AppleLootObject::AppleLootObject(int x, int y, std::string spriteFile, std::string mapLink)
	: LootObject(x, y, spriteFile, mapLink)
{
	description = "a red apple";
}


AppleLootObject::~AppleLootObject()
{
}
