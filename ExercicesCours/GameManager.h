#pragma once

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

