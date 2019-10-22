#pragma once

#ifndef DEF_SCREENMANAGER
#define DEF_SCREENMANAGER

#include <windows.h>
#include <string>
#include <list>

#include "GameObject.h"
#include "BreakableObject.h"
#include "InfoPanel.h"

#define GAME_SCREEN_WIDTH 120
#define GAME_SCREEN_HEIGHT 40

#define CAM_WIDTH 70
#define CAM_HEIGHT 40

#define INFO_PANEL_ORIG_X 75
#define INFO_PANEL_ORIG_Y 1

enum Display_value
{
	Menu,
	Game,
	PlayerDead
};


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

	bool showCollider = false;

	HANDLE writeHandle;
	HANDLE readHandle;


	CHAR_INFO buffer[GAME_SCREEN_WIDTH * GAME_SCREEN_HEIGHT];

	COORD bufferSize = { GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT };
	COORD initialBufferCoord = { 0, 0 };
	SMALL_RECT bufferArea = { 0, 0, GAME_SCREEN_WIDTH - 1, GAME_SCREEN_HEIGHT - 1 };

	int playerPosX = CAM_WIDTH /2;
	int playerPosY = CAM_HEIGHT/2;

	int cameraPosX = playerPosX - CAM_WIDTH / 2;
	int cameraPosY = playerPosY - CAM_HEIGHT / 2;

	TileMap currentMap;

	InfoPanel *infoPanel;

	BreakableObject *shakeObject;

	ScreenManager();

	Display_value display_state;

public:

	static ScreenManager& Instance()
	{
		static ScreenManager INSTANCE;
		return INSTANCE;
	}
	
	~ScreenManager();

	void Init();

	void ClearScreen();
	void SampleDisplay(std::list<GameObject *> gameObjects);

	bool GetExitGame();

	void SetTextCoord(int x, int y, char c);
	char GetTextCoord(int x, int y);
	void SetTextCoord(int x, int y, char c, int color);
	void SetTextCoordFixed(int x, int y, char c, int color);

	void SetTextColor(int x, int y, int color);

	void Clear();

	void ReadMap();
	void DrawBorder();

	bool RightMap();
	bool LeftMap();
	bool TopMap();
	bool BottomMap();

	inline std::string GetCurrentMap() const { return currentMap.currentMapName; }
	inline void SetShakeObject(BreakableObject* g) { shakeObject = g; }
	inline BreakableObject* GetShakeObject() {return shakeObject; }


	inline void SetDisplayState(Display_value new_display) { display_state = new_display; }


	void DisplayGameObjects(std::list<GameObject *> gameObjects);
	void ShowCollider();
	void DisplayGameObject(GameObject *gameObject);

	void HighlightLineAtCoords(COORD coords);
	void ClickOnCoords(int x, int y);

	void ShowMenu();

	void ShowGameOver();

	void SetDescription(std::string infos);
	void SetInventory(std::list<Item *> inventory);
	void SetCrafts(std::list<CraftableItem *> items);

	void WriteInfoPanel(InfoPanel *_infoPanel);
	void WriteLineAtCoords(int x, int y, InfoLine const &line);

	inline void SetHealthBarValue(int health) { infoPanel->healthBar.value = health; }
	inline void SetFoodBarValue(int food) { infoPanel->foodBar.value = food; }
	void DisplayTextBar(struct TextBar &textBar);

};

#endif