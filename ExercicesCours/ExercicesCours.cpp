#include "pch.h"
#include "GameManager.h"

#include "MapGenerator.h"

int main()
{
	
	GameManager::Instance().InitTest();
	GameManager::Instance().Run();
}

