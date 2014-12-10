#include "GameMenu.h"
#include "Settings.h"
#include <iostream>

GameMenu::GameMenu(sf::RenderWindow & w, Event & e, Parameters & p, bool & s, int &win)
	: Display(w), win(w), event(e), param(p), start(s), winner(win)
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
	
	addTextMenu(SETTING, new TextMenu(350, 0, "Settings", 128, 250, 60, 60));
	addKeyTextMenu(SETTING, new TextMenu(400, 200, "Back", 64), &GameMenu::menuReturn);

	addTextMenu(CREDITS, new TextMenu(350, 0, "Credits", 128, 250, 60, 60));
	addTextMenu(CREDITS, new TextMenu(300, 200, "Olivier", 64, 60, 250, 150));
	addTextMenu(CREDITS, new TextMenu(300, 300, "Marc", 64, 60, 150, 150));
	addTextMenu(CREDITS, new TextMenu(300, 400, "Axel", 64, 60, 250, 250));
	addKeyTextMenu(CREDITS, new TextMenu(400, 600, "Back", 64), &GameMenu::menuReturn);

	addTextMenu(WIN, new TextMenu(350, 0, "GameOver", 128, 250, 60, 60));
	addTextMenu(WIN, new TextMenu(300, 200, "Player 1 win !" , 64, 60, 250, 150));
	addKeyTextMenu(WIN, new TextMenu(400, 600, "Back", 64), &GameMenu::menuReturn);

	addTextMenu(WIN2, new TextMenu(350, 0, "GameOver", 128, 250, 60, 60));
	addTextMenu(WIN2, new TextMenu(300, 200, "Player 2 win !" , 64, 60, 250, 150));
	addKeyTextMenu(WIN2, new TextMenu(400, 600, "Back", 64), &GameMenu::menuReturn);
	
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
		drawSquare(Settings::WIDTH / 2, 0, Settings::WIDTH / 2, Settings::HEIGHT, 0, 255, 255, 255, 255);
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
	
		loadSplitText(textMenu[std::make_pair(currentState, i)]->x, 
				textMenu[std::make_pair(currentState, i)]->y, 
				font, 
				textMenu[std::make_pair(currentState, i)]->text, 
				textMenu[std::make_pair(currentState, i)]->size);
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
	currentState = SETTING;
}

void GameMenu::menuWin()
{
	currentState = WIN;
	
}

void GameMenu::menuReturn()
{
	if (beforeState[beforeState.size() - 1] == NONE)
		win.close();
	else
	{ if (currentState == WIN || currentState == WIN2)
		{
			currentState = MAIN;
			return;
		}
	
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
