#pragma once

#ifndef DEF_INPUTMANAGER
#define DEF_INPUTMANAGER

#include <iomanip>
#include <fstream>

#include <windows.h>

#include <iostream>
#include <string>


class InputManager
{

private :
	HANDLE readHandle;

	COORD coord;
	INPUT_RECORD InputRecord;
	DWORD Events;


public:
	InputManager();
	~InputManager();

	void Init();
	void Update();

};

#endif