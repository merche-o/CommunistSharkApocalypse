#pragma once

#include <string>

enum e_color
{
	BLACK,
	WHITE
};

class Settings
{
public:
	static const int WIDTH;
	static const int HEIGHT;
	static const float SPEED_MAP;
	static const std::string GAME_NAME;
};