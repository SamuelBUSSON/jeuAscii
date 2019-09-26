#include "pch.h"
#include "ScreenManager.h"


#include <iomanip>
#include <fstream>
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>

#include "GameManager.h"
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

int GetColorByChar(char const c) 
{
	switch (c)
	{
	case 'G':
		return 0x0A;	//Light Green
	case 'B':
		return 0x09;	//Light Blue
	case 'R':
		return 0x0C;	//Light Red
	case 'H':
		return 0x0F;	//White
	case 'C':
		return 0x0B;	//Cyan
	case 'Y':
		return 0x06;	//Dark Yellow
	case 'E':
		return 0x08;	//White

	case 'V':
		return 0x0E;	//Yellow Flash

	case 'r':
		return 0xCC;	//Background Red
	case 'p':
		return 0x44;	//Background Red[[==
	case 'g':
		return 0x22;	//Background Green
	case 'b':
		return 0x99;	//Background Blue
	case 'c':
		return 0xBB;	//Background Cyan
	case 'w':
		return 0xFF;	//Background White
	case 'y':
		return 0xEE;	//Background yellow

	default:
		return 0;
		break;
	}
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


void ScreenManager::SetTextColor(int x, int y, int color)
{

	if (x + y * SCREEN_WIDTH <= SCREEN_WIDTH * SCREEN_HEIGHT) {
		buffer[x + y * SCREEN_WIDTH].Attributes = color;
	}

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
		if(y > 0)
		{
				for (int x = 0; x < line.length(); x++)
				{
					if (y < gameObject->GetHeight() + 1)
					{
						if (line[x] != 'W')
						{
							SetTextCoord(gameObject->GetX() + x, gameObject->GetY() + y, line[x], 0);
						}
					}
					else
					{
						if (line[x] != 'W') 
						{
							if (GameManager::instance().GetHighlightGameObject() && GameManager::instance().GetHighlightGameObject() == gameObject)
							{

									SetTextColor(gameObject->GetX() + x, gameObject->GetY() + y - gameObject->GetHeight(), GetColorByChar(line[x]) + 0x80);
							}
							else 
							{
								SetTextColor(gameObject->GetX() + x, gameObject->GetY() + y - gameObject->GetHeight(), GetColorByChar(line[x]));
							}
							
						}
					}
				}
		}
		y++;
	}

	inFile.close();
}

void ScreenManager::ReadMap()
{	
	
	std::ifstream inFile;
	inFile.open(currentMap.currentMapName);
	std::string line;

	int numberLine = 0;	

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
		else 
		{
			for (int x = 0; x < line.length(); x++)
			{
				SetTextCoord(x + 1, numberLine, line[x], line[x] == 'M' ? 0x22 : FOREGROUND_GREEN);
			}
		}
		numberLine++;
	}

	if (inFile) {
		inFile.close();
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

bool ScreenManager::RightMap() {
	if (currentMap.rightMap != " ") {
		currentMap.currentMapName = currentMap.rightMap;
		return true;
	}
	return false;
}

bool ScreenManager::LeftMap() {
	if (currentMap.leftMap != " ") {
		currentMap.currentMapName = currentMap.leftMap;
		return true;
	}
	return false;
}

bool ScreenManager::TopMap() {
	if (currentMap.topMap != " ") {
		currentMap.currentMapName = currentMap.topMap;
		return true;
	}
	return false;
}

bool ScreenManager::BottomMap() {
	if (currentMap.bottomMap != " ") {

		currentMap.currentMapName = currentMap.bottomMap;
		return true;
	}
	return false;
}

void ScreenManager::DisplayGameObjects(std::list<GameObject *> gameObjects) {
	for (GameObject* object : gameObjects) {
		if (object->GetMapLink() == currentMap.currentMapName || object == GameManager::instance().GetPlayer())
		{
			DisplayGameObject(object);
			//object->DrawCollider();			
		}
	}
}

void ScreenManager::WriteInfoPanel(InfoPanel *_infoPanel) {
	int lineJump = 0;

	for (struct Panel *panel : _infoPanel->panels) {
		WriteLineAtCoords(INFO_PANEL_ORIG_X + panel->origX, INFO_PANEL_ORIG_Y + panel->origY + lineJump, _infoPanel->GetDescriptionPanel().header);
		for (struct Line *line : panel->text) {
			WriteLineAtCoords(INFO_PANEL_ORIG_X + panel->origX, INFO_PANEL_ORIG_Y + panel->origY + 1 + lineJump, line);
			lineJump++;
		}
	}
}

void ScreenManager::SetDescription(std::string desc) {
	infoPanel->SetDescription(desc);
}

void ScreenManager::SetInventory(std::list<LootObject *> inventory) {
	infoPanel->SetInventory(inventory);
}

void ScreenManager::WriteLineAtCoords(int x, int y, struct Line line) {
	for (size_t i = 0; i < line.text.length(); i++) {
		buffer[(x + i) + (y * SCREEN_WIDTH)].Char.UnicodeChar = line.text[i];
		buffer[(x + i) + (y * SCREEN_WIDTH)].Attributes = line.color;
	}
}