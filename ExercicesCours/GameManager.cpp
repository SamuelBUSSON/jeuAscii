#include "pch.h"
#include "GameManager.h"

#include "TreeObject.h"
#include "Player.h"

#include <algorithm>


GameManager::GameManager() {

	screenManager = new ScreenManager();
	inputManager = new InputManager();
}


GameManager::~GameManager() {
	for (GameObject *object : gameObjects) {
		delete object;
	}
	delete screenManager;
}

void GameManager::Init() {

	gameObjects.push_front(new TreeObject(20, 20, "Sprite/Tree.txt"));
	gameObjects.push_front(new TreeObject(10, 35, "Sprite/Tree.txt"));

	screenManager->Init();
	inputManager->Init();
}

void GameManager::Run() {

	while (!exit_game)
	{
	
		screenManager->ClearScreen();
		screenManager->SampleDisplay(GetGameObjects());
		Update();
	}
}

std::list<GameObject *> GameManager::GetGameObjects() {
	gameObjects.sort(ZIndexComparison());
	return gameObjects;
}


void GameManager::Update()
{
	INPUT_RECORD InputRecord = inputManager->GetInputEvent();

	switch (InputRecord.EventType)
	{
	case KEY_EVENT:

		switch (InputRecord.Event.KeyEvent.wVirtualKeyCode)
		{
		case VK_ESCAPE:
			break;

		case VK_SPACE:

			break;


		case VK_RETURN:

			break;

		case VK_LEFT:
			if (InputRecord.Event.KeyEvent.bKeyDown) {
				screenManager->GoLeft();
			}
			break;

		case VK_RIGHT:
			if (InputRecord.Event.KeyEvent.bKeyDown) {
				screenManager->GoRight();
			}
			break;

		case VK_UP:
			if (InputRecord.Event.KeyEvent.bKeyDown) {
				screenManager->GoUp();
			}
			break;

		case VK_DOWN:
			if (InputRecord.Event.KeyEvent.bKeyDown) {
				screenManager->GoDown();
			}
			break;

		default:


			break;



		}//switch

		//---------------------------------------------------------------------------------
		break;

	case MOUSE_EVENT: // mouse input 

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