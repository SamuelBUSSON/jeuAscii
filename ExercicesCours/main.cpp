#include "pch.h"
#include <time.h>

#include "MapGenerator.h"
#include "GameManager.h"

int main()
{
	srand(time(NULL));
	GameManager::Instance().InitTest();
	GameManager::Instance().Run();
}

