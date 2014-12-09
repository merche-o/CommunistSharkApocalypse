#include "Display.h"
#include "Settings.h"
#include <iostream>

Display::Display(sf::RenderWindow & w)
	: win(w)
{
	font.loadFromFile("../Ressources/Text/Text.ttf");
}


Display::~Display(void)
{
}

void Display::loadImage(float x, float y, sf::Texture & Texture, int transparency)
{
	sf::Sprite		Sprite;

	Sprite.setTexture(Texture);
	Sprite.setPosition(x, y);
	Sprite.setColor(sf::Color(255, 255, 255, transparency));
	win.draw(Sprite);
}

void Display::loadStar(Star* star)
{
	sf::Sprite		Sprite;

	Sprite.setTexture(star->texture);
	Sprite.setTextureRect(sf::IntRect(star->anim * 16, 0, 16, 16));
	Sprite.setPosition(star->x, star->y);
	win.draw(Sprite);
}

void Display::loadPlayer(Player* p)
{
	sf::RectangleShape rect;

	if (p->color == BLACK)
	{
		rect.setSize(sf::Vector2f(p->width * p->scale, p->height * p->scale));
		rect.setFillColor(sf::Color(0, 0, 0));
		if (p->scale == 1.0)
			rect.setOutlineThickness(-3);
		else
			rect.setOutlineThickness(-1);
		rect.setOutlineColor(sf::Color(255, 255, 255));
		rect.setPosition(p->x, p->y);
	}
	else if (p->color == WHITE)
	{
		rect.setSize(sf::Vector2f(p->width * p->scale, p->height * p->scale));
		rect.setFillColor(sf::Color(255, 255, 255));
		if (p->scale == 1.0)
			rect.setOutlineThickness(-3);
		else
			rect.setOutlineThickness(-1);
		rect.setOutlineColor(sf::Color(0, 0, 0));
		rect.setPosition(p->x, p->y);
	}

	win.draw(rect);
}

void Display::loadText(float x, float y, sf::Font font, std::string str, int size, int r, int g, int b)
{
	sf::Text text;

	text.setFont(font);
	text.setCharacterSize(size);
	text.setColor(sf::Color(r, g, b));
	text.setPosition(x, y);
	text.setString(str);
	win.draw(text);
}

void Display::loadSplitText(float x, float y, sf::Font font, std::string str, int size)
{
	sf::Text text1;
	sf::Text text2;

	text1.setFont(font);
	text1.setCharacterSize(size);
	text1.setColor(sf::Color(255, 0, 0));
	text1.setPosition(x, y);
	text1.setString(str);

	sf::View clipView(sf::FloatRect(100.f, 100.f, 50.f, 200.f));
	// ratio entre 0 et 1
	clipView.setViewport(sf::FloatRect(100.f / win.getSize().x,
                                   100.f / win.getSize().y,
                                   50.f  / win.getSize().x,
                                   200.f / win.getSize().y));
	win.setView(clipView);
	win.draw(text1);
	
	
	win.draw(text2);

	
	win.setView(win.getDefaultView());
}

void Display::drawSquare(float x, float y, int width, int height, int outline, int r, int g, int b, int a)
{
	sf::RectangleShape rect;

	rect.setSize(sf::Vector2f(width, height));
	rect.setFillColor(sf::Color(r, g, b, a));
	rect.setOutlineThickness(outline);
	rect.setPosition(x, y);
	win.draw(rect);
}

void Display::middleLine(int line)
{
	sf::RectangleShape rect;

	rect.setSize(sf::Vector2f(4, Settings::HEIGHT));
	rect.setFillColor(sf::Color(255, 0, 0, 100));
	rect.setPosition(line - 2, 0);
	win.draw(rect);
}

void Display::RefreshWindow()
{
  win.display();
}

// scinder du text en deux


/*** METHODE 1 ***/
/*

// je dessine des trucs non clippés...

window.draw(truc_pas_clippe);

// je clip avec le rectangle [100, 100, 50, 200]
sf::View clipView(sf::FloatRect(100.f, 100.f, 50.f, 200.f));
clipView.setViewport(sf::FloatRect(100.f / window.getSize().x,
                                   100.f / window.getSize().y,
                                   50.f  / window.getSize().x,
                                   200.f / window.getSize().y));
window.setView(clipView);

// je dessine des trucs clippés...
window.draw(truc_clippe);

// je restaure la vue par défaut
window.setView(window.getDefaultView());

// je dessine des trucs non clippés...
window.draw(autre_truc_pas_clippe);
*/