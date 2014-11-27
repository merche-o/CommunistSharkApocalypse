#pragma once

#include <vector>
#include "SFML\Graphics.hpp"
#include "Player.h"

enum e_input {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Event
{
private:
	sf::Window & win;
	sf::Event event;
	std::vector<Player*> & player;
	void setPlayer1Key(bool);
	void setPlayer2Key(bool);
public:
	Event(sf::Window & w, std::vector<Player*> & p);
	~Event(void);

	void checkEvent();
	void menuEvent(int & pos, bool & push, bool & refresh);
};

