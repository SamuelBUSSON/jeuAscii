#include "pch.h"
#include "GameObject.h"

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>

std::vector<std::string> explode(std::string const & s, char delim)
{
	std::vector<std::string> result;
	std::istringstream iss(s);

	for (std::string token; std::getline(iss, token, delim); )
	{
		result.push_back(std::move(token));
	}

	return result;
}

GameObject::GameObject(int x, int y, std::string spriteFile) {
	posX = x;
	posY = y;
	sprite = LoadSpriteFile(spriteFile);
}

GameObject::GameObject(int x, int y, std::string spriteFile, std::string mapName)
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
		x <= posX + sprite.width &&
		y >= posY &&
		y <= posY + sprite.height
	);
}

bool GameObject::SpriteIsOnCoordsAndMap(int x, int y, std::string map_name)
{
	return (
		x >= posX &&
		x <= posX + sprite.width &&
		y >= posY &&
		y <= posY + sprite.height &&
		map_link == map_name
		);
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
		height,
		color
	};

	inFile.close();

	return spriteReturn;
}

