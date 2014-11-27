#pragma once

#include <vector>
#include "Settings.h"
#include <SFML\Graphics.hpp>
#include "Vector2d.h"

enum e_dir
{
	D_LEFT,
	D_RIGHT
};

enum e_act
{
	WALK,
	JUMP
};

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
	float &loopTime;
	float speed;
	std::vector<bool> inputMap;
	e_color side;
	Vector2d speedVect;
	Vector2d accelVect;
	int accelCount;
private:

public:
	Player(float &loopTime, int num);
	~Player(void);
};

