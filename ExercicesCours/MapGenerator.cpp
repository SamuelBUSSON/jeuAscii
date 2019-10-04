#include "pch.h"
#include "MapGenerator.h"


#include <iostream>
#include <fstream>  
#include <string>  
#include <filesystem>  

#include "GameManager.h"
#include "TreeObject.h"
#include "StoneObject.h"
#include "MonsterObject.h"
#include "Utiles.h"


void CreateDoor(std::string &s, Direction direct) 
{
	switch (direct)
	{
	case North:
		for (int i = MAP_WIDTH/2 - DOOR_LENGTH/2 ; i < MAP_WIDTH/2 + DOOR_LENGTH / 2; i++)
		{
			SetCharAtCoord(i, 1, s, ' ');
		}
		break;

	case South:
		for (int i = MAP_WIDTH/2 - DOOR_LENGTH/2 + 1; i <= MAP_WIDTH/2 + DOOR_LENGTH / 2; i++)
		{
			SetCharAtCoord(i, MAP_HEIGHT, s, ' ');
		}
		break;


	case East:
		for (int i = 1; i <= DOOR_LENGTH / 2; i++)
		{
			SetCharAtCoord(0, MAP_HEIGHT/2 + i - 1, s, ' ');
		}
		break;

	case West:
		for (int i = 1; i <= DOOR_LENGTH / 2; i++)
		{
			SetCharAtCoord(MAP_WIDTH - 1, MAP_HEIGHT / 2 + i - 1, s, ' ');
		}
		break;
	}
}


MapGenerator::MapGenerator()
{
	numberOfMap = std::distance(std::filesystem::directory_iterator{ basePath }, std::filesystem::directory_iterator{});	
}


MapGenerator::~MapGenerator()
{
}

std::string MapGenerator::CreateMap()
{
	std::string returnValue = basePath + "Map" + std::to_string(numberOfMap) + ".txt";

	std::ofstream outfile(returnValue);
	std::string map;

	for (int i = 0; i < MAP_WIDTH; i++)
	{
		map += ' ';
	}
	map += '\n';

	for (int x = 0; x < MAP_HEIGHT; x++)
	{
		for (int y = 0; y < MAP_WIDTH; y++)
		{
			if (x == 0 || x == MAP_HEIGHT-1) 
			{
				map += 'M';
			}
			else {
				if (y == 0 || y == MAP_WIDTH - 1)
				{
					map += 'M';
				}
				else {
					map += ' ';
				}
			}

		}
		if (x != MAP_HEIGHT - 1) {
			map += '\n';
		}
	}

	CreateDoor(map, South);
	CreateDoor(map, North);
	CreateDoor(map, East);
	CreateDoor(map, West);

	int x = 0;
	int y = 0;

	int object_chanceSpawn;

	for (int i = 0; i < rand() % MAX_OBJECT_PER_MAP + MIN_OBJECT_PER_MAP; i++)
	{
		object_chanceSpawn = rand() % 100;

		//50% of object is Tree
		if (object_chanceSpawn < 50) 
		{
			x = rand() % (MAP_WIDTH - 18) + 2;
			y = rand() % (MAP_HEIGHT - 18) + 4;
			GameManager::Instance().AddGameObject(new TreeObject(x, y, "Sprite/Tree.txt", returnValue));
		}

		//35% of object is Stone
		if (object_chanceSpawn >= 50 && object_chanceSpawn < 80 )
		{
			x = rand() % (MAP_WIDTH - 10) + 2;
			y = rand() % (MAP_HEIGHT - 10) + 4;
			GameManager::Instance().AddGameObject(new StoneObject(x, y, "Sprite/Stone.txt", returnValue));
		}

		//15% of object is Monster
		if (object_chanceSpawn >= 80)
		{
			x = rand() % (MAP_WIDTH/2) + 2;
			y = rand() % (MAP_HEIGHT/2) + 4;
			GameManager::Instance().AddMonsterObject(new MonsterObject(x, y, "Sprite/Monster.txt", returnValue));
		}
	}

	//SetCharAtCoord(x, y, map, 'T');

	outfile << map << std::endl;

	outfile.close();

	numberOfMap++;

	return returnValue;
}
