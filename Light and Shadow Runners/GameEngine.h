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

enum e_state
{
	MENU,
	GAME
};

class GameEngine
{
private:
	Map map;

	e_state state;
	Parameters parameters;
	GameMenu menu;
	bool restart;

	Graphic graphic;
	SoundEngine sound;
	std::vector<Player*> player;
	std::vector<Star*> stars;
	float popStar;
	Event event;
	
	sf::Clock globalClock;
	sf::Time globalTimer;
	float loopTime;

public:
	sf::RenderWindow window;

public:
	GameEngine(void);
	~GameEngine(void);

	void run();
	void starsGenerator();
};

