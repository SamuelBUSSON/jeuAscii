#include "pch.h"
#include "InputManager.h"

#include <windows.h>


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

INPUT_RECORD InputManager::GetInputEvent()
{
	ReadConsoleInput(readHandle, &InputRecord, 1, &Events);

	return InputRecord;
}

