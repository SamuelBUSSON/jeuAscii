#include "pch.h"
#include "StoneObject.h"


StoneObject::StoneObject(int x, int y, std::string spriteFile)
: BreakableObject(x, y, spriteFile, STONE_HEALTH) {
}


StoneObject::~StoneObject() {
}

void StoneObject::OnClick() {
	BreakableObject::OnClick();
	//ici peut etre de l'animation
}

void StoneObject::OnBreak() {

}