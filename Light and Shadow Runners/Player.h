#pragma once

#include <vector>
#include "Settings.h"

class Player
{
public:
	float x;
	float y;
	int width;
	int height;
	float scale;
	e_color color;
	bool home;

private:

public:
	Player(int num);
	~Player(void);
};

