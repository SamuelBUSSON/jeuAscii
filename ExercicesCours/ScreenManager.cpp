#include "pch.h"
#include "ScreenManager.h"


#include <iomanip>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>


using namespace std;


const vector<string> explode(const string& s, const char& c)
{
	string buff{ "" };
	vector<string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}

ScreenManager::ScreenManager() {

	writeHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	cm.currentMapName = "Sprite/Maps/Map1.txt";
	
}

ScreenManager::~ScreenManager() {

}

void ScreenManager::Init() {

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

	SetCurrentConsoleFontEx(writeHandle, false, &customFont);
	
	SetCurrentConsoleFontEx(writeHandle, false, &customFont);
	*/

	ReadMap();
	DisplayPlayer();

	
}

void ScreenManager::ClearScreen() {
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			SetTextCoord(x, y, ' ');
		}
	}
}


void ScreenManager::SampleDisplay() 
{
	cameraPosX = playerPosX - CAM_WIDTH / 2;
	cameraPosY = playerPosY - CAM_HEIGHT / 2;

	ReadMap();
	DisplayPlayer();
	WriteConsoleOutput(writeHandle, buffer, bufferSize, initialBufferCoord, &bufferArea);
}

bool ScreenManager::GetExitGame() {
	return EXITGAME;
}

void ScreenManager::SetTextCoord(int x, int y, char c)
{
	buffer[x + y * SCREEN_WIDTH].Char.UnicodeChar = c;
}

char ScreenManager::GetTextCoord(int x, int y)
{
	return buffer[x + y * SCREEN_WIDTH].Char.UnicodeChar;
}

void ScreenManager::SetTextCoord(int x, int y, char c, int color)
{
	x = x - cameraPosX;
	y = y - cameraPosY;

	buffer[x + y * SCREEN_WIDTH].Char.UnicodeChar = c;
	buffer[x + y * SCREEN_WIDTH].Attributes = color;
}

void ScreenManager::Clear() 
{
	for (int currentX = 0; currentX < SCREEN_WIDTH; currentX++) {
		for (int currentY = 0; currentY < SCREEN_HEIGHT; currentY++) {
			buffer[currentX + currentY * SCREEN_WIDTH].Char.UnicodeChar = 0x2588;
		}
	}
}

void ScreenManager::DisplaySpriteFromString(string filename, int coordX, int coordY, int color)
{
	std::ifstream inFile;
	inFile.open(filename);
	std::string line;
	int y = 0;

	char c;
	while (getline(inFile, line)) 
	{
		for (int x = 0; x < line.length(); x++)
		{
			if (line[x] != 'W') 
			{
				SetTextCoord(coordX + x, coordY + y, line[x], color);
			}
		}
		y++;
	}
}

void ScreenManager::ReadMap()
{
	std::ifstream inFile;
	inFile.open("Sprite/Maps/Map1.txt");
	std::string line;
	int numberLine = 0;

	//Draw border
	for (int i = 0; i <= CAM_WIDTH + 1; i++)
	{
		for (int y = 0; y < CAM_HEIGHT -1 ; y++)
		{
			if (i == 0 || i == CAM_WIDTH + 1 || y == 0 || y == CAM_HEIGHT - 2) {
				SetTextCoord(i, y, ' ', BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			}			
		}
	}

	char c;
	while (getline(inFile, line)) {
		if (numberLine == 0) 
		{
			vector<string> v{ explode(line, ',') };
			if (v.size() >= 4) {
				cm.topMap = v[0];
				cm.rightMap = v[1];
				cm.bottomMap = v[2];
				cm.leftMap = v[3];
			}
		}
		else 
		{
			for (int x = 0; x < line.length(); x++)
			{
				SetTextCoord(x + 1, numberLine, line[x], FOREGROUND_GREEN);
			}
		}		
		numberLine++;
	}
}

void ScreenManager::GoLeft()
{
	playerPosX--;
	if (playerPosX <= 1) {
		playerPosX = 1;
	}

	if (GetTextCoord( playerPosX - 1 , playerPosY) == 'M') {
		playerPosX++;
	}

}

void ScreenManager::GoRight()
{
	playerPosX++;
	if (playerPosX >= CAM_WIDTH - 1) {
		playerPosX = CAM_WIDTH - 1;
	}

	if (GetTextCoord(playerPosX + 1, playerPosY) == 'M') {
		playerPosX--;
	}
}

void ScreenManager::GoDown()
{
	playerPosY++;
	if (playerPosY >= CAM_HEIGHT - 3) {
		playerPosY = CAM_HEIGHT - 3;
	}

	if (GetTextCoord(playerPosX, playerPosY) == 'M') {
		playerPosY--;
	}
}

void ScreenManager::GoUp()
{
	playerPosY--;
	if (playerPosY <= 1) {
		playerPosY = 1;
	}

	if (GetTextCoord(playerPosX, playerPosY) == 'M') {
		playerPosY++;
	}
}

void ScreenManager::DisplayPlayer() 
{
	SetTextCoord(playerPosX, playerPosY, 'O', FOREGROUND_RED);
	SetTextCoord(playerPosX-1, playerPosY, '\\', FOREGROUND_RED);
	SetTextCoord(playerPosX+1, playerPosY, '/', FOREGROUND_RED);
}



