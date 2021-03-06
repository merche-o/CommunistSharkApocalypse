#include "Graphic.h"
#include "Settings.h"
#include "Utils.h"
#include <iostream>

Graphic::Graphic(sf::RenderWindow & w, Map & m, std::vector<Star*> & s, std::vector<Player*> & p, float & Time)
	: Display(w), win(w), map(m), stars(s), player(p), loopTime(Time)
{
	glowStarTime = 0;
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
	for (int i = map.plus; i < map.map.size() / 2; ++i)
	{
		drawSquare(map.map[std::make_pair(BLACK, i)]->x, map.map[std::make_pair(BLACK, i)]->y, map.map[std::make_pair(BLACK, i)]->width, map.map[std::make_pair(BLACK, i)]->height, 0, 0, 0, 0, 255);
		drawSquare(map.map[std::make_pair(WHITE, i)]->x, map.map[std::make_pair(WHITE, i)]->y, map.map[std::make_pair(WHITE, i)]->width, map.map[std::make_pair(WHITE, i)]->height, 0, 255, 255, 255, 255);
	}
	//middleLine(Settings::WIDTH / 2 + map.center);
	//middleLine(Settings::WIDTH / 2 - 150 + map.center);
	//middleLine(Settings::WIDTH / 2 + 150 + map.center);
}

void Graphic::drawStars()
{
	bool nextFrame = false;

	glowStarTime += loopTime;
	if (glowStarTime >= 0.1)
	{
		glowStarTime = 0;
		nextFrame = true;
	}

	for (int i = 0; i < stars.size(); ++i)
	{
		stars[i]->y += stars[i]->speed * loopTime;
		if (nextFrame == true)
			stars[i]->nextFrame();
		loadStar(stars[i]);
	}
}

void Graphic::drawPlayer()
{
	loadPlayer(player[0]);
	loadPlayer(player[1]);
}

void Graphic::drawLimits()
{
	int w = map.map[std::make_pair(BLACK, map.plus)]->width;
	
	sf::Texture texture1;
	sf::Texture texture2;

	texture1.loadFromFile("../Ressources/Images/lightlimit.png");
	texture2.loadFromFile("../Ressources/Images/darklimit.png");

	loadImage(w - Settings::WIDTH, Settings::HEIGHT - texture1.getSize().y, texture1);
	loadImage(w, Settings::HEIGHT - texture2.getSize().y, texture2);
}