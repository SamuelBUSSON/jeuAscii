#include "pch.h"
#include "ScreenManager.h"
#include "GameManager.h"

int main()
{

	GameManager::instance().Init();
	GameManager::instance().Run();
}

