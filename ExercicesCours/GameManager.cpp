#include "pch.h"
#include "GameManager.h"
#include <algorithm>


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

std::set<GameObject> GameManager::GetGameObjects() {
	std::sort(gameObjects.begin(), gameObjects.end(), ZIndexCompare);
	return gameObjects;
}

bool ZIndexCompare(GameObject objectA, GameObject objectB) {
	return objectA.GetX() > objectB.GetY();
}