#include "Map.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


Map::Map(void)
{
	plus = 0;
	center = 0;
	speed = Settings::SPEED_MAP;
	map[std::make_pair(BLACK, 0)] = new Rect(0, Settings::HEIGHT / 2, Settings::WIDTH / 2 - 100, Settings::HEIGHT / 2);
	map[std::make_pair(WHITE, 0)] = new Rect(Settings::WIDTH / 2 - 100, Settings::HEIGHT / 2, Settings::WIDTH / 2 + 100, Settings::HEIGHT / 2);
	map[std::make_pair(BLACK, 1)] = new Rect(0, 0, Settings::WIDTH / 2, Settings::HEIGHT / 2);
	map[std::make_pair(WHITE, 1)] = new Rect(Settings::WIDTH / 2, 0, Settings::WIDTH / 2, Settings::HEIGHT / 2);
	for (int i = 0; i < 10; ++i)
		generator();
}


Map::~Map(void)
{
}

void Map::generator()
{
	srand(map[std::make_pair(BLACK, map.size() / 2 - 1)]->y * time(NULL));
	int h = rand() % 200 + 200;
	int w = rand() % 300;

	map[std::make_pair(BLACK, map.size() / 2)] = new Rect(0,
															map[std::make_pair(BLACK, map.size() / 2 - 1)]->y - h,
															Settings::WIDTH / 2 + w - 150 + center,
															h);
	map[std::make_pair(WHITE, map.size() / 2)] = new Rect(Settings::WIDTH / 2 + w - 150 + center,
															map[std::make_pair(WHITE, map.size() / 2 - 1)]->y - h,
															Settings::WIDTH / 2 - w + 150 - center,
															h);
}

void Map::scroll()
{
	for (int i = plus; i < map.size() / 2; ++i)
	{
		map[std::make_pair(BLACK, i)]->y += speed;
		map[std::make_pair(WHITE, i)]->y += speed;
		if (map[std::make_pair(BLACK, i)]->y > Settings::HEIGHT)
		{
			generator();
			//map.erase(std::make_pair(BLACK, i));
			//map.erase(std::make_pair(WHITE, i));
			++plus;
		}
	}
}