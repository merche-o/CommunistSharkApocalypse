#include "PhysicsEngine.h"
#include <iostream>


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
	float x;
	float y;
	for(int i = 0; i < players.size(); i++)
	{
		player = players.at(i);
		x = player->x;
		y = player->nextFrameY;
		player->collideDown = false;
		player->collideUp = false;
		/*if (player->color == BLACK)
			std::cout << player->fallSpeed << std::endl;*/
		if (player->jumpStrength == 0)
			applyGravity(player, x, y);
		else
			applyJump(player, x, y);
		collideWalls(player, x, y);
		player->x = x;
		player->y = y;
		player->nextFrameY = y;
		if (player->onTheFloor)
			player->speedScale *= 0.8;
		else
			player->speedScale *= 0.85;
	}
}

void	PhysicsEngine::applyGravity(Player * player, float & x, float & y)
{
	int mapHeight = mapHeightForPlayer(player);

	if (player->side == e_color::BLACK && x + player->getWidth() != mapHeight)
	{
		x += player->fallSpeed * player->loopTime * player->scale;
		if (x + player->getWidth() + 1 > mapHeight)
			x = mapHeight - player->getWidth() - 1;
		player->fallSpeed *= 1.1;
	}
	else if (player->side == e_color::WHITE && x - 1 != mapHeight)
	{
		x -= player->fallSpeed * player->loopTime * player->scale;
		if (x - 1 < mapHeight)
			x = mapHeight + 1;
		player->fallSpeed *= 1.1;
	}
	if (player->fallSpeed > player->maxFallSpeed /** player->scale*/)
		player->fallSpeed = player->maxFallSpeed /** player->scale*/;
	if (((player->side == e_color::WHITE && x - 1 == mapHeight) ||
		(player->side == e_color::BLACK && x + player->getWidth() + 1 == mapHeight)))
	{
		player->onTheFloor = true;
		player->fallSpeed = player->initFallSpeed;
	}
}

void	PhysicsEngine::applyJump(Player * player, float & x, float & y)
{
	if (player->side == e_color::BLACK)
	{
		x -= player->jumpStrength * player->loopTime * player->scale;
	}
	else
	{
		x += player->jumpStrength * player->loopTime * player->scale;
	}
	player->jumpStrength *= 0.85;

	if (player->jumpStrength < 80)
		player->jumpStrength = 0;
}


int		PhysicsEngine::mapHeightForPlayer(Player * player)
{
	int height1 = mapHeightForPoint(player->x, player->y, player->side);
	int height2 = mapHeightForPoint(player->x, player->y + player->getWidth() - 1, player->side);

	if (player->side == e_color::WHITE)
	{
		if (height1 > height2)
			return (height1);
		return (height2);
	}
	else if (height1 < height2)
		return(height1);
	return (height2);
}

int		PhysicsEngine::mapHeightForPoint(float x, float y, e_color side)
{
	int height = 480;
	bool tmp = false;
	for ( mapIterator mapIt = map.map.begin(); mapIt != map.map.end(); mapIt++)
	{
		if (mapIt->first.first == e_color::BLACK)
		{
			if (!tmp && (mapIt->second->y + mapIt->second->height >= y))
			{
				height = mapIt->second->width;
				tmp = true;
			}
			else if (tmp && 
					(	(side == e_color::BLACK && mapIt->second->width < height) || 
						(side == e_color::WHITE && mapIt->second->width > height)))
			{
				height = mapIt->second->width;
			}
			if (mapIt->second->y + mapIt->second->height > y)
				break;
		}
	}
	return (height);
}



void		PhysicsEngine::collideWalls(Player * player, float & x, float & y)
{
	int		newHeightX;
	int		tmp;
	int		newHeightY;

	if (y < player->y)
	{
		newHeightX = mapHeightForPoint(x, player->y, player->side);
		newHeightY = player->y;
		for (int i = player->y; i >= y; --i)
		{
			tmp = mapHeightForPoint(x, i, player->side);
			if ((player->side == WHITE && tmp > newHeightX) || (player->side == BLACK && tmp < newHeightX))
			{
				newHeightX = tmp;
				newHeightY = i;
			}
		}
		//std::cout << newHeightX << " " << newHeightY << " x = " << x << std::endl;
		if ((player->side == WHITE && newHeightX > player->x && x < newHeightX) ||
			(player->side == BLACK && newHeightX < (player->x + player->getWidth() - 1) && (x + player->getWidth() - 1) > newHeightX))
		{
			//std::cout << "collision !" << std::endl;
			y = newHeightY + 1;
			player->collideUp = true;

		}
	}
	else if (y > player->y)
	{
		newHeightX = mapHeightForPoint(x, player->y + player->getWidth() - 1, player->side);
		newHeightY = player->y + player->getWidth() - 1;
		for (int i = player->y; i <= y; ++i)
		{
			tmp = mapHeightForPoint(x, i + player->getWidth() - 1, player->side);
			if ((player->side == WHITE && tmp > newHeightX) || (player->side == BLACK && tmp < newHeightX))
			{
				newHeightX = tmp;
				newHeightY = i;
			}
		}
		//std::cout << "haut point de la map : " << newHeightX << " sa coordonnée en y : " << newHeightY << " x = " << x << " y = " << y << std::endl;
		if ((player->side == WHITE && newHeightX > player->x && x < newHeightX) ||
			(player->side == BLACK && newHeightX < (player->x + player->getWidth() - 1) && (x + player->getWidth() - 1) > newHeightX))
		{
			//std::cout << "collision ! nouvelle coordonnée en y = " << newHeightY - 2 << std::endl;
			y = newHeightY - 2;
			player->collideDown = true;
		}
	}
}
