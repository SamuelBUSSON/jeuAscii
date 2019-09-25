#pragma once

#ifndef DEF_SCREENMANAGER
#define DEF_SCREENMANAGER

#include <iomanip>
#include <fstream>

#include <windows.h>
#include <iostream>
#include <string>

#define SCREEN_WIDTH 100
#define SCREEN_HEIGHT 40

#define CAM_WIDTH 70
#define CAM_HEIGHT 40

struct CurrentMap
{
	std::string currentMapName;
	std::string topMap;
	std::string rightMap;
	std::string bottomMap;
	std::string leftMap;
};

class ScreenManager {

private:
	bool EXITGAME = false;

	HANDLE writeHandle;
	HANDLE readHandle;


	CHAR_INFO buffer[SCREEN_WIDTH * SCREEN_HEIGHT];

	COORD bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD initialBufferCoord = { 0, 0 };
	SMALL_RECT bufferArea = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	CurrentMap cm;

	int playerPosX = CAM_WIDTH /2;
	int playerPosY = CAM_HEIGHT/2;

	int cameraPosX = playerPosX - CAM_WIDTH / 2;
	int cameraPosY = playerPosY - CAM_HEIGHT / 2;



public:
	ScreenManager();
	~ScreenManager();

	void Init();

	void ClearScreen();

	void SampleDisplay();
	bool GetExitGame();
	//void Update();
	void SetTextCoord(int x, int y, char c);
	char GetTextCoord(int x, int y);
	void SetTextCoord(int x, int y, char c, int color);
	void Clear();
	void DisplaySpriteFromString(std::string filename, int coordX, int coordY, int color);
	void ReadMap();


	void GoLeft();
	void GoRight();
	void GoUp();
	void DisplayPlayer();
	void GoDown();

};

#endif