#include "Player.h"


Player::Player()
{
	//texture.loadFromFile("../Ressources/Images/Player.png");
	x = 0;
	y = 0;

	
	animFrame = 1;
	dir = LEFT;
	act = WALK;
}


Player::~Player(void)
{
}

