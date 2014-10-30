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
			else if (event.key.code == sf::Keyboard::Up);
			else if (event.key.code == sf::Keyboard::Down);
			else if (event.key.code == sf::Keyboard::Left);
			else if (event.key.code == sf::Keyboard::Right);
		}
		else if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Up);
			else if (event.key.code == sf::Keyboard::Down);
			else if (event.key.code == sf::Keyboard::Left);
			else if (event.key.code == sf::Keyboard::Right);
		}
    }
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