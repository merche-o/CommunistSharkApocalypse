#pragma once

#include "SFML\Graphics.hpp"
#include "Player.h"

class Display
{
private:
	sf::RenderWindow & win;

public:
	sf::Font font;

public:
	Display(sf::RenderWindow &);
	~Display(void);

	void loadImage(float x, float y, sf::Texture & texture, int transparency = 255);
	void loadPlayer(Player* p);
	void loadText(float, float, sf::Font, std::string, int size, int r, int g, int b);
	void loadSplitText(float x, float y, sf::Font font, std::string str, int size);
	void drawSquare(float x, float y, int width, int height, int outline, int r, int g, int b, int a);
	void RefreshWindow();
};

