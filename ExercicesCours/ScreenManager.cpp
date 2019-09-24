#include "pch.h"
#include "ScreenManager.h"


#include <iomanip>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

ScreenManager::ScreenManager() {

	writeHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
}

ScreenManager::~ScreenManager() {

}

void ScreenManager::Init() {

	/*DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;

	SetConsoleMode(readHandle, fdwMode);*/

	SetConsoleWindowInfo(writeHandle, TRUE, &bufferArea);

	SetConsoleScreenBufferSize(writeHandle, bufferSize);
	/*
	CONSOLE_FONT_INFOEX customFont;
	customFont.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	customFont.nFont = 0;
	customFont.dwFontSize.X = 12;
	customFont.dwFontSize.Y = 12;
	customFont.FontFamily = FF_ROMAN;
	customFont.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(writeHandle, false, &customFont);*/

	for (int currentX = 0; currentX < SCREEN_WIDTH; currentX++) {
		for (int currentY = 0; currentY < SCREEN_HEIGHT; currentY++) {
			buffer[currentX + currentY * SCREEN_WIDTH].Char.UnicodeChar = 0x2588;
			//buffer[currentX + currentY * SCREEN_WIDTH].Attributes = FOREGROUND_GREEN;
		}
	}	

	
}


void ScreenManager::SampleDisplay() 
{
	ReadMap();

	SetTextCoord(40, 20, 'o');


	WriteConsoleOutput(writeHandle, buffer, bufferSize, initialBufferCoord, &bufferArea);
}

bool ScreenManager::GetExitGame() {
	return EXITGAME;
}

void ScreenManager::SetTextCoord(int x, int y, char c)
{
	buffer[x + y * SCREEN_WIDTH].Char.UnicodeChar = c;
}

void ScreenManager::SetTextCoord(int x, int y, char c, int color)
{
	buffer[x + y * SCREEN_WIDTH].Char.UnicodeChar = c;
	buffer[x + y * SCREEN_WIDTH].Attributes = color;
}

void ScreenManager::DisplaySpriteFromString(string filename, int coordX, int coordY, int color)
{
	std::ifstream inFile;
	inFile.open(filename);
	std::string line;
	int y = 0;

	char c;
	while (getline(inFile, line)) {
		for (int x = 0; x < line.length(); x++)
		{
			if (line[x] != 'W') {
				SetTextCoord(coordX + x, coordY + y, line[x], color);
			}
			
		}
		y++;
	}
}

void ScreenManager::ReadMap()
{
	std::ifstream inFile;
	inFile.open("Sprite/Map.txt");
	std::string line;
	int numberLine = 0;

	char c;
	while (getline(inFile, line)) {
		if (numberLine >= currentMapCoordY - (CAM_HEIGHT/2) && numberLine <= currentMapCoordY + (CAM_HEIGHT / 2))
		{
			for (int i = 0; i < line.length(); i++)
			{
				if (i >= currentMapCoordX - (CAM_WIDTH / 2) && i <= currentMapCoordX + (CAM_WIDTH / 2))
				{
					SetTextCoord(((CAM_WIDTH / 2) + i% (CAM_WIDTH / 2)), ((CAM_HEIGHT / 2) + numberLine % (CAM_HEIGHT / 2)), line[i], FOREGROUND_RED | FOREGROUND_INTENSITY);
				}
			}
		}

		numberLine++;
	}
}

void ScreenManager::GoLeft()
{
	currentMapCoordX--;
	if (currentMapCoordX <= 0) {
		currentMapCoordX = 0;
	}
}

void ScreenManager::GoRight()
{
	currentMapCoordX++;
}

void ScreenManager::GoDown()
{
	currentMapCoordY++;
}

void ScreenManager::GoUp()
{
	currentMapCoordY--;
	if (currentMapCoordY <= 0) {
		currentMapCoordY = 0;
	}
}



