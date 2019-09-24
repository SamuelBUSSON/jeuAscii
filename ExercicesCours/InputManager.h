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

	COORD coord;
	INPUT_RECORD InputRecord;
	DWORD Events;

	ScreenManager* sm;


public:
	InputManager();
	~InputManager();

	void Init();
	void Update();
	INPUT_RECORD GetInputEvent();

};

#endif