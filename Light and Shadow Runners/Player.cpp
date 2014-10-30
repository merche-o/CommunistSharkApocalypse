#include "Player.h"


Player::Player(float &LoopTime, p_color Color, p_side Side)
	: loopTime(LoopTime), color(Color), side(Side)
{
	//texture.loadFromFile("../Ressources/Images/Player.png");
	x = 0;
	y = 0;

	int i = 0;
	while (i < 4)
		{
			inputMap.push_back(false);
			++i;
		}
	
	animFrame = 1;
	dir = D_LEFT;
	act = WALK;
	speed = 4;
}


Player::~Player(void)
{
}

