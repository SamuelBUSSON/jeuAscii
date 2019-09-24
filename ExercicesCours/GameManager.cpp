#include "pch.h"
#include "GameManager.h"


GameManager::GameManager() {

	screenManager = new ScreenManager();
	inputManager = new InputManager();
}


GameManager::~GameManager() {
	delete screenManager;
}

void GameManager::Init() {
	screenManager->Init();
	inputManager->Init();
}

void GameManager::Run() {

	while (!screenManager->GetExitGame()) 	{
		screenManager->SampleDisplay();
		inputManager->Update();
	}
}