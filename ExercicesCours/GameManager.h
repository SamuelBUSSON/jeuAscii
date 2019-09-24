#pragma once

#ifndef DEF_GAMEMANAGER
#define DEF_GAMEMANAGER

#include "ScreenManager.h"
#include "InputManager.h"

class GameManager {
private:

	ScreenManager* screenManager;
	InputManager* inputManager;
	bool exit_game = false;


public:
	GameManager();
	~GameManager();

	void Init();
	void Run();
	void Update();
};

#endif