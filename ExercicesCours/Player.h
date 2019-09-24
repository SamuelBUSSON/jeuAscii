#pragma once
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

