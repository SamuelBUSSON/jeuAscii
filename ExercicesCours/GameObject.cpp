#include "pch.h"
#include "GameObject.h"


GameObject::GameObject(int x, int y) 
: posX(x), posY(y) {
}


GameObject::~GameObject() {

}

void GameObject::Init() {

}

void GameObject::OnClick() {

}

bool GameObject::HitboxIsOnCoords(int x, int y) {
	return (
		x >= hitbox.originX &&
		x <= hitbox.originX + hitbox.width &&
		y >= hitbox.originY &&
		y <= hitbox.originY + hitbox.height
	);
}
