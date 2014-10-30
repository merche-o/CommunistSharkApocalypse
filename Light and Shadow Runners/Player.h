#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

enum e_dir
{
	D_LEFT,
	D_RIGHT
};

enum e_act
{
	WALK,
	JUMP
};

enum p_side {
	S_BLACK,
	S_WHITE
};

enum p_color {
	P_BLACK,
	p_WHITE
};

class Player
{
public:
	float x;
	float y;
	float &loopTime;
	int width;
	int height;
	e_act act;
	e_dir dir;
	int animFrame;
	int speed;
	sf::Texture texture;
	std::vector<bool> inputMap;
	p_side side;
	p_color color;
private:
	
public:
	Player(float &loopTime, p_color Color, p_side Side);
	~Player(void);
};

