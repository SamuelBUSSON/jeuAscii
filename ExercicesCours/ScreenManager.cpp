#include "pch.h"
#include "ScreenManager.h"


#include <iomanip>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

#include "InfoPanel.h"

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
	currentMap.currentMapName = "Sprite/Maps/Map1.txt";

	infoPanel = new InfoPanel();
}

ScreenManager::~ScreenManager() {
	delete infoPanel;
}

void ScreenManager::Init() {

	SetConsoleWindowInfo(writeHandle, TRUE, &bufferArea);
	SetConsoleScreenBufferSize(writeHandle, bufferSize);

	ReadMap();
	DisplayPlayer();	
}

void ScreenManager::ClearScreen() {
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			SetTextCoord(x, y, ' ', 0);
		}
	}
}


void ScreenManager::SampleDisplay(std::list<GameObject *> gameObjects) 
{
	//cameraPosX = playerPosX - CAM_WIDTH / 2;
	//cameraPosY = playerPosY - CAM_HEIGHT / 2;

	ReadMap();
	DisplayPlayer();
	DisplayGameObjects(gameObjects);
	DrawBorder();

	WriteInfoPanel(infoPanel);

	WriteConsoleOutput(writeHandle, buffer, bufferSize, initialBufferCoord, &bufferArea);

}

bool ScreenManager::GetExitGame() {
	return EXITGAME;
}

void ScreenManager::SetTextCoord(int x, int y, char c)
{
/*	x = x - cameraPosX;
	y = y - cameraPosY;*/

	if (x + y * SCREEN_WIDTH <= SCREEN_WIDTH * SCREEN_HEIGHT) {
		buffer[x + y * SCREEN_WIDTH].Char.UnicodeChar = c;
	}
}

char ScreenManager::GetTextCoord(int x, int y)
{
	return buffer[x + y * SCREEN_WIDTH].Char.UnicodeChar;
}

void ScreenManager::SetTextCoord(int x, int y, char c, int color)
{
	x = x - cameraPosX;
	y = y - cameraPosY;
	
	if (x + y * SCREEN_WIDTH <= SCREEN_WIDTH * SCREEN_HEIGHT) {
		buffer[x + y * SCREEN_WIDTH].Char.UnicodeChar = c;
		buffer[x + y * SCREEN_WIDTH].Attributes = color;
	}

}

void ScreenManager::SetTextCoordFixed(int x, int y, char c, int color)
{
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

void ScreenManager::DisplayGameObject(GameObject *gameObject) {
	std::ifstream inFile;
	inFile.open(gameObject->GetSpriteFileName());
	std::string line;
	int y = 0;

	char c;
	while (getline(inFile, line))
	{
		for (int x = 0; x < line.length(); x++)
		{
			if (line[x] != 'W')
			{
				SetTextCoord(gameObject->GetX() + x, gameObject->GetY() + y, line[x], gameObject->GetColor());
			}
		}
		y++;
	}
}

void ScreenManager::ReadMap()
{	
	
	std::ifstream inFile;
	inFile.open(currentMap.currentMapName);
	std::string line;

	int numberLine = 0;	

	
	
	char c;
	while (getline(inFile, line)) {	

		if (numberLine == 0) 
		{
			vector<string> v = explode(line, ',');
			if (v.size() >= 4) {
				currentMap.topMap = v[0];
				currentMap.rightMap = v[1];
				currentMap.bottomMap = v[2];
				currentMap.leftMap = v[3];

			}
		}



		/*if (numberLine >= playerPosY - CAM_HEIGHT/2 && numberLine <= playerPosY + CAM_HEIGHT/2)
		{*/
			for (int x = 0; x < line.length(); x++)
			{
				/*if(x >= playerPosX - CAM_WIDTH/2 && x <= playerPosX + CAM_WIDTH / 2)
				{*/
					SetTextCoord(x + 1, numberLine, line[x], FOREGROUND_GREEN);
				//}
			}
		//}
		numberLine++;
	}

	
}

void ScreenManager::DrawBorder() {
	//Draw border
	for (int i = 0; i <= CAM_WIDTH + 1; i++)
	{
		for (int y = 0; y < CAM_HEIGHT - 1; y++)
		{
			if (i == 0 || i == CAM_WIDTH + 1 || y == 0 || y == CAM_HEIGHT - 2) {
				SetTextCoordFixed(i, y, ' ', FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			}
		}
	}
}

void ScreenManager::GoLeft()
{
	playerPosX--;
}

void ScreenManager::GoRight()
{
	playerPosX++;
}

void ScreenManager::GoDown()
{
	playerPosY++;
}

void ScreenManager::GoUp()
{
	playerPosY--;
}

void ScreenManager::DisplayPlayer() 
{
	SetTextCoord(playerPosX, playerPosY, 'O', FOREGROUND_RED);
	SetTextCoord(playerPosX-1, playerPosY, '\\', FOREGROUND_RED);
    SetTextCoord(playerPosX+1, playerPosY, '/', FOREGROUND_RED);
}


void ScreenManager::CheckPlayerPosition() 
{
	if (playerPosY >= YDOORTOP && playerPosY <= YDOORBOT)
	{
		if (playerPosX >= CAM_WIDTH - 2) 
		{
			playerPosX = 3;
			currentMap.currentMapName = currentMap.rightMap;
		}
		if (playerPosX <= 2)
		{
			playerPosX = CAM_WIDTH - 3;
			currentMap.currentMapName = currentMap.leftMap;
		}
	}
	
	if (playerPosX >= XDOORLEFT && playerPosX <= XDOORRIGHT) 
	{
		if (playerPosY <= 1) 
		{
			playerPosY = CAM_HEIGHT - 2;
			currentMap.currentMapName = currentMap.topMap;
		}

		if (playerPosY >= CAM_HEIGHT - 1) 
		{
			playerPosY = 2;
			currentMap.currentMapName = currentMap.bottomMap;
		}
	}

	
}

void ScreenManager::DisplayGameObjects(std::list<GameObject *> gameObjects) {
	for (GameObject* object : gameObjects) {
		DisplayGameObject(object);
	}
}

void ScreenManager::WriteInfoPanel(InfoPanel *_infoPanel) {
	std::string text = _infoPanel->GetText();
	for (size_t i = 0; i < text.length(); i++) {
		buffer[(INFO_PANEL_ORIG_X + i) + (INFO_PANEL_ORIG_Y * SCREEN_WIDTH)].Char.UnicodeChar = text[i];
		buffer[(INFO_PANEL_ORIG_X + i) + (INFO_PANEL_ORIG_Y * SCREEN_WIDTH)].Attributes = _infoPanel->GetTextColor();
	}
}

void ScreenManager::SetInfo(std::string infos) {
	infoPanel->SetString(infos);
}
