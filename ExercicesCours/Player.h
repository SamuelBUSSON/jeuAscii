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

public:
	Player(int x, int y, std::string spriteFile);
	~Player();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
};

#endif