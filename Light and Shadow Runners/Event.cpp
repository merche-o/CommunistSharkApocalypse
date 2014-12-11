#include "Event.h"


Event::Event(sf::Window & w, std::vector<Player*> & p)
	: win(w), player(p)
{
}


Event::~Event(void)
{
}

void Event::checkEvent()
{
	bool push = true;
	while (win.pollEvent(event))
    {
		if (event.type == sf::Event::Closed)
            win.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			setPlayer1Key(push);
		
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			push = false;
			setPlayer1Key(push);
		}
    }
}

void Event::setPlayer1Key(bool value)
	{
		if (event.key.code == sf::Keyboard::Escape)
				win.close();
			else if (event.key.code == sf::Keyboard::Up)
				this->player[0]->inputMap[UP] = value;
			else if (event.key.code == sf::Keyboard::Down)
				this->player[0]->inputMap[DOWN] = value;
			else if (event.key.code == sf::Keyboard::Left)
				this->player[0]->inputMap[LEFT] = value;
			else if (event.key.code == sf::Keyboard::Right)
				this->player[0]->inputMap[RIGHT] = value;
			else if (event.key.code == sf::Keyboard::W)
				this->player[1]->inputMap[UP] = value;
			else if (event.key.code == sf::Keyboard::S)
				this->player[1]->inputMap[DOWN] = value;
			else if (event.key.code == sf::Keyboard::A)
				this->player[1]->inputMap[LEFT] = value;
			else if (event.key.code == sf::Keyboard::D)
				this->player[1]->inputMap[RIGHT] = value;
}

void Event::menuEvent(int & pos, bool & push, bool & refresh)
{
	while (win.pollEvent(event))
    {
		if (event.type == sf::Event::Closed)
            win.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				win.close();
			else if (event.key.code == sf::Keyboard::Return)
			{
				push = true;
				refresh = true;
			}
			else if (event.key.code == sf::Keyboard::Up)
			{
				--pos;
				refresh = true;
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				++pos;
				refresh = true;
			}
		}
	}
}