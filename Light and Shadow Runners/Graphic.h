#pragma once

#include <vector>
#include "Display.h"
#include "Player.h"

class Graphic : public Display
{
private:
	sf::RenderWindow & win;
	std::vector<Player*> & player;
	float & loopTime;
	float time;

public:
	Graphic(sf::RenderWindow & w, std::vector<Player*> & p, float & Time);
	~Graphic(void);

	void RefreshWindow();
};

