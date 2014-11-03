#pragma once

#include <vector>
#include "Display.h"
#include "Player.h"
#include "Map.h"

class Graphic : public Display
{
private:
	sf::RenderWindow & win;
	std::map<std::pair<e_color, int>, Rect*> & map;
	std::vector<Player*> & player;
	float & loopTime;
	float time;

public:
	Graphic(sf::RenderWindow & w, std::map<std::pair<e_color, int>, Rect*> & m, std::vector<Player*> & p, float & Time);
	~Graphic(void);

	void RefreshWindow();
	void drawMap();
	void drawPlayer();
};

