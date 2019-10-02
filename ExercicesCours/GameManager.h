#pragma once

#ifndef DEF_GAMEMANAGER
#define DEF_GAMEMANAGER

#include "ScreenManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Player.h"
#include "LootObject.h"

#include <list>
#include <map>

#define YDOORTOP 13
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
	bool isClicking = false;
	bool exit_game = false;

	GameObject *highlightedGameObject;
	int highlightedGameObjectOldColor;

	GameManager();

	Player* player;

	std::list<LootObject *> inventory;

	std::map<int, std::list<GameObject *>> gameObjectsMap;
	//TODO :
	//std::map<int, std::list<GameObject *>> gameObjectsMap;
	
public:
	void CheckPlayerPosition();
	bool DetectCollision(int x, int y);
	~GameManager();

	void Init();
	void Run();
	void Update();


	void AddGameObject(GameObject *gameObject);
	void DestroyGameObject(GameObject *gameObject);
	void DestroyLootObject(GameObject *gameObject);

	void AddLootToInventory(LootObject *lootObject);
	void RemoveLootFromInventory(LootObject *lootObject);

	GameObject* GetGameObjectAtCoords(int x, int y);
	GameObject * GetGameObjectAtCoordsOnMap(int x, int y);
	GameObject * GetGameObjectColliderAtCoordsOnMap(int x, int y);
	void HighlightGameObjectAtCoords(COORD coords);
	void RemoveHighlight();

	void ClickOnCoords(int x, int y);
	std::list<GameObject *> GetGameObjects();

	//std::list<GameObject*> GetGameObjectsByMap(std::string mapName);

	inline GameObject* GetHighlightGameObject() { return highlightedGameObject; }
	inline bool IsClicking() { return isClicking; }
	inline Player* GetPlayer() { return player; }

	//Stats
	bool Heal(int healValue);

	static GameManager& instance()
	{
		static GameManager INSTANCE;
		return INSTANCE;
	}
};


#endif