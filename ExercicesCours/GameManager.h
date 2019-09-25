#pragma once

#ifndef DEF_GAMEMANAGER
#define DEF_GAMEMANAGER

#include "ScreenManager.h"
#include "GameObject.h"
#include "InputManager.h"

#include <list>



struct ZIndexComparison {
	inline bool const operator()(const GameObject *objectA, const GameObject *objectB) {
		return (objectA->GetY() > objectB->GetY());
	}
};



class GameManager {
private:
	ScreenManager* screenManager;
	std::list<GameObject *> gameObjects;

	InputManager* inputManager;
	COORD mousePosition;
	bool exit_game = false;

	GameObject *highlightedGameObject;
	int highlightedGameObjectOldColor;
	
public:
	GameManager();
	~GameManager();

	void Init();
	void Run();
	void Update();

	GameObject* GetGameObjectAtCoords(int x, int y);
	void HighlightGameObjectAtCoords(COORD coords);
	std::list<GameObject *> GetGameObjects();
};


#endif