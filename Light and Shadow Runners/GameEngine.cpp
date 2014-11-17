#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
	: map(), graphic(window, map.map, player, loopTime), menu(window, event, parameters, restart), sound(), event(window, player), ref(player, loopTime, map)
{
	sound.musicOFF();
	sound.playMusic(sound.music);


	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT), Settings::GAME_NAME);
	window.setFramerateLimit(30);
	
	player.push_back(new Player(loopTime,2));
	player.push_back(new Player(loopTime,1));
	
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
			
			globalTimer = globalClock.getElapsedTime();
			loopTime = globalTimer.asSeconds();
			globalClock.restart();
			ref.playerMove();
			if (ref.killPlayer() == true)
				state = MENU;



			event.checkEvent();

			window.clear();
			graphic.drawMap();
			graphic.drawPlayer();
		
			graphic.RefreshWindow();
		}
    }
}