#pragma once

#ifndef DEF_GAMEMANAGER
#define DEF_GAMEMANAGER

#include "ScreenManager.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Player.h"

#include "Item.h"

#include "LootObject.h"
#include "MonsterObject.h"
#include "Node.h"
#include "Graph.h"


#include <list>
#include <map>

#define YDOORTOP 13
#define YDOORBOT  22

#define XDOORLEFT 29
#define XDOORRIGHT 40


#define FRAMERATE 40.0
#define LOOSE_FOOD_TIME 15

struct ZIndexComparison {
	inline bool const operator()(const GameObject *objectA, const GameObject *objectB) {
		return ((objectA->GetY() + objectA->GetHeight()) < (objectB->GetY() + objectB->GetHeight()));
	}
};



class GameManager {
private:
	ScreenManager* screenManager;
	std::list<GameObject *> gameObjects;
	std::list<MonsterObject *> monsterObjects;

	InputManager* inputManager;
	COORD mousePosition;
	bool isClicking = false;
	bool exit_game = false;
	bool game_over = false;

	GameObject *highlightedGameObject;
	int highlightedGameObjectOldColor;

	int timeInSecond = 0;
	bool loose_food = false;

	GameManager();

	Player* player;

	std::list<Item *> inventory;
	std::list<CraftableItem *> crafts;

	std::map<int, std::list<GameObject *>> gameObjectsMap;


	Graph* allMapsGraph = new Graph();
	Node* current_node;
	//TODO :
	//std::map<int, std::list<GameObject *>> gameObjectsMap;
	
public:
	void CheckPlayerPosition();

	void CheckPlayerPositionTest();
	//bool DetectCollision(int x, int y);
	~GameManager();

	void Init();

	void InitTest();

	void Run();
	void Update();


	void AddGameObject(GameObject *gameObject);
	void AddMonsterObject(MonsterObject * monster);
	void DestroyGameObject(GameObject *gameObject);

	void AddItemToInventory(Item *Item);
	void RemoveItemFromInventory(Item *Item, bool update = true);

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

	bool CanCraft(CraftableItem *item);
	bool Craft(CraftableItem *item);
	void UnlockCraft(CraftableItem *item);

	inline Node*  GetCurrentNode() { return current_node; }
	inline void  SetCurrentNode(Node* n) { current_node = n; }
	inline void  GameOver() { game_over = true; }

	inline Graph*  GetGraph() { return allMapsGraph; }
	
	static GameManager& Instance()
	{
		static GameManager INSTANCE;
		return INSTANCE;
	}
};


#endif