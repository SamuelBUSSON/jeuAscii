#pragma once

#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "GameObject.h"


class Player : public GameObject
{
private:
	const unsigned int MAX_HEALTH = 12;
	const unsigned int MAX_FOOD = 12;
	const unsigned int FOOD_BONUS = 4;


	unsigned int health;
	unsigned int food;

public:
	Player(int x, int y, std::string spriteFile);
	~Player();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void DrawPos();


	/* STATS */
	inline unsigned const int GetHealth() const { return health; }
	inline unsigned const int GetMaxHealth() const { return MAX_HEALTH; }

	inline unsigned const int GetFood() const { return food > MAX_FOOD ? MAX_FOOD : food; }
	inline unsigned const int GetMaxFood() const { return MAX_FOOD; }

	bool Heal(int healValue);
	bool Eat(int foodValue);
};

#endif