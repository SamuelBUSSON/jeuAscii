#include "pch.h"
#include "GameManager.h"


GameManager::GameManager() {

	screenManager = new ScreenManager();
	inputManager = new InputManager();
}


GameManager::~GameManager() {
	delete screenManager;
}

void GameManager::Init() {
	screenManager->Init();
	inputManager->Init();
}

void GameManager::Run() {

	while (!exit_game)
	{
		screenManager->SampleDisplay();
		Update();
	}
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
