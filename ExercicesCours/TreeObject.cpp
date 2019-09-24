#include "pch.h"
#include "TreeObject.h"


TreeObject::TreeObject(int x, int y)
: BreakableObject(x, y, TREE_HEALTH) {
}


TreeObject::~TreeObject() {
}

void TreeObject::OnClick() {
	BreakableObject::OnClick();
	//ici peut etre de l'animation
}

void TreeObject::OnBreak() {

}