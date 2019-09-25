#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(int x, int y, std::string spriteFile) {
	posX = x;
	posY = y;
	sprite.spriteFile = spriteFile;
}


GameObject::~GameObject() {

}

void GameObject::Init() {

}

void GameObject::OnClick() {

}

bool GameObject::SpriteIsOnCoords(int x, int y) {
	return (
		x >= 0 &&
		x <= sprite.width &&
		y >= 0 &&
		y <= sprite.height
	);
}
