#pragma once

#ifndef DEF_GAMEMANAGER
#define DEF_GAMEMANAGER

#include "ScreenManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Player.h"

#include <list>
#include <map>

#define YDOORTOP 14
#define YDOORBOT  22

#define XDOORLEFT 29
#define XDOORRIGHT 40

struct ZIndexComparison {
	inline bool const operator()(const GameObject *objectA, const GameObject *objectB) {
		return ((objectA->GetY() + objectA->GetHeight()) < (objectB->GetY() + objectB->GetHeight()));
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

	GameManager();

	Player* player;

	std::map<int, std::list<GameObject *>> gameObjectsMap;
	
public:
	void CheckPlayerPosition();
	bool DetectCollision(int x, int y);
	~GameManager();

	void Init();
	void Run();
	void Update();

	GameObject* GetGameObjectAtCoords(int x, int y);
	GameObject * GetGameObjectAtCoordsOnMap(int x, int y);
	GameObject * GetGameObjectColliderAtCoordsOnMap(int x, int y);
	void HighlightGameObjectAtCoords(COORD coords);
	void RemoveHighlight();
	std::list<GameObject *> GetGameObjects();

	std::list<GameObject*> GetGameObjectsByMap(std::string mapName);

	inline GameObject* GetHighlightGameObject() { return highlightedGameObject; }

	static GameManager& instance()
	{
		static GameManager INSTANCE;
		return INSTANCE;
	}
};


#endif