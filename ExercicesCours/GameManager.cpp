#include "pch.h"
#include "GameManager.h"

#include "TreeObject.h"
#include "FireCamp.h"
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
	gameObjects.push_front(new FireCamp(10, 8, "Sprite/FireCamp.txt"));
	gameObjects.push_front(new TreeObject(20, 20, "Sprite/Tree.txt"));
	gameObjects.push_front(new TreeObject(25, 25, "Sprite/Tree.txt"));

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

				screenManager->GoLeft();

				break;

			case VK_RIGHT:

				screenManager->GoRight();

				break;

			case VK_UP:

				screenManager->GoUp();

				break;

			case VK_DOWN:
					screenManager->GoDown();
				break;

			default:


				break;

			}
			screenManager->CheckPlayerPosition();
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


void GameManager::HighlightGameObjectAtCoords(COORD coords) {
	GameObject *gameObject = GetGameObjectAtCoords(coords.X, coords.Y);

	if (gameObject == nullptr) {
		RemoveHighlight();
	}
	else {
		RemoveHighlight();
		highlightedGameObjectOldColor = gameObject->GetColor();
		highlightedGameObject = gameObject;
		highlightedGameObject->SetColor(20);

		screenManager->SetInfo(highlightedGameObject->GetDescription());
	}
}

void GameManager::RemoveHighlight() {
	if (highlightedGameObject != nullptr && highlightedGameObjectOldColor != NULL) {
		highlightedGameObject->SetColor(highlightedGameObjectOldColor);
		highlightedGameObject = nullptr;
		highlightedGameObjectOldColor = NULL;

		screenManager->SetInfo("");
	}
}