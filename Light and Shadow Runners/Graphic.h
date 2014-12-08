#pragma once

#include <vector>
#include "Display.h"
#include "Player.h"
#include "Map.h"
#include "Star.h"

class Graphic : public Display
{
private:
	sf::RenderWindow & win;
	Map & map;
	std::vector<Player*> & player;
	std::vector<Star*> & stars;
	float & loopTime;
	float time;
	float glowStarTime;

public:
	Graphic(sf::RenderWindow & w, Map & m, std::vector<Star*> & s, std::vector<Player*> & p, float & Time);
	~Graphic(void);

	void RefreshWindow();
	void drawMap();
	void drawStars();
	void drawPlayer();
	void drawLimits();
};

