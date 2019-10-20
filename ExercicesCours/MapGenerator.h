#pragma once

#include <string>



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

