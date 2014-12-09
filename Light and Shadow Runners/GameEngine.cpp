#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
: map(), graphic(window, map,stars, player, loopTime), menu(window, event, parameters, restart), sound(), event(window, player), ref(player, loopTime, map),  physicEngine(map, player, stars)
{
	sound.musicOFF();
	sound.playMusic(sound.music);


	window.create(sf::VideoMode(Settings::WIDTH, Settings::HEIGHT), Settings::GAME_NAME);
	window.setFramerateLimit(30);
	
	player.push_back(new Player(loopTime,2));
	player.push_back(new Player(loopTime,1));

	
	state = MENU;
	restart = false;

	//stars.push_back(new Star(10, 10, WHITE));
	//stars.push_back(new Star(Settings::WIDTH - 26, 10, BLACK));
	popStar = 0;
}


GameEngine::~GameEngine(void)
{
}

void GameEngine::run()
{
	int winner = 2;
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
			ref.moveMapLine();
			
			winner = ref.killPlayer();
			
			if (winner != -1)
			{
				std::cout << "Player " << winner +1  <<  " win !" << std::endl;
				state = MENU;

			}



			physicEngine.Update();
			event.checkEvent();

			window.clear();
			//map.generator();
			starsGenerator();
			map.scroll();
			graphic.drawMap();
			graphic.drawStars();
			graphic.drawPlayer();
			graphic.drawLimits();
		
			graphic.RefreshWindow();
		}
    }
}

void GameEngine::starsGenerator()
{
	popStar += loopTime;
	if (popStar >= 0.2)
	{
		srand(map.map[std::make_pair(BLACK, map.map.size() / 2 - 1)]->y * time(NULL));
		int x = rand() % 310;

		stars.push_back(new Star(x, 0, WHITE));
		stars.push_back(new Star(Settings::WIDTH - x - 16, 0, BLACK));
		popStar = 0;
	}
}