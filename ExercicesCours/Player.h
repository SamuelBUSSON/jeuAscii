#pragma once

#ifndef DEF_PLAYER
#define DEF_PLAYER

#define PLAYER_MAX_HEALTH 12
#define PLAYER_MAX_FOOD 10

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
	void DrawPos();

	inline unsigned const int GetHealth() const { return health; }
	bool Heal(int healValue);
};

#endif