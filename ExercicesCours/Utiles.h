#pragma once

#include <fstream>
#include <string>
#include <vector>

#define MAP_WIDTH 70
#define MAP_HEIGHT 37

#define DOOR_LENGTH 11

#define MIN_OBJECT_PER_MAP 2
#define MAX_OBJECT_PER_MAP 4

const std::vector<std::string> explode(const std::string& s, const char& c);

void SetCharAtCoord(int x, int y, std::string &s, char c);