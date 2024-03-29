#include "pch.h"
#include "ScreenManager.h"

#include <fstream>
#include <windows.h>
#include <string>
#include <vector>

#include "GameManager.h"
#include "InfoPanel.h"


using namespace std;

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


ScreenManager::ScreenManager() : display_state(Menu) {

	writeHandle = GetStdHandle(STD_OUTPUT_HANDLE);

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
	for (int x = 0; x < GAME_SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < GAME_SCREEN_HEIGHT; y++)
		{
			SetTextCoord(x, y, ' ', 0);
		}
	}
}


void ScreenManager::SampleDisplay(std::list<GameObject *> gameObjects) 
{
	switch (display_state)
	{
	case Menu:
		ShowMenu();
		break;
	case Game:
			ReadMap();

			if (shakeObject)
			{
				shakeObject->Shake();
			}

			DisplayGameObjects(gameObjects);
			DrawBorder();

			WriteInfoPanel(infoPanel);
		break;
	case PlayerDead:
		ShowGameOver();
		break;
	default:
		break;
	}

	WriteConsoleOutput(writeHandle, buffer, bufferSize, initialBufferCoord, &bufferArea);
}

bool ScreenManager::GetExitGame() {
	return EXITGAME;
}

void ScreenManager::HighlightLineAtCoords(COORD coords)
{
	infoPanel->HighlightLineAtCoords(coords.X - INFO_PANEL_ORIG_X, coords.Y - INFO_PANEL_ORIG_Y);
}

void ScreenManager::ClickOnCoords(int x, int y)
{
	infoPanel->ClickOnCoords(x - INFO_PANEL_ORIG_X, y - INFO_PANEL_ORIG_Y);
}

void ScreenManager::SetTextCoord(int x, int y, char c)
{
/*	x = x - cameraPosX;
	y = y - cameraPosY;*/

	if (x + y * GAME_SCREEN_WIDTH <= GAME_SCREEN_WIDTH * GAME_SCREEN_HEIGHT) {
		buffer[x + y * GAME_SCREEN_WIDTH].Char.UnicodeChar = c;
	}
}

char ScreenManager::GetTextCoord(int x, int y)
{
	return buffer[x + y * GAME_SCREEN_WIDTH].Char.UnicodeChar;
}

void ScreenManager::SetTextCoord(int x, int y, char c, int color)
{
	if (x + y * GAME_SCREEN_WIDTH <= GAME_SCREEN_WIDTH * GAME_SCREEN_HEIGHT) {
		buffer[x + y * GAME_SCREEN_WIDTH].Char.UnicodeChar = c;
		buffer[x + y * GAME_SCREEN_WIDTH].Attributes = color;
	}

}

void ScreenManager::SetTextCoordFixed(int x, int y, char c, int color)
{
	buffer[x + y * GAME_SCREEN_WIDTH].Char.UnicodeChar = c;
	buffer[x + y * GAME_SCREEN_WIDTH].Attributes = color;
}


void ScreenManager::SetTextColor(int x, int y, int color)
{

	if (x + y * GAME_SCREEN_WIDTH <= GAME_SCREEN_WIDTH * GAME_SCREEN_HEIGHT) {
		buffer[x + y * GAME_SCREEN_WIDTH].Attributes = color;
	}

}

void ScreenManager::Clear() 
{
	for (int currentX = 0; currentX < GAME_SCREEN_WIDTH; currentX++) {
		for (int currentY = 0; currentY < GAME_SCREEN_HEIGHT; currentY++) {
			buffer[currentX + currentY * GAME_SCREEN_WIDTH].Char.UnicodeChar = 0x2588;
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
							if (GameManager::Instance().GetHighlightGameObject() && GameManager::Instance().GetHighlightGameObject() == gameObject)
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
	inFile.open(GameManager::Instance().GetCurrentNode()->GetMapName());
	//inFile.open(currentMap.currentMapName);
	std::string line;

	int numberLine = 0;	
	while (getline(inFile, line)) {
		if (numberLine > 0){
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
		if (object->GetMapLink() == GameManager::Instance().GetCurrentNode()->GetMapName() || object == GameManager::Instance().GetPlayer())
		{
			DisplayGameObject(object);
			if (showCollider) {
				object->DrawCollider();		
			}
	
		}
	}
}

void ScreenManager::ShowCollider() {
	showCollider = !showCollider;
}

void ScreenManager::WriteInfoPanel(InfoPanel *_infoPanel) {
	int lineJump = 0;

	for (struct Panel *panel : _infoPanel->panels) {
		lineJump = panel->marginY;
		WriteLineAtCoords(INFO_PANEL_ORIG_X + panel->marginX, INFO_PANEL_ORIG_Y + lineJump, *(panel->header));
		lineJump++;

		for (InfoLine *line : panel->text) {
			WriteLineAtCoords(INFO_PANEL_ORIG_X + panel->marginX + panel->padding, INFO_PANEL_ORIG_Y + lineJump, *line);
			lineJump++;
		}
	}

	DisplayTextBar(_infoPanel->healthBar);
	DisplayTextBar(_infoPanel->foodBar);
}

void ScreenManager::SetDescription(std::string desc) {
	infoPanel->SetDescription(desc);
}

void ScreenManager::SetInventory(std::list<Item *> inventory) {
	infoPanel->SetInventory(inventory);
}

void ScreenManager::SetCrafts(std::list<CraftableItem *> items)
{
	infoPanel->RemoveHighlight();
	infoPanel->SetCrafts(items);
}


void ScreenManager::WriteLineAtCoords(int x, int y, InfoLine const &line) {
	for (size_t i = 0; i < line.text.length(); i++) {
		buffer[(x + i) + (y * GAME_SCREEN_WIDTH)].Char.UnicodeChar = line.text[i];
		buffer[(x + i) + (y * GAME_SCREEN_WIDTH)].Attributes = line.color;
	}
}


void ScreenManager::DisplayTextBar(struct TextBar &textBar)
{
	int x = textBar.origX + INFO_PANEL_ORIG_X;
	int y = textBar.origY + INFO_PANEL_ORIG_Y;
	int padding = textBar.label->text.length() > 10 ? textBar.label->text.length() : 10;

	WriteLineAtCoords(x, y, *(textBar.label));


	buffer[(x + padding) + (y * GAME_SCREEN_WIDTH)].Char.UnicodeChar = ' ';
	buffer[(x + padding) + (y * GAME_SCREEN_WIDTH)].Attributes = 0x00;
	buffer[(x + 1 + padding) + (y * GAME_SCREEN_WIDTH)].Char.UnicodeChar = ' ';
	buffer[(x + 1 + padding) + (y * GAME_SCREEN_WIDTH)].Attributes = 0x00;
	buffer[(x + 2 + padding) + (y * GAME_SCREEN_WIDTH)].Char.UnicodeChar = '<';
	buffer[(x + 2 + padding) + (y * GAME_SCREEN_WIDTH)].Attributes = 0x07;

	for (size_t i = padding + 3; i < padding + textBar.value + 3; i++) {
		buffer[(x + i) + (y * GAME_SCREEN_WIDTH)].Char.UnicodeChar = textBar.unit;
		buffer[(x + i) + (y * GAME_SCREEN_WIDTH)].Attributes = textBar.color;
	}

	buffer[(x + padding + textBar.maxValue + 3) + (y * GAME_SCREEN_WIDTH)].Char.UnicodeChar = '>';
	buffer[(x + padding + textBar.maxValue + 3) + (y * GAME_SCREEN_WIDTH)].Attributes = 0x07;
}


void ScreenManager::ShowMenu()
{
	std::ifstream inFile;
	inFile.open("Sprite/Menu.txt");
	std::string line;

	int numberLine = 0;
	while (getline(inFile, line)) {
			for (int x = 0; x < line.length(); x++)
			{
				SetTextCoord(x, numberLine, line[x], FOREGROUND_RED);
			}
		numberLine++;
	}

	if (inFile) {
		inFile.close();
	}
}

void ScreenManager::ShowGameOver()
{
	std::ifstream inFile;
	inFile.open("Sprite/GameOver.txt");
	std::string line;

	int numberLine = 0;
	while (getline(inFile, line)) {
		for (int x = 0; x < line.length(); x++)
		{
			SetTextCoord(x, numberLine, line[x], FOREGROUND_RED);
		}
		numberLine++;
	}

	if (inFile) {
		inFile.close();
	}
}