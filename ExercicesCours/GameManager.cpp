#include "pch.h"
#include "GameManager.h"

#include "TreeObject.h"
#include "Player.h"

#include <algorithm>



void GameManager::CheckPlayerPosition()
{
	if (player->GetY() >= YDOORTOP && player->GetY() <= YDOORBOT)
	{
		if (player->GetX() >= CAM_WIDTH - 2)
		{
			player->SetX(3);
			ScreenManager::instance().RightMap();
		}
		if (player->GetX() <= 2)
		{
			player->SetX(CAM_WIDTH - 3);
			ScreenManager::instance().LeftMap();
		}
	}

	if (player->GetX() >= XDOORLEFT && player->GetX() <= XDOORRIGHT)
	{
		if (player->GetY() <= 1)
		{
			player->SetY(CAM_HEIGHT - 4);
			ScreenManager::instance().TopMap();
		}

		if (player->GetY() >= CAM_HEIGHT - 3)
		{
			player->SetY(2);
			ScreenManager::instance().BottomMap();
		}
	}
}

bool GameManager::DetectCollision(int x, int y) 
{
	if (GetGameObjectAtCoords(x, y) && GetGameObjectAtCoords(x, y) != player) {
		return true;
	}
	return false;
}


GameManager::GameManager() {
	inputManager = new InputManager();

	player = new Player(CAM_WIDTH / 2, CAM_HEIGHT /2 -10, "Sprite/Player.txt");
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
	gameObjects.push_front(player);

	ScreenManager::instance().Init();
	inputManager->Init();
}

void GameManager::Run() {

	while (!exit_game)
	{
		ScreenManager::instance().ClearScreen();
		ScreenManager::instance().SampleDisplay(GetGameObjects());
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
				if (DetectCollision(player->GetX(), player->GetY())) {
					player->MoveUp();
				}
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


void GameManager::HighlightGameObjectAtCoords(COORD coords) {
	GameObject *gameObject = GetGameObjectAtCoords(coords.X, coords.Y);

	if (gameObject == nullptr) {
		if (highlightedGameObject != nullptr && highlightedGameObjectOldColor != NULL) {
			highlightedGameObject->SetColor(highlightedGameObjectOldColor);
			highlightedGameObject = nullptr;
			highlightedGameObjectOldColor = NULL;
		}
	}
	else if (gameObject != nullptr && gameObject != highlightedGameObject) {
		highlightedGameObjectOldColor = gameObject->GetColor();
		highlightedGameObject = gameObject;
		highlightedGameObject->SetColor(20);
	}
}