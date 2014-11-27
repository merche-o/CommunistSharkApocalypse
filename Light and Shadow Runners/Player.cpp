#include "Player.h"


Player::Player(int num)
{
	width = 50;
	height = 50;
	scale = 1.0;
	home = true;

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
}


Player::~Player(void)
{
}

