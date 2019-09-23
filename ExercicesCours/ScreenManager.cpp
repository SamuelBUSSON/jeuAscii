#include <windows.h>
#include "ScreenManager.h"

ScreenManager::ScreenManager() {

}

ScreenManager::~ScreenManager() {

}


void ScreenManager::SampleDisplay() {

	const int SCREEN_WIDTH = 80;
	const int SCREEN_HEIGHT = 40;

	HANDLE writeHandle;
	HANDLE readHandle;

	writeHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	readHandle = GetStdHandle(STD_INPUT_HANDLE);

	CHAR_INFO buffer[SCREEN_WIDTH * SCREEN_HEIGHT];

	COORD bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD initialBufferCoord = { 0, 0 };
	SMALL_RECT bufferArea = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	SetConsoleWindowInfo(writeHandle, TRUE, &bufferArea);

	SetConsoleScreenBufferSize(writeHandle, bufferSize);

	for (int currentX = 0; currentX < SCREEN_WIDTH; currentX++) {
		for (int currentY = 0; currentY < SCREEN_HEIGHT; currentY++) {
			buffer[currentX + currentY * SCREEN_WIDTH].Char.UnicodeChar = 0x2588;
			buffer[currentX + currentY * SCREEN_WIDTH].Attributes = FOREGROUND_GREEN;
		}
	}

	WriteConsoleOutput(writeHandle, buffer, bufferSize, initialBufferCoord, &bufferArea);
}