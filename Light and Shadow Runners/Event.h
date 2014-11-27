#pragma once

#include <vector>
#include "SFML\Graphics.hpp"
#include "Player.h"

class Event
{
private:
	sf::Window & win;
	sf::Event event;
	std::vector<Player*> & player;

public:
	Event(sf::Window & w, std::vector<Player*> & p);
	~Event(void);

	void checkEvent();
	void menuEvent(int & pos, bool & push, bool & refresh);
};

