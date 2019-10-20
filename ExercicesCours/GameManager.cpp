#include "pch.h"
#include "GameManager.h"

#include "TreeObject.h"
#include "FireCamp.h"
#include "StoneObject.h"
#include "Item.h"

#include "PrecisionTimer.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>

#include "Utiles.h"
#include <stdio.h>

void RemoveMaps() 
{
	//Folder where all maps are
	std::string path = "Sprite/MapTest/";

	//Browse the folder and get each file
	for (const auto & entry : std::filesystem::directory_iterator(path))
	{
		remove((entry.path().generic_string()).c_str());
	}

	system("exec rm -r Sprite/MapTest/*");
}


/**
* @brief : Check if player is next to door
**/
void GameManager::CheckPlayerPosition()
{
	if (player->GetY() >= YDOORTOP && player->GetY() <= YDOORBOT)
	{
		if (player->GetX() >= CAM_WIDTH - 2)
		{
			if (ScreenManager::Instance().RightMap()) {
				player->SetX(3);
			}
		}
		if (player->GetX() <= 2)
		{			
			if (ScreenManager::Instance().LeftMap()) {
				player->SetX(CAM_WIDTH - 3);
			}			
		}
	}

	if (player->GetX() >= XDOORLEFT && player->GetX() <= XDOORRIGHT)
	{
		if (player->GetY() <= 0)
		{
			if (ScreenManager::Instance().TopMap())
			{
				player->SetY(CAM_HEIGHT - 5);
			}
		}

		if (player->GetY() >= CAM_HEIGHT - 4)
		{
			if (ScreenManager::Instance().BottomMap()) {
				player->SetY(1);
			}
		}
	}
}

/**
* @brief : Check if player is next to door
**/
void GameManager::CheckPlayerPositionTest()
{
	Vector2 v = current_node->GetPos();

	if (player->GetY() >= YDOORTOP && player->GetY() <= YDOORBOT)
	{
		if (player->GetX() >= CAM_WIDTH - 2)
		{
			//RIGHT
			if (current_node->GetNodeAdjacent(East) == nullptr) {
				current_node->AddAdjacent(East, new Node(MapGenerator::Instance().CreateMap()));
			}
			SetCurrentNode(current_node->GetNodeAdjacent(East));
			v.x++;
			player->SetX(2);
		}
		if (player->GetX() <= 1)
		{
			//LEFT
			if (current_node->GetNodeAdjacent(West) == nullptr) {
				current_node->AddAdjacent(West, new Node(MapGenerator::Instance().CreateMap()));
			}
			SetCurrentNode(current_node->GetNodeAdjacent(West));
			v.x--;
			player->SetX(CAM_WIDTH - 3);
		}
	}

	if (player->GetX() >= XDOORLEFT && player->GetX() <= XDOORRIGHT)
	{
		if (player->GetY() <= 0)
		{
			//TOP
			if (current_node->GetNodeAdjacent(North) == nullptr) {
				current_node->AddAdjacent(North, new Node(MapGenerator::Instance().CreateMap()));
			}			
			SetCurrentNode(current_node->GetNodeAdjacent(North));
			v.y++;
			current_node->SetGraphPos(v);
			player->SetY(CAM_HEIGHT - 5);
		}

		if (player->GetY() >= CAM_HEIGHT - 4)
		{
			//BOTTOM
			if (current_node->GetNodeAdjacent(South) == nullptr) {
				current_node->AddAdjacent(South, new Node(MapGenerator::Instance().CreateMap()));
			}
			SetCurrentNode(current_node->GetNodeAdjacent(South));
			v.y--;
			current_node->SetGraphPos(v);
			player->SetY(1);
		}
	}

	player->SetMapLink(current_node->GetMapName());

	allMapsGraph->AddNode(v.x, v.y, current_node);

	current_node->CheckMapAround();

}



GameManager::GameManager() {
	inputManager = new InputManager();
	player = new Player(CAM_WIDTH / 2, CAM_HEIGHT /2, "Sprite/Player.txt");
}


GameManager::~GameManager() {

	for (GameObject *object : gameObjects) {
		delete object;
	}
	gameObjects.clear();

	for (Item *loot : inventory) {
		delete loot;
	}
	inventory.clear();

	delete screenManager;
}
/**
* @brief : Init the game
**/
void GameManager::Init() {

	RemoveMaps();

	//Folder where all maps are
	std::string path = "Sprite/Maps/";
	int fileCount = 0;
	//Count Line of file
	int numberLine(0);
	//Browse the folder and get each file
	for (const auto & entry : std::filesystem::directory_iterator(path)) 
	{
		std::fstream myfile;
		myfile.open(entry, std::ios::out | std::ios::in | std::ios::app);
		std::string line;
		//Get FileName
		std::string base_filename = entry.path().generic_string();

		numberLine = 0;

		while (std::getline(myfile, line))
		{
			if (numberLine > 0) {
				for (int x = 0; x < line.length(); x++)
				{
					switch (line[x])
					{
					case 'T':
						gameObjects.push_front(new TreeObject(x, numberLine, "Sprite/Tree.txt", base_filename));
						break;

					case 'F':
						gameObjects.push_front(new FireCamp(x, numberLine, "Sprite/FireCamp.txt", base_filename));
						break;

					case 'S':
						gameObjects.push_front(new StoneObject(x, numberLine, "Sprite/Stone.txt", base_filename));
						break;

					case 'G':
						gameObjects.push_front(new GameObject(x, numberLine, "Sprite/Monster.txt", base_filename));
						break;

					default:
						break;
					}					
				}
			}
			numberLine++;
		}

		myfile.close();
		fileCount++;
	}

	gameObjects.push_front(player);

	ScreenManager::Instance().Init();
	inputManager->Init();
}

void GameManager::InitTest()
{

	RemoveMaps();

	SetCurrentNode(new Node(MapGenerator::Instance().CreateMap()));
	current_node->SetGraphPos(Vector2({ 0, 0 }));
	allMapsGraph->AddNode(0, 0, current_node);	
	

	gameObjects.push_front(player);

	ScreenManager::Instance().Init();
	inputManager->Init();

}

/**
* @brief : Run The game (Game Loop)
**/
void GameManager::Run() 
{

	//create a timer
	PrecisionTimer timer(FRAMERATE);

	//start the timer
	timer.Start();

	while (!exit_game)
	{
		if (timer.ReadyForNextFrame()) 
		{
			ScreenManager::Instance().ClearScreen();
			ScreenManager::Instance().SampleDisplay(GetGameObjects());
			Update();
		}
	}
}

std::list<GameObject *> GameManager::GetGameObjects() {
	return gameObjects;
}

/**
* @brief : Get Input Event and manage it
**/
void GameManager::Update()
{
	for (auto it : monsterObjects)
	{
		it->Update();
	}

	if (inputManager->IsInput()) {
		INPUT_RECORD InputRecord = inputManager->GetInputEvent();

		switch (InputRecord.EventType)
		{
		case KEY_EVENT:

			if (InputRecord.Event.KeyEvent.bKeyDown) {
				switch (InputRecord.Event.KeyEvent.wVirtualKeyCode)
				{
				case VK_ESCAPE:
					exit_game = true;
					break;

				case VK_SPACE:
					ScreenManager::Instance().SetDisplayState(Game);
					break;


				case VK_F1:
					ScreenManager::Instance().ShowCollider();
					break;

				case VK_LEFT:
					player->MoveLeft();
					break;

				case VK_RIGHT:
					player->MoveRight();
					break;

				case VK_UP:
					player->MoveUp();
					break;

				case VK_DOWN:
					player->MoveDown();
					break;

				default:


					break;

				}
				CheckPlayerPositionTest();
				//CheckPlayerPosition();

			}//switch

			//---------------------------------------------------------------------------------
			break;

		case MOUSE_EVENT: // mouse input 

			mousePosition = InputRecord.Event.MouseEvent.dwMousePosition;


			HighlightGameObjectAtCoords(mousePosition);
			ScreenManager::Instance().HighlightLineAtCoords(mousePosition);

			//ScreenManager::instance().SetInfo("x : " + std::to_string(InputRecord.Event.MouseEvent.dwMousePosition.X) + " y : " + std::to_string(InputRecord.Event.MouseEvent.dwMousePosition.Y));

			if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				if (!isClicking) {
					ClickOnCoords(mousePosition.X, mousePosition.Y);

					isClicking = true;
				}
			}
			else {
				isClicking = false;
			}// mouse 

			break;

		case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
			;
			break;

		case FOCUS_EVENT:  // disregard focus events 

		case MENU_EVENT:   // disregard menu events 

			break;

		default:
			break;
		}
	}
	
}

/**
* @brief : Add Game object to the game
* @param gameObject : The gameObject to add
**/
void GameManager::AddGameObject(GameObject *gameObject) {
	gameObjects.push_front(gameObject);
	gameObjects.sort(ZIndexComparison());
}

/**
* @brief : Add Game object to the game
* @param gameObject : The gameObject to add
**/
void GameManager::AddMonsterObject(MonsterObject *monster) {
	gameObjects.push_front(monster);
	monsterObjects.push_front(monster);
}

/**
* @brief : Destroy gameObject from the game
* @param gameObject : The gameObject to destroy
**/
void GameManager::DestroyGameObject(GameObject *gameObject) {
	std::list<GameObject *>::iterator itr = std::find(gameObjects.begin(), gameObjects.end(), gameObject);

	if (itr != gameObjects.end()) {
		delete * itr;
		gameObjects.erase(itr);
	}
}


void GameManager::AddItemToInventory(Item *item) {
	inventory.push_front(item);
	ScreenManager::Instance().SetInventory(inventory);
	ScreenManager::Instance().SetCrafts(crafts);
}

void GameManager::RemoveItemFromInventory(Item *item, bool update)
{
	std::list<Item *>::iterator itr = std::find(inventory.begin(), inventory.end(), item);

	if (itr != inventory.end()) {
		delete *itr;
		inventory.erase(itr);
	}

	if (update) {
		ScreenManager::Instance().SetInventory(inventory);
		ScreenManager::Instance().SetCrafts(crafts);
	}
}


void GameManager::UnlockCraft(CraftableItem *item)
{
	bool alreadyUnlocked = false;
	for (CraftableItem *craft : crafts) {
		if (craft->GetName() == item->GetName()) {
			alreadyUnlocked = true;
			break;
		}
	}

	if (!alreadyUnlocked) {
		crafts.push_back(item);
		item->OnUnlock();
		ScreenManager::Instance().SetCrafts(crafts);
	}
	else {
		delete item;
	}
}

bool GameManager::Craft(CraftableItem *craftableItem)
{
	if (CanCraft(craftableItem)) {
		for (Item *neededItem : craftableItem->GetNeededItems()) {
			for (Item *inventoryItem : inventory) {
				if (inventoryItem->GetName().compare(neededItem->GetName()) == 0) {
					RemoveItemFromInventory(inventoryItem, false);
					break;
				}
			}
		}

		for (Item *itemToCraft : craftableItem->GetItemsToCraft()) {
			inventory.push_back(itemToCraft);
		}

		ScreenManager::Instance().SetInventory(inventory);
		ScreenManager::Instance().SetCrafts(crafts);
		
		return true;
	}
	else {
		return false;
	}
}

bool GameManager::CanCraft(CraftableItem *craftableItem)
{
	std::map<std::string, std::list<Item*>> countItems;
	for (Item *item : craftableItem->GetNeededItems()) {
		countItems[item->GetName()].push_back(item);
	}

	std::map<std::string, std::list<Item*>> countItemsInventory;
	for (Item *item : inventory) {
		countItemsInventory[item->GetName()].push_back(item);
	}

	size_t enoughItems = 0;
	for (std::pair<std::string, std::list<Item*>> item : countItems) {
		if (countItemsInventory[item.first].size() >= item.second.size()) enoughItems++;
	}

	return (enoughItems == countItems.size());
}


/**
* @brief : Return object on Coord x, y, return the highest object on Y axis
* @return : The object om coord 
**/
GameObject* GameManager::GetGameObjectAtCoords(int x, int y) {

	for (GameObject *object : gameObjects) {
		if (object->SpriteIsOnCoords(x, y)) {
			return object;
		}
	}

	return nullptr;
}

/**
* @brief : Return object on Coord x, y on currentMap, return the highest object on Y axis
* @return : The object on coord
**/
GameObject* GameManager::GetGameObjectAtCoordsOnMap(int x, int y) {

	std::list<GameObject *>::reverse_iterator rIterObject;

	for (rIterObject = gameObjects.rbegin(); rIterObject != gameObjects.rend(); rIterObject++) {
		if ((*rIterObject)->SpriteIsOnCoordsAndMap(x, y, current_node->GetMapName()) || (*rIterObject == player && (*rIterObject)->SpriteIsOnCoords(x, y)))
		{
			return *rIterObject;
		}
	}
	return nullptr;
}

/**
* @brief : Return object on Coord x, y on currentMap if there is collider
* @return : The object on coord
**/
GameObject* GameManager::GetGameObjectColliderAtCoordsOnMap(int x, int y) {

	for (GameObject *object : gameObjects)
	{
		if (object->SpriteColliderIsOnCoordsAndMap(x, y, current_node->GetMapName()))
		{
			return object;
		}
	}
	return nullptr;
}

/**
* @brief : Highlight object on mouse move
* @param coords : The object on coord
**/
void GameManager::HighlightGameObjectAtCoords(COORD coords) {
	GameObject *gameObject = GetGameObjectAtCoordsOnMap(coords.X, coords.Y);

	if (gameObject == nullptr || gameObject == ScreenManager::Instance().GetShakeObject()) {
		RemoveHighlight();
	}
	else {
		RemoveHighlight();
		highlightedGameObject = gameObject;

		ScreenManager::Instance().SetDescription(highlightedGameObject->GetDescription());
	}
}
/**
* @brief : Remove the previous highlighted object
**/
void GameManager::RemoveHighlight() {
	if (highlightedGameObject != nullptr) 
	{
		highlightedGameObject = nullptr;

		ScreenManager::Instance().SetDescription("");
	}
}

void GameManager::ClickOnCoords(int x, int y) {
	GameObject *gameObject = GetGameObjectAtCoordsOnMap(x, y);

	if (gameObject != nullptr) {
		gameObject->OnClick();
		return;
	}

	ScreenManager::Instance().ClickOnCoords(x, y);
}