#pragma once

#ifndef DEF_GAMEMANAGER
#define DEF_GAMEMANAGER

#include "ScreenManager.h"
#include "GameObject.h"
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


public:
	GameManager();
	~GameManager();

	void Init();
	void Run();
	std::set<GameObject, ZIndexComparison> GetGameObjects();
};


#endif