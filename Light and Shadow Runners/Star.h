#pragma once

#include <SFML\Graphics.hpp>
#include "Settings.h"

class Star
{
public:
	int	size;
	int x;
	int y;
	int speed;
	int anim;
	int addAnim;
	e_color color;
	sf::Texture texture;

public:
	Star(int X, int Y, e_color Color);
	Star(int X, int Y, e_color Color, int Speed);
	~Star(void);

	void nextFrame();
};

