#include "pch.h"
#include "GameManager.h"


GameManager::GameManager() {

	screenManager = new ScreenManager();
}


GameManager::~GameManager() {
	delete screenManager;
}

void GameManager::Init() {
	screenManager->Init();
}

void GameManager::Run() {

	while (!screenManager->GetExitGame()) 	{
		screenManager->SampleDisplay();
		screenManager->Update();
	}
}