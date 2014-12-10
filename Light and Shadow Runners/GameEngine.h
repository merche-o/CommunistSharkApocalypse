#pragma once

#include <vector>
#include "SFML\Graphics.hpp"
#include "Settings.h"
#include "Parameters.h"
#include "Graphic.h"
#include "GameMenu.h"
#include "Player.h"
#include "Event.h"
#include "SoundEngine.h"
#include "Map.h"
#include "Star.h"
#include "Referee.h"
#include "PhysicsEngine.h"

enum e_state
{
	MENU,
	GAME,
	WINSCREEN
};

class GameEngine
{
private:
	Map map;

	e_state state;
	Parameters parameters;
	GameMenu menu;
	bool restart;
	Referee ref;
	Graphic graphic;
	SoundEngine sound;
	PhysicsEngine physicEngine;
	std::vector<Player*> player;
	std::vector<Star*> stars;
	float popStar;
	Event event;
	
	sf::Clock globalClock;
	sf::Time globalTimer;
	float loopTime;
	int winner;

public:
	sf::RenderWindow window;

public:
	GameEngine(void);
	~GameEngine(void);

	void run();
	void resetGame();
	void starsGenerator();
};

