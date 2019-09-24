#include "pch.h"
#include "InputManager.h"

#include <iomanip>
#include <fstream>

#include <windows.h>
#include <iostream>
#include <string>

#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 60

InputManager::InputManager()
{
	readHandle = GetStdHandle(STD_INPUT_HANDLE);
}


InputManager::~InputManager()
{

}

void InputManager::Init() {

	DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(readHandle, fdwMode);
}

void InputManager::Update() {
	ReadConsoleInput(readHandle, &InputRecord, 1, &Events);


	switch (InputRecord.EventType) {
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
		

			break;

		case VK_RIGHT:
			

			break;

		case VK_UP:


			break;

		case VK_DOWN:


			break;



		}//switch

		//---------------------------------------------------------------------------------
		break;

	case MOUSE_EVENT: // mouse input 

		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
			coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			

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

	FlushConsoleInputBuffer(readHandle);
}

