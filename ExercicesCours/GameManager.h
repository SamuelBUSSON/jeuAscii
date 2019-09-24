#pragma once

#ifndef DEF_GAMEMANAGER
#define DEF_GAMEMANAGER

#include "ScreenManager.h"
#include "GameObject.h"
#include <set>

class GameManager {
private:
	ScreenManager* screenManager;
	std::set<GameObject> gameObjects;


public:
	GameManager();
	~GameManager();

	void Init();
	void Run();
	std::set<GameObject> GetGameObjects();
};

#endif