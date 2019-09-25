#include "pch.h"
#include "GameObject.h"

#include <fstream>

GameObject::GameObject(int x, int y, std::string spriteFile) {
	posX = x;
	posY = y;
	sprite = LoadSpriteFile(spriteFile);
}


GameObject::~GameObject() {

}

void GameObject::Init() {

}

void GameObject::OnClick() {

}

bool GameObject::SpriteIsOnCoords(int x, int y)
{
	return (
		x >= posX &&
		x <= posX + sprite.width &&
		y >= posY &&
		y <= posY + sprite.height
	);
}

Sprite GameObject::LoadSpriteFile(std::string spriteFile)
{
	std::ifstream inFile;
	inFile.open(spriteFile);
	std::string line;

	int width = 0;
	int height = 0;
	int color = 100;

	while (getline(inFile, line))
	{
		width = (line.length() > width) ? line.length() : width;
		height++;
	}

	struct Sprite spriteReturn = {
		spriteFile,
		width,
		height,
		color
	};

	return spriteReturn;
}
