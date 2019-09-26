#include "pch.h"
#include "BreakableObject.h"


BreakableObject::BreakableObject(int x, int y, std::string spriteFile, int _health)
: GameObject(x, y, spriteFile), health(_health) {
}

BreakableObject::BreakableObject(int x, int y, std::string spriteFile, int _health, std::string mapName)
	: GameObject(x, y, spriteFile, mapName), health(_health) {
}


BreakableObject::~BreakableObject()
{
}

void BreakableObject::OnClick() {
	health--;
	UpdateDescription();

	if (health < 1) {
		OnBreak();
	}
}