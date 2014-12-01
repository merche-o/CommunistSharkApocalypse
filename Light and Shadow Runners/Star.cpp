#include "Star.h"


Star::Star(int X, int Y, e_color Color)
	: x(X), y(Y), color(Color)
{
	srand(time(NULL));
	speed = rand() % 100 + 50; // mettre random 50 - 150
	anim = 0;
	addAnim = 1;
	if (color == BLACK)
		texture.loadFromFile("../Ressources/Images/darkstar.png");
	else if (color == WHITE)
		texture.loadFromFile("../Ressources/Images/lightstar.png");
}


Star::~Star(void)
{
}

void Star::nextFrame()
{
	anim += addAnim;
	if (anim == 0 || anim == 4)
		addAnim *= -1;
}