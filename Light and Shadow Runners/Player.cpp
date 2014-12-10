#include "Player.h"


Player::Player(float &LoopTime, int num)
	: loopTime(LoopTime)
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
	maxSpeed = 500;
	speedScale = 0;
	jumpStrength = 0;
	initJumpStrength = 500;
	isJumping = false;
	JumpIsReleased = true;
	onTheFloor = false;
	fallSpeed = 100;
	initFallSpeed = 100;
	maxFallSpeed = 900;
	maxJumpTime = 0.2;
	currentJumpTime = 0;
	collideUp = false;
	collideDown = false;
	collideScreen = false;
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
		y = Settings::HEIGHT / 2 - 25;
	}
	nextFrameY = y;
	side = color;
	inDash = 0;
	tmpTime = 0;
}


Player::~Player(void)
{
}

int		Player::getWidth(void)
{
	return (this->width * this->scale);
}


