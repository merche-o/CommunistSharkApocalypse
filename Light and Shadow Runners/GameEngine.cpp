#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
	: graphic(window, player, loopTime), menu(window, event, parameters, restart), sound(), event(window, player)
{
	sound.musicOFF();
	sound.playMusic(sound.music);


	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT, Settings::CASE_SIZE), Settings::GAME_NAME);
	window.setFramerateLimit(30);
	
	player.push_back(new Player());
	
	state = MENU;
	restart = false;
}


GameEngine::~GameEngine(void)
{
}

void GameEngine::run()
{
    while (window.isOpen())
    {
		if (state == MENU)
		{
			menu.run();
			if (restart == true)
				state = GAME;
		}
		else if (state == GAME)
		{
			if (restart == true)
			{
				globalClock.restart();
				restart = false;
			}
			
			window.clear();
	
			globalTimer = globalClock.getElapsedTime();
			loopTime = globalTimer.asSeconds();
			globalClock.restart();


			event.checkEvent();
		
		
			graphic.RefreshWindow();
		}
    }
}