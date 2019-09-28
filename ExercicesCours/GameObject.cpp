#include "pch.h"
#include "GameObject.h"

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "ScreenManager.h"


#include "Utiles.h"

GameObject::GameObject(int x, int y, std::string spriteFile)  : shakeCounter(0){
	posX = x;
	posY = y;
	sprite = LoadSpriteFile(spriteFile);
}

GameObject::GameObject(int x, int y, std::string spriteFile, std::string mapName) : shakeCounter(0)
{
	posX = x;
	posY = y;
	sprite = LoadSpriteFile(spriteFile);
	map_link = mapName;
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
		x < posX + sprite.width &&
		y > posY &&
		y <= posY + sprite.height
	);
}

bool GameObject::SpriteIsOnCoordsAndMap(int x, int y, std::string map_name)
{
	return (SpriteIsOnCoords(x, y) && map_link == map_name);
}

bool GameObject::SpriteColliderIsOnCoordsAndMap(int x, int y, std::string map_name)
{
	return (
		x >= colliderStartX &&
		x <= colliderEndX &&
		y >= colliderStartY &&
		y <= colliderEndY &&
		map_link == map_name
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

	getline(inFile, line);

	std::vector<std::string> v = explode(line, ' ');
	if (v.size() >= 6) {
		width = stoi(v[0]);
		height = stoi(v[1]);

		colliderStartX = posX + stoi(v[2]) - 1;
		colliderStartY = posY + stoi(v[3]) - 1;
		colliderEndX = posX + stoi(v[4]) - 1;
		colliderEndY = posY + stoi(v[5]) - 1;
	}



	struct Sprite spriteReturn = {
		spriteFile,
		width,
		height
	};

	inFile.close();

	return spriteReturn;
}

void GameObject::DrawCollider() 
{
	for (int x = colliderStartX; x <= colliderEndX; x++)
	{
		for (int y = colliderStartY; y <= colliderEndY; y++)
		{
			ScreenManager::instance().SetTextCoord(x, y, ' ', BACKGROUND_BLUE);
		}
	}


}

void GameObject::Shake()
{
	shakeCounter++;
	
	switch (shakeCounter)
	{
	case 1:
		posY++;
		break;

	case 2:
		posY -= 2;
		break;

	case 3:
		posY += 2;
		break;

	case 4:
		posY--;
		shakeCounter = 0;
		ScreenManager::instance().SetShakeObject(nullptr);
		break;
	default:
		break;
	}
}

