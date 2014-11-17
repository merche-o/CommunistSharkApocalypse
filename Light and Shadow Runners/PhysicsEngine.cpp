#include "PhysicsEngine.h"


PhysicsEngine::PhysicsEngine(Map & Map, std::vector<Player*> & Players)
	: map(Map), players(Players), scale(1)
{
}


PhysicsEngine::~PhysicsEngine(void)
{
}

void	PhysicsEngine::Update(void)
{
	Player * player;
	for(int i = 0; i < players.size(); i++)
	{
		player = players.at(i);
		applyGravity(*player);
		collide(*player);
	}
}

#pragma region Forces
void	PhysicsEngine::applyGravity(Player & player)
{
	if (player.side == e_color::BLACK)
		player.accelVect.add(9.81 * (SCALE), 0);
	else
		player.accelVect.add(-9.81 * (SCALE), 0);
	player.accelCount++;
}
#pragma endregion

#pragma region Collisions
void	PhysicsEngine::collide(Player & player)
{
//	if (
}

int		PhysicsEngine::getMapHeight(Player & player)
{
	int height = 480;
	bool tmp = false;
	for ( mapIterator i = map.map.begin(); i != map.map.end(); i++)
	{
		if (i->first.first == e_color::BLACK)
		{
			if (!tmp && (i->second->y + i->second->height > player.y))
				height = i->second->width;
			else if (tmp && 
					(	(player.side == e_color::BLACK && i->second->width < height) || 
						(player.side == e_color::WHITE && i->second->width > height)))
				height = i->second->width;
			if (i->second->y + i->second->height > player.y + player.height)
				break;
		}
	}
	return (height);
}
#pragma endregion