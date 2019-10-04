#include "pch.h"
#include "BreakableObject.h"

#include "ScreenManager.h"

BreakableObject::BreakableObject(int x, int y, std::string spriteFile, int _health)
: GameObject(x, y, spriteFile), health(_health) {
}

BreakableObject::BreakableObject(int x, int y, std::string spriteFile, int _health, std::string mapName)
	: GameObject(x, y, spriteFile, mapName), health(_health) {
}


BreakableObject::~BreakableObject()
{
}

void BreakableObject::OnClick() 
{
	ScreenManager::instance().SetShakeObject(this);

	health--;
	UpdateDescription();

	if (health < 1) {
		OnBreak();
	}
}

void BreakableObject::Shake()
{
	shakeCounter++;

	switch (shakeCounter)
	{
	case 1:
		posX--;
		posY++;
		break;

	case 2:
		posX++;
		posY -= 2;
		break;

	case 3:
		posX++;
		posY += 2;
		break;

	case 4:
		posX--;
		posY--;
		shakeCounter = 0;
		ScreenManager::instance().SetShakeObject(nullptr);
		break;
	default:
		break;
	}
}