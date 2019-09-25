#pragma once

#ifndef DEF_PLAYER
#define DEF_PLAYER

#define PLAYER_HEALTH 10
#define PLAYER_FOOD 10

#include "GameObject.h"


class Player : public GameObject
{
private:
	unsigned int health;
	int food;

	std::string spriteFile = "Sprite/Player.txt";

public:
	Player(int x, int y);
	~Player();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
};

#endif