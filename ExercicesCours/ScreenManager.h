#pragma once
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <string>

#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 60

class ScreenManager {

private:
	bool EXITGAME = false;

	HANDLE writeHandle;
	HANDLE readHandle;

	COORD coord;
	INPUT_RECORD InputRecord;
	DWORD Events;


	CHAR_INFO buffer[SCREEN_WIDTH * SCREEN_HEIGHT];

	COORD bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD initialBufferCoord = { 0, 0 };
	SMALL_RECT bufferArea = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };


public:
	ScreenManager();
	~ScreenManager();

	void Init();

	void SampleDisplay();
	bool GetExitGame();
	void Update();
	void SetTextCoord(int x, int y, char c);
	void SetTextCoord(int x, int y, char c, int color);
	void DisplaySpriteFromString(std::string filename, int coordX, int coordY, int color);
};