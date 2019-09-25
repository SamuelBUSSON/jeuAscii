#include "pch.h"
#include "TreeObject.h"


TreeObject::TreeObject(int x, int y, std::string spriteFile)
: BreakableObject(x, y, spriteFile, TREE_HEALTH) {
}

TreeObject::TreeObject(int x, int y, std::string spriteFile, std::string mapName)
	: BreakableObject(x, y, spriteFile, TREE_HEALTH, mapName) {
}


TreeObject::~TreeObject() {
}

void TreeObject::OnClick() {
	BreakableObject::OnClick();
	//ici peut etre de l'animation
}

void TreeObject::OnBreak() {

}