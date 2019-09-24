#pragma once

#ifndef DEF_GAMEMANAGER
#define DEF_GAMEMANAGER

#include "ScreenManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include <set>



struct ZIndexComparison {
	inline bool const operator()(const GameObject &objectA, const GameObject &objectB) {
		return (objectA.GetY() > objectB.GetY());
	}
};



class GameManager {
private:
	ScreenManager* screenManager;
	std::set<GameObject, ZIndexComparison> gameObjects;

	InputManager* inputManager;
	bool exit_game = false;


public:
	GameManager();
	~GameManager();

	void Init();
	void Run();
	std::set<GameObject, ZIndexComparison> GetGameObjects();
	void Update();
};


#endif