#include "pch.h"
#include "FireCamp.h"


FireCamp::FireCamp(int x, int y, std::string spriteFile)
: GameObject(x, y, spriteFile) {
}

FireCamp::FireCamp(int x, int y, std::string spriteFile, std::string mapName)
	: GameObject(x, y, spriteFile, mapName) {
}


FireCamp::~FireCamp() {
}
