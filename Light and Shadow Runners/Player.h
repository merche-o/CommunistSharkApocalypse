#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "Settings.h"
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
	float &loopTime;
	int width;
	int height;
	float speed;
	float scale;
	std::vector<bool> inputMap;
	bool home;
	e_color color;
	e_color side;
	Vector2d speedVect;
	Vector2d accelVect;
	int accelCount;
private:
	
public:
	Player(float &loopTime, int num);
	~Player(void);
};

