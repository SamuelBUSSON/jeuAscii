#include "pch.h"
#include "InputManager.h"

#include <windows.h>


#include <iostream>
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

bool InputManager::IsInput() 
{
	DWORD numInputs = 0;
	GetNumberOfConsoleInputEvents(readHandle, &numInputs);

	if (numInputs > 0) {
		return true;
	}
	return false;
}


INPUT_RECORD InputManager::GetInputEvent()
{
	ReadConsoleInput(readHandle, &InputRecord, 1, &Events);
	return InputRecord;
}

