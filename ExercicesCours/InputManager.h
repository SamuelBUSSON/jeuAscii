#pragma once

#ifndef DEF_INPUTMANAGER
#define DEF_INPUTMANAGER

#include <iomanip>
#include <fstream>

#include <windows.h>
#include "ScreenManager.h"

#include <iostream>
#include <string>


class InputManager
{

private :
	HANDLE readHandle;

	COORD mousePosition;
	INPUT_RECORD InputRecord;
	DWORD Events;

	ScreenManager* sm;


public:
	InputManager();
	~InputManager();

	void Init();
	inline COORD GetMousePosition() const { return mousePosition; }
	INPUT_RECORD GetInputEvent();

};

#endif