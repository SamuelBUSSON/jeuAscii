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
	readHandle = GetStdHandle(STD_INPUT_HANDLE);
}

ScreenManager::~ScreenManager() {

}

void ScreenManager::Init() {

	DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;

	SetConsoleMode(readHandle, fdwMode);

	SetConsoleWindowInfo(writeHandle, TRUE, &bufferArea);

	SetConsoleScreenBufferSize(writeHandle, bufferSize);

	for (int currentX = 0; currentX < SCREEN_WIDTH; currentX++) {
		for (int currentY = 0; currentY < SCREEN_HEIGHT; currentY++) {
			buffer[currentX + currentY * SCREEN_WIDTH].Char.UnicodeChar = 0x2588;
			//buffer[currentX + currentY * SCREEN_WIDTH].Attributes = FOREGROUND_GREEN;
		}
	}	

	
}


void ScreenManager::SampleDisplay() 
{
	WriteConsoleOutput(writeHandle, buffer, bufferSize, initialBufferCoord, &bufferArea);
}

bool ScreenManager::GetExitGame() {
	return EXITGAME;
}

void ScreenManager::Update() {
		ReadConsoleInput(readHandle, &InputRecord, 1, &Events);


		switch (InputRecord.EventType) {
		case KEY_EVENT: // keyboard input 


			switch (InputRecord.Event.KeyEvent.wVirtualKeyCode)
			{
			case VK_ESCAPE:
				EXITGAME = TRUE;
				break;

			case VK_SPACE:		

					

				break;


			case VK_RETURN:

				break;

			case VK_LEFT:
				// left key   move player left
				//std::cout << "VK_LEFT   = " << InputRecord.Event.KeyEvent.wVirtualKeyCode << " \n";

				break;

			case VK_RIGHT:
				// right key   move player right
				//std::cout << "VK_RIGHT   = " << InputRecord.Event.KeyEvent.wVirtualKeyCode << " \n";

				break;

			case VK_UP:
				// up key   move player up
				//std::cout << "VK_UP   = " << InputRecord.Event.KeyEvent.wVirtualKeyCode << " \n";


				break;

			case VK_DOWN:
				// up key   move player down
				//std::cout << "VK_DOWN   = " << InputRecord.Event.KeyEvent.wVirtualKeyCode << " \n";


				break;



			}//switch

			//---------------------------------------------------------------------------------
			break;

		case MOUSE_EVENT: // mouse input 

			if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				coord.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
				coord.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;	

				//DisplaySpriteFromString("Sprite/Tree.txt", coord.X, coord.Y, coord.X | coord.Y);
				SetTextCoord(coord.X - 1, coord.Y, coord.X -1, coord.X - 1);
				SetTextCoord(coord.X , coord.Y, coord.X, coord.X);
				SetTextCoord(coord.X + 1, coord.Y, coord.X + 1, coord.X + 1);
				SetTextCoord(coord.X + 2, coord.Y, coord.X + 2, coord.X + 2);

				/*SetTextCoord(coord.X-1, coord.Y, '\\', FOREGROUND_RED);
				SetTextCoord(coord.X, coord.Y, 'o', FOREGROUND_RED);
				SetTextCoord(coord.X+1, coord.Y, '/', FOREGROUND_RED);*/



				//SetConsoleCursorPosition(hout, coord);
				//SetConsoleTextAttribute(hout, rand() % 7 + 9);

				/*if ((InputRecord.Event.MouseEvent.dwMousePosition.X == buttonX) &&
					(InputRecord.Event.MouseEvent.dwMousePosition.Y == buttonY)) {

					clearscreen();
					gotoxy(1, 1);
					setcolor(7);
					drawpixel(buttonX, buttonY, 1);
					setcolor(3);
					cout << " mybutton was pressed \n";
					setcolor(7);
					Sleep(500);
					drawpixel(buttonX, buttonY, 1);
					gotoxy(buttonX + 2, buttonY);
					setcolor(3);
					cout << "<----- a button      \n";


				}*/

				//std::cout << "Hello world at " << InputRecord.Event.MouseEvent.dwMousePosition.X << " x " << InputRecord.Event.MouseEvent.dwMousePosition.Y << " ";

			}// mouse 

			break;

		case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
			;
			break;

		case FOCUS_EVENT:  // disregard focus events 

		case MENU_EVENT:   // disregard menu events 

			break;

		default:
			std::cout << "Unknown event type \n";
			break;
		}



		//FlushConsoleInputBuffer(hin);
	
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
			SetTextCoord(coordX + x, coordY + y, line[x], color);
		}
		y++;
	}
}



