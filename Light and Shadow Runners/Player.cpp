#include "Player.h"


Player::Player(float &LoopTime, int num)
	: loopTime(LoopTime), speedVect(0, 0), accelVect(0, 0), accelCount(0)
{

	int i = 0;
	while (i < 4)
		{
			inputMap.push_back(false);
			++i;
		}
	
	width = 50;
	height = 50;
	scale = 1.0;
	home = true;
	speed = 5;
	if (num == 1)
	{
		color = BLACK;
		x = 10;
		y = Settings::HEIGHT / 2;
	}
	else if (num == 2)
	{
		color = WHITE;
		x = Settings::WIDTH - width - 10;
		y = Settings::HEIGHT / 2;
	}
	side = color;
}


Player::~Player(void)
{
}

