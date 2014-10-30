#include "GameMenu.h"
#include <iostream>

GameMenu::GameMenu(sf::RenderWindow & w, Event & e, Parameters & p, bool & s)
	: Display(w), win(w), event(e), param(p), start(s)
{
	refresh = true;
	posMenu = 0;
	currentState = MAIN;
	beforeState.push_back(NONE);

	addTextMenu(MAIN, new TextMenu(350, 0, "Menu", 128, 250, 60, 60));
	addKeyTextMenu(MAIN, new TextMenu(400, 200, "Play", 64), &GameMenu::menuPlay);
	addKeyTextMenu(MAIN, new TextMenu(400, 300, "Settings", 64), &GameMenu::menuSettings);
	addKeyTextMenu(MAIN, new TextMenu(400, 400, "Credits", 64), &GameMenu::menuCredits);
	addKeyTextMenu(MAIN, new TextMenu(400, 500, "Quit", 64), &GameMenu::menuReturn);
	
	addTextMenu(SETTINGS, new TextMenu(350, 0, "Settings", 128, 250, 60, 60));
	addKeyTextMenu(SETTINGS, new TextMenu(400, 200, "Back", 64), &GameMenu::menuReturn);

	addTextMenu(CREDITS, new TextMenu(350, 0, "Credits", 128, 250, 60, 60));
	addTextMenu(CREDITS, new TextMenu(300, 200, "Olivier", 64, 60, 250, 150));
	addTextMenu(CREDITS, new TextMenu(300, 300, "Marc", 64, 60, 150, 150));
	addTextMenu(CREDITS, new TextMenu(300, 400, "Axel", 64, 60, 250, 250));
	addKeyTextMenu(CREDITS, new TextMenu(400, 600, "Back", 64), &GameMenu::menuReturn);
}


GameMenu::~GameMenu(void)
{
}

void GameMenu::run()
{
	if (refresh == true)
	{
		if (isPushed == true)
		{
			if (posMenu != sizeKeyTextMenu[currentState] - 1) // If action != Return
				beforeState.push_back(currentState);
			(this->*(actionMenu[std::make_pair(currentState, posMenu)]))();
			if (!win.isOpen())
				return;
			posMenu = 0;
			isPushed = false;
		}
		if (posMenu < 0)
			posMenu = sizeKeyTextMenu[currentState] - 1;
		else if (posMenu > sizeKeyTextMenu[currentState] - 1)
			posMenu = 0;
		
		win.clear();
		displayCurrentMenu();
		win.display();

		refresh = false;
	}

	event.menuEvent(posMenu, isPushed, refresh);
}

void GameMenu::displayCurrentMenu()
{
	for (int i = 0; i < sizeTextMenu[currentState]; ++i)
	{
		loadText(textMenu[std::make_pair(currentState, i)]->x, 
				textMenu[std::make_pair(currentState, i)]->y, 
				font, 
				textMenu[std::make_pair(currentState, i)]->text, 
				textMenu[std::make_pair(currentState, i)]->size,
				textMenu[std::make_pair(currentState, i)]->color.r, 
				textMenu[std::make_pair(currentState, i)]->color.g, 
				textMenu[std::make_pair(currentState, i)]->color.b);
	}

	for (int i = 0; i < sizeKeyTextMenu[currentState]; ++i)
	{
		if (posMenu == i)
		{
			loadText(keyTextMenu[std::make_pair(currentState, i)]->x, 
					keyTextMenu[std::make_pair(currentState, i)]->y, 
					font, 
					keyTextMenu[std::make_pair(currentState, i)]->text, 
					keyTextMenu[std::make_pair(currentState, i)]->size, 
					250, 250, 60);
		}
		else
		{
			loadText(keyTextMenu[std::make_pair(currentState, i)]->x, 
					keyTextMenu[std::make_pair(currentState, i)]->y, 
					font, 
					keyTextMenu[std::make_pair(currentState, i)]->text, 
					keyTextMenu[std::make_pair(currentState, i)]->size, 
					250, 150, 60);
		}
	}
}

void GameMenu::menuCredits()
{
	currentState = CREDITS;
}

void GameMenu::menuSettings()
{
	currentState = SETTINGS;
}

void GameMenu::menuReturn()
{
	if (beforeState[beforeState.size() - 1] == NONE)
		win.close();
	else
	{
		currentState = beforeState[beforeState.size() - 1];
		beforeState.erase(beforeState.begin() + beforeState.size() - 1);
	}
}

void GameMenu::menuPlay()
{
	start = true;
}

void GameMenu::addTextMenu(e_state state, TextMenu * text)
{
	textMenu[std::make_pair(state, sizeTextMenu[state])] = text;
	sizeTextMenu[state]++;
}

void GameMenu::addKeyTextMenu(e_state state, TextMenu * text, void(GameMenu:: *p)())
{
	keyTextMenu[std::make_pair(state, sizeKeyTextMenu[state])] = text;
	actionMenu[std::make_pair(state, sizeKeyTextMenu[state])] = p;
	sizeKeyTextMenu[state]++;
}
