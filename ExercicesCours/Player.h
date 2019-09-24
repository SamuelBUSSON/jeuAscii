#pragma once

#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
};

#endif