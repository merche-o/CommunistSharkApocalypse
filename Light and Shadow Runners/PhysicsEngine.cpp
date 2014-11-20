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
	int mapHeight;
	for(int i = 0; i < players.size(); i++)
	{
		player = players.at(i);
		x = player->x;
		y = player->y;
		mapHeight = getMapHeight(player);
		if (player->jumpStrength == 0)
			applyGravity(player, x, y, mapHeight);
		else
			applyJump(player, x, y);
		player->x = x;
		player->y = y;
	}
}

void	PhysicsEngine::applyGravity(Player * player, float & x, float & y, int mapHeight)
{
	if (player->side == e_color::BLACK && x + player->width + 1 != mapHeight)
	{
		x += player->fallSpeed * player->loopTime;
		if (x + player->width + 1 > mapHeight)
			x = mapHeight - player->width - 1;
		player->fallSpeed *= 1.05;
	}
	else if (player->side == e_color::WHITE && x - 1 != mapHeight)
	{
		x -= player->fallSpeed * player->loopTime;
		if (x - 1 < mapHeight)
			x = mapHeight + 1;
		player->fallSpeed *= 1.05;
	}
	if (player->fallSpeed > player->maxFallSpeed)
		player->fallSpeed = player->maxFallSpeed;
	if (!player->onTheFloor &&
		((player->side == e_color::WHITE && x - 1 == mapHeight) ||
		(player->side == e_color::BLACK && x + player->width + 1 == mapHeight)))
	{
		player->onTheFloor = true;
		player->fallSpeed = player->initFallSpeed;
	}
}

void	PhysicsEngine::applyJump(Player * player, float & x, float & y)
{
	if (player->side == e_color::BLACK)
	{
		x -= player->jumpStrength * player->loopTime;
	}
	else
	{
		x += player->jumpStrength * player->loopTime;
	}
	player->jumpStrength *= 0.87;

	if (player->jumpStrength < 30)
		player->jumpStrength = 0;
}


int		PhysicsEngine::getMapHeight(Player * player)
{
	int height = 480;
	bool tmp = false;
	for ( mapIterator i = map.map.begin(); i != map.map.end(); i++)
	{
		if (i->first.first == e_color::BLACK)
		{
			if (!tmp && (i->second->y + i->second->height > player->y))
				height = i->second->width;
			else if (tmp && 
					(	(player->side == e_color::BLACK && i->second->width < height) || 
						(player->side == e_color::WHITE && i->second->width > height)))
				height = i->second->width;
			if (i->second->y + i->second->height > player->y + player->height)
				break;
		}
	}
	return (height);
}
