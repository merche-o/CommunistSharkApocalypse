#pragma once

#include <vector>
#include "Settings.h"
#include <SFML\Graphics.hpp>
#include "Vector2d.h"

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

class Player
{
public:
	float x;
	float y;
	int width;
	int height;
	float maxSpeed;
	float speedScale;
	float scale;
	e_color color;
	bool home;
	float &loopTime;
	float speed;
		float tmpTime;
	int inDash;
	std::vector<bool> inputMap;
	e_color side;
	int mapHeight;
	float jumpStrength;
	float initJumpStrength;
	float maxFallSpeed;
	float fallSpeed;
	float initFallSpeed;
	float maxJumpTime;
	float currentJumpTime;
	bool isJumping;
	bool JumpIsReleased;
	bool onTheFloor;
	float nextFrameY;
	bool collideUp;
	bool collideDown;
	int num;
	bool collideScreen;

private:

public:
	Player(float &loopTime, int num);
	~Player(void);
	int getWidth(void);
	void reset();
};

