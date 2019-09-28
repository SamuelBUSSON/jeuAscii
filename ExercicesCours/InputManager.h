#pragma once

#ifndef DEF_INPUTMANAGER
#define DEF_INPUTMANAGER

#include <windows.h>
#include "ScreenManager.h"

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
	bool IsInput();
	inline COORD GetMousePosition() const { return mousePosition; }
	INPUT_RECORD GetInputEvent();

};

#endif