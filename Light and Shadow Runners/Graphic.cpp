#include "Graphic.h"
#include "Settings.h"
#include "Utils.h"
#include <iostream>

Graphic::Graphic(sf::RenderWindow & w, std::map<std::pair<e_color, int>, Rect*> & m, std::vector<Player*> & p, float & Time)
	: Display(w), win(w), map(m), player(p), loopTime(Time)
{
}


Graphic::~Graphic(void)
{
}

void Graphic::RefreshWindow()
{
	win.display();
}

void Graphic::drawMap()
{
	for (int i = 0; i < map.size() / 2; ++i)
	{
		drawSquare(map[std::make_pair(BLACK, i)]->x, map[std::make_pair(BLACK, i)]->y, map[std::make_pair(BLACK, i)]->width, map[std::make_pair(BLACK, i)]->height, 0, 0, 0, 0, 255);
		drawSquare(map[std::make_pair(WHITE, i)]->x, map[std::make_pair(WHITE, i)]->y, map[std::make_pair(WHITE, i)]->width, map[std::make_pair(WHITE, i)]->height, 0, 255, 255, 255, 255);
	}
}

void Graphic::drawPlayer()
{
	
	if (player[0] != NULL)
		loadPlayer(player[0]);
	if(player[1] != NULL)
		loadPlayer(player[1]);
}