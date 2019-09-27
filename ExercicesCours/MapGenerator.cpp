#include "pch.h"
#include "MapGenerator.h"


#include <iostream>
#include <fstream>  
#include <string>  
#include <filesystem>  

#include "GameManager.h"
#include "TreeObject.h"

void SetCharAtCoord(int x, int y, std::string &s, char c)
{	
	s[x + (y * (MAP_WIDTH + 1))] = c;
}

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

	for (int i = 0; i < TREE_PER_MAP; i++)
	{
		int x = rand() % (3 + MAP_WIDTH - 19);
		int y = rand() % (3 + MAP_HEIGHT - 12);

		GameManager::Instance().AddGameObject(new TreeObject(x, y, "Sprite/Tree.txt", returnValue));
	}

	

	//SetCharAtCoord(x, y, map, 'T');

	outfile << map << std::endl;

	outfile.close();

	numberOfMap++;

	return returnValue;
}
