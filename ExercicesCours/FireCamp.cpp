#include "pch.h"
#include "FireCamp.h"

/**
* @brief : Constructor for FireCamp Object
* @param x : This pos on X axis
* @param y : This pos on Y axis
*
* @param spriteFile : This sprite
**/
FireCamp::FireCamp(int x, int y, std::string spriteFile)
: GameObject(x, y, spriteFile) {
	description = "a fire camp";
}
/**
* @brief : Constructor for FireCamp Object
* @param x : This pos on X axis
* @param y : This pos on Y axis
*
* @param spriteFile : This sprite
* @param mapLink : The map where object is
**/
FireCamp::FireCamp(int x, int y, std::string spriteFile, std::string mapName)
	: GameObject(x, y, spriteFile, mapName) {
	description = "a fire camp";
}


FireCamp::~FireCamp() {
}
