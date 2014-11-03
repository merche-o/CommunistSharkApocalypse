#include "Map.h"


Map::Map(void)
{
	map[std::make_pair(BLACK, 0)] = new Rect(0, 0, Settings::WIDTH / 2, Settings::HEIGHT / 2);
	map[std::make_pair(WHITE, 0)] = new Rect(Settings::WIDTH / 2, 0, Settings::WIDTH / 2, Settings::HEIGHT / 2);
	map[std::make_pair(BLACK, 1)] = new Rect(0, Settings::HEIGHT / 2, Settings::WIDTH / 2 - 100, Settings::HEIGHT / 2);
	map[std::make_pair(WHITE, 1)] = new Rect(Settings::WIDTH / 2 - 100, Settings::HEIGHT / 2, Settings::WIDTH / 2 + 100, Settings::HEIGHT / 2);
}


Map::~Map(void)
{
}
