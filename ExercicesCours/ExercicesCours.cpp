#include "pch.h"
#include "ScreenManager.h"
#include "GameManager.h"

int main()
{
	GameManager gameManager;

	gameManager.Init();
	gameManager.Run();
}

