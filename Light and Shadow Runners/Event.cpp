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
	while (win.pollEvent(event))
    {
		if (event.type == sf::Event::Closed)
            win.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				win.close();
			else if (event.key.code == sf::Keyboard::Up)
				this->player[0]->inputMap[UP] = true;
			else if (event.key.code == sf::Keyboard::Down)
				this->player[0]->inputMap[DOWN] = true;
			else if (event.key.code == sf::Keyboard::Left)
				this->player[0]->inputMap[LEFT] = true;
			else if (event.key.code == sf::Keyboard::Right)
				this->player[0]->inputMap[RIGHT] = true;
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Up)
				this->player[0]->inputMap[UP] = false;
			else if (event.key.code == sf::Keyboard::Down)
				this->player[0]->inputMap[DOWN] = false;
			else if (event.key.code == sf::Keyboard::Left)
				this->player[0]->inputMap[LEFT] = false;
			else if (event.key.code == sf::Keyboard::Right)
				this->player[0]->inputMap[RIGHT] = false;
		}
    }
}
 
//have to finish player inputKey

void Event::setPlayer1Key()
	{
		if (event.key.code == sf::Keyboard::Escape)
				win.close();
			else if (event.key.code == sf::Keyboard::Up)
				this->player[0]->inputMap[UP] = true;
			else if (event.key.code == sf::Keyboard::Down)
				this->player[0]->inputMap[DOWN] = true;
			else if (event.key.code == sf::Keyboard::Left)
				this->player[0]->inputMap[LEFT] = true;
			else if (event.key.code == sf::Keyboard::Right)
				this->player[0]->inputMap[RIGHT] = true;
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