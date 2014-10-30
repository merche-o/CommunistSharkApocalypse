#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

enum e_dir
{
	LEFT,
	RIGHT
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
	int width;
	int height;
	e_act act;
	e_dir dir;
	int animFrame;
	sf::Texture texture;

private:

public:
	Player();
	~Player(void);
};

