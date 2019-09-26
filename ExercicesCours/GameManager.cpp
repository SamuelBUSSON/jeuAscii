#include "pch.h"
#include "GameManager.h"

#include "TreeObject.h"
#include "FireCamp.h"
#include "Player.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>


bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

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

bool GameManager::DetectCollision(int x, int y) 
{
	if (GetGameObjectAtCoordsOnMap(x, y) && GetGameObjectAtCoordsOnMap(x, y) != player) {
		return true;
	}
	return false;
}


GameManager::GameManager() {
	inputManager = new InputManager();

	player = new Player(CAM_WIDTH / 2, CAM_HEIGHT /2, "Sprite/Player.txt");
}


GameManager::~GameManager() {
	for (GameObject *object : gameObjects) {
		delete object;
	}
	delete screenManager;
}

void GameManager::Init() {

	std::string path = "Sprite/Maps";
	int fileCount = 0;

	for (const auto & entry : std::filesystem::directory_iterator(path)) 
	{
		std::fstream myfile;
		myfile.open(entry);
		std::string line;

		//myfile << "\n"+ std::to_string(fileCount) << std::endl;

		std::string base_filename = entry.path().generic_string();

		int numberLine = 0;
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

void GameManager::Run() {

	while (!exit_game)
	{
		ScreenManager::instance().ClearScreen();
		ScreenManager::instance().SampleDisplay(GetGameObjectsByMap(ScreenManager::instance().GetCurrentMap()));
		ScreenManager::instance().SetInfo("x : "+ std::to_string(player->GetX()) + " y : " + std::to_string(player->GetY()));
		Update();
	}
}

std::list<GameObject *> GameManager::GetGameObjects() {
	gameObjects.sort(ZIndexComparison());
	return gameObjects;
}

std::list<GameObject *> GameManager::GetGameObjectsByMap(std::string mapName) {

	std::list<GameObject *> gmSort;
	std::list<GameObject *>::iterator itr = gameObjects.begin();

	while (itr != gameObjects.end()) {
		if ((*itr)->GetMapLink() == mapName) {
			gmSort.push_front((*itr));
		}
		if ((*itr) == player) {
			gmSort.push_front((*itr));
		}
		itr++;
	}

	gmSort.sort(ZIndexComparison());

	return gmSort;
}


void GameManager::Update()
{
	INPUT_RECORD InputRecord = inputManager->GetInputEvent();

	switch (InputRecord.EventType)
	{
	case KEY_EVENT:

		if (InputRecord.Event.KeyEvent.bKeyDown) {
			switch (InputRecord.Event.KeyEvent.wVirtualKeyCode)
			{
			case VK_ESCAPE:
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

			CheckPlayerPosition();

		}//switch

		//---------------------------------------------------------------------------------
		break;

	case MOUSE_EVENT: // mouse input 

		mousePosition = InputRecord.Event.MouseEvent.dwMousePosition;

		HighlightGameObjectAtCoords(mousePosition);

		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			/*coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
			coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;*/


		}// mouse 

		break;

	case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
		;
		break;

	case FOCUS_EVENT:  // disregard focus events 

	case MENU_EVENT:   // disregard menu events 

		break;

	default:
		std::cout << "Unknown event type \n";
		break;
	}
}


/*
	Retourne l'objet situé à la position [x, y]
	Si plusieurs objets sont à cette position alors la fonction retourne l'objet le plus bas (le posY le plus élevé)
*/
GameObject* GameManager::GetGameObjectAtCoords(int x, int y) {

	for (GameObject *object : gameObjects) {
		if (object->SpriteIsOnCoords(x, y)) {
			return object;
		}
	}

	return nullptr;
}

GameObject* GameManager::GetGameObjectAtCoordsOnMap(int x, int y) {

	for (GameObject *object : gameObjects) 
	{
		if (object->SpriteIsOnCoordsAndMap(x, y, ScreenManager::instance().GetCurrentMap())) 
		{
			return object;
		}
	}
	return nullptr;
}

GameObject* GameManager::GetGameObjectColliderAtCoordsOnMap(int x, int y) {

	for (GameObject *object : gameObjects)
	{
		if (object->SpriteColliderIsOnCoordsAndMap(x, y, ScreenManager::instance().GetCurrentMap()))
		{
			return object;
		}
	}
	return nullptr;
}




void GameManager::HighlightGameObjectAtCoords(COORD coords) {
	GameObject *gameObject = GetGameObjectAtCoordsOnMap(coords.X, coords.Y);

	if (gameObject == nullptr) {
		RemoveHighlight();
	}
	else {
		RemoveHighlight();
		highlightedGameObject = gameObject;
		ScreenManager::instance().SetInfo(highlightedGameObject->GetDescription());
	}
}

void GameManager::RemoveHighlight() {
	if (highlightedGameObject != nullptr) 
	{
		highlightedGameObject = nullptr;
		ScreenManager::instance().SetInfo("");
	}
}