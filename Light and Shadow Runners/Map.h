#pragma once

#include <map>
#include "Settings.h"
#include "Rect.h"

class Map
{
public:
std::map<std::pair<e_color, int>, Rect*> map;

public:
	Map(void);
	~Map(void);
};

