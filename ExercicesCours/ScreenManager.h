#pragma once

#ifndef DEF_SCREENMANAGER
#define DEF_SCREENMANAGER

#include <iomanip>
#include <fstream>

#include <windows.h>
#include <iostream>
#include <string>
#include <list>

#include "GameObject.h"
#include "InfoPanel.h"

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 40

#define CAM_WIDTH 70
#define CAM_HEIGHT 40

#define INFO_PANEL_ORIG_X 75
#define INFO_PANEL_ORIG_Y 1

#define YDOORTOP 15
#define YDOORBOT  23

#define XDOORLEFT 30
#define XDOORRIGHT 41

struct TileMap {
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

	int playerPosX = CAM_WIDTH /2;
	int playerPosY = CAM_HEIGHT/2;

	int cameraPosX = playerPosX - CAM_WIDTH / 2;
	int cameraPosY = playerPosY - CAM_HEIGHT / 2;

	TileMap currentMap;

	InfoPanel *infoPanel;


public:
	ScreenManager();
	~ScreenManager();

	void Init();

	void ClearScreen();
	void SampleDisplay(std::list<GameObject *> gameObjects);

	bool GetExitGame();

	void SetTextCoord(int x, int y, char c);
	char GetTextCoord(int x, int y);
	void SetTextCoord(int x, int y, char c, int color);
	void SetTextCoordFixed(int x, int y, char c, int color);

	void Clear();

	void ReadMap();
	void DrawBorder();

	void GoLeft();
	void GoRight();
	void GoUp();
	void GoDown();

	void CheckPlayerPosition();

	void DisplayPlayer();
	void DisplayGameObjects(std::list<GameObject *> gameObjects);
	void DisplayGameObject(GameObject *gameObject);

	void WriteInfoPanel(InfoPanel *_infoPanel);
	void SetInfo(std::string infos);
};

#endif