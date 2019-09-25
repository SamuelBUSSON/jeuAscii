#include "pch.h"
#include "BreakableObject.h"


BreakableObject::BreakableObject(int x, int y, std::string spriteFile, int _health)
: GameObject(x, y, spriteFile), health(_health) {
}


BreakableObject::~BreakableObject()
{
}

void BreakableObject::OnClick() {
	health--;

	if (health < 1) {
		OnBreak();
	}
}