#include "GameEngine.h"
#include <iostream>

GameEngine::GameEngine(void)
: map(), graphic(window, map,stars, player, loopTime), menu(window, event, parameters, restart, winner), sound(), event(window, player), ref(player, loopTime, map),  physicEngine(map, player, stars)
{
	sound.musicOFF();
	sound.playMusic(sound.music);

	winner = 2;
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

void GameEngine::resetGame()
{
	map.map.clear();
	map.init();
	stars.clear();
	int i = 0;
	while (i < player.size())
		{
			player[i]->reset();
			i++;
	}
	winner = 2;
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
		else	 if (state == WINSCREEN)
				{
					if ( winner == 0)
			menu.currentState= GameMenu::WIN;
					else 
						menu.currentState =GameMenu::WIN2;
			menu.refresh = true;
					menu.run();
					if (menu.currentState == GameMenu::MAIN)
					{	state = MENU;
				}
				
				
			}
		else if (state == GAME)
		{
			if (restart == true)
			{
				globalClock.restart();
				restart = false;
				resetGame();
			}
			
			globalTimer = globalClock.getElapsedTime();
			loopTime = globalTimer.asSeconds();
			globalClock.restart();
			ref.playerMove();
			ref.moveMapLine();
			
			winner = ref.killPlayer();
			
			if (winner != -1)
			{
				menu.beforeState.push_back(GameMenu::MAIN);
				state = WINSCREEN;
			}
			
			event.checkEvent();

			physicEngine.Update();
			
			window.clear();
			
			starsGenerator();
			starChangeColor();
			map.scroll();
			graphic.drawMap();
			graphic.drawStars();
			graphic.drawPlayer();
			graphic.drawLimits();
		
			graphic.RefreshWindow();
			//map.generator();
		
		}
    }
}

void GameEngine::starChangeColor()
{
	for (int i = 0; i < stars.size(); ++i)
	{stars[i]->color = WHITE;
		for (int j = map.plus; j < map.map.size() / 2; ++j)
		{
			if (stars[i]->y > map.map[std::make_pair(BLACK, j)]->y &&
				stars[i]->y < (map.map[std::make_pair(BLACK, j)]->y + map.map[std::make_pair(BLACK, j)]->height))
			{
				if (stars[i]->x < map.map[std::make_pair(BLACK, j)]->width)
				{
					stars[i]->color = WHITE;
					stars[i]->texture.loadFromFile("../Ressources/Images/lightstar.png");
				}
				else if (stars[i]->x > map.map[std::make_pair(BLACK, j)]->width)
				{
					stars[i]->color = BLACK;
					stars[i]->texture.loadFromFile("../Ressources/Images/darkstar.png");
				}
			}
		}
	}
}

void GameEngine::starsGenerator()
{
	popStar += loopTime;
	if (popStar >= 0.5)
	{
		srand(map.map[std::make_pair(BLACK, map.map.size() / 2 - 1)]->y * time(NULL));
		//int x1 = rand() % (310 + map.center);
		//int x2 = rand() % (310 - map.center);
		int x1 = rand() % (450 + map.center);
		int x2 = rand() % (450 - map.center);

		stars.push_back(new Star(x1, 0, WHITE));
		stars.push_back(new Star(Settings::WIDTH - x2 - 16, 0, BLACK));
		popStar = 0;
	}
}