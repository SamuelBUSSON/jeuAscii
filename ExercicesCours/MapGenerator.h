#pragma once

#include <string>

#define MAP_WIDTH 70
#define MAP_HEIGHT 37

#define DOOR_LENGTH 11

#define TREE_PER_MAP 3


enum Direction
{
	North,
	East,
	South,
	West,
};

class MapGenerator
{

private:
	MapGenerator();
	int numberOfMap;

public:

	
	std::string basePath = "Sprite/MapTest/";


	~MapGenerator();

	std::string CreateMap();

	static MapGenerator& Instance()
	{
		static MapGenerator INSTANCE;
		return INSTANCE;
	}

	inline int GetNumberOfMap() {return numberOfMap; }
};

