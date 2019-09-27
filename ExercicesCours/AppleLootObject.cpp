#include "pch.h"
#include "AppleLootObject.h"

/**
* @brief : Constructor for Apple
* @param x : This pos on X axis
* @param y : This pos on Y axis
*
* @param spriteFile : This sprite
* @param mapLink : The map where object is
**/

AppleLootObject::AppleLootObject(int x, int y, std::string spriteFile, std::string mapLink)
	: LootObject(x, y, spriteFile, mapLink)
{
	description = "a red apple";
}


AppleLootObject::~AppleLootObject()
{
}
