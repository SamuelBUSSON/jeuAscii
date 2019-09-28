#include "pch.h"
#include "GameManager.h"


#include "TreeObject.h"
#include "FireCamp.h"
#include "StoneObject.h"

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

	/*
	//Folder where all maps are	
	std::string path = "Sprite/MapTest/Map";
	std::string s = "";

	for (int i = 0; i < MapGenerator::Instance().GetNumberOfMap(); i++)
	{
		s = path +  std::to_string(i) + ".txt";
		remove(s.c_str());
	}*/

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
			if (ScreenManager::instance().RightMap()) {
				player->SetX(3);
			}
		}
		if (player->GetX() <= 2)
		{			
			if (ScreenManager::instance().LeftMap()) {
				player->SetX(CAM_WIDTH - 3);
			}			
		}
	}

	if (player->GetX() >= XDOORLEFT && player->GetX() <= XDOORRIGHT)
	{
		if (player->GetY() <= 0)
		{
			if (ScreenManager::instance().TopMap())
			{
				player->SetY(CAM_HEIGHT - 5);
			}
		}

		if (player->GetY() >= CAM_HEIGHT - 4)
		{
			if (ScreenManager::instance().BottomMap()) {
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
			player->SetX(3);
		}
		if (player->GetX() <= 2)
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

	ScreenManager::instance().Init();
	inputManager->Init();
}

void GameManager::InitTest()
{

	RemoveMaps();

	//allMapsGraph = new Graph();

	//Folder where all maps are
	std::string path = "Sprite/MapTest/";
	int fileCount = 0;
	//Count Line of file
	int numberLine(0);
	//Browse the folder and get each file
	for (const auto & entry : std::filesystem::directory_iterator(path))
	{
		fileCount++;
	}

	if (fileCount == 0) 
	{
		SetCurrentNode(new Node(MapGenerator::Instance().CreateMap()));
		current_node->SetGraphPos(Vector2({ 0, 0 }));
		allMapsGraph->AddNode(0, 0, current_node);
		
	}
	

	gameObjects.push_front(player);

	ScreenManager::instance().Init();
	inputManager->Init();

}

/**
* @brief : Run The game (Game Loop)
**/
void GameManager::Run() {

	while (!exit_game)
	{
		ScreenManager::instance().ClearScreen();
		ScreenManager::instance().SampleDisplay(GetGameObjects());
		Update();
	}
}

/**
* @brief : Run The game (Game Loop)
**/

std::list<GameObject *> GameManager::GetGameObjects() {
	gameObjects.sort(ZIndexComparison());
	return gameObjects;
}

/**
* @brief : Get Input Event and manage it
**/
void GameManager::Update()
{
	
	
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

					break;


				case VK_RETURN:

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

			//ScreenManager::instance().SetInfo("x : " + std::to_string(InputRecord.Event.MouseEvent.dwMousePosition.X) + " y : " + std::to_string(InputRecord.Event.MouseEvent.dwMousePosition.Y));

			if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
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
}

/**
* @brief : Destroy gameObject from the game
* @param gameObject : The gameObject to destroy
**/
void GameManager::DestroyGameObject(GameObject *gameObject) {
	std::list<GameObject *>::iterator it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);

	if (it != gameObjects.end()) {
		delete * it;
		gameObjects.erase(it);
	}
}
/**
* @brief : Destroy lootObject from the game
* @param gameObject : The lootObject to destroy
**/
void GameManager::DestroyLootObject(GameObject *gameObject) {
	std::list<GameObject *>::iterator it = std::find(gameObjects.begin(), gameObjects.end(), gameObject);

	if (it != gameObjects.end()) {
		gameObjects.erase(it);
	}
}

/**
* @brief : Add lootObject to player's inventory
* @param lootObject : The lootObject to add
**/
void GameManager::AddLootToInventory(LootObject *lootObject) {
	inventory.push_front(lootObject);
	ScreenManager::instance().SetInventory(inventory);
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

	for (GameObject *object : gameObjects) 
	{
		if (object->SpriteIsOnCoordsAndMap(x, y, current_node->GetMapName()) || (object == player && object->SpriteIsOnCoords(x, y)))
		{
			return object;
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

	if (gameObject == nullptr || gameObject == ScreenManager::instance().GetShakeObject()) {
		RemoveHighlight();
	}
	else {
		RemoveHighlight();
		highlightedGameObject = gameObject;

		ScreenManager::instance().SetDescription(highlightedGameObject->GetDescription());
	}
}
/**
* @brief : Remove the previous highlighted object
**/
void GameManager::RemoveHighlight() {
	if (highlightedGameObject != nullptr) 
	{
		highlightedGameObject = nullptr;

		ScreenManager::instance().SetDescription("");
	}
}

void GameManager::ClickOnCoords(int x, int y) {
	GameObject *gameObject = GetGameObjectAtCoordsOnMap(x, y);

	if (gameObject != nullptr) {
		gameObject->OnClick();
		ScreenManager::instance().SetShakeObject(gameObject);
	}
}
