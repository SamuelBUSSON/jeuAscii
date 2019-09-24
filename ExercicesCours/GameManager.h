#pragma once

#ifndef DEF_GAMEMANAGER
#define DEF_GAMEMANAGER

#include "ScreenManager.h"

class GameManager {
private:
	ScreenManager* screenManager;



public:
	GameManager();
	~GameManager();

	void Init();
	void Run();
};

#endif