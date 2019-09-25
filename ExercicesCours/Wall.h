#pragma once
#include "GameObject.h"

#include <iomanip>
#include <fstream>

#include <windows.h>
#include <iostream>
#include <string>


class Wall : public GameObject
{

private:
	std::string sprite = "Sprite/Wall.txt";


public:
	Wall();
	~Wall();
};

