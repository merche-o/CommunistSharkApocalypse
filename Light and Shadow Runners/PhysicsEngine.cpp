#include "PhysicsEngine.h"
#include <iostream>


PhysicsEngine::PhysicsEngine(Map & Map, std::vector<Player*> & Players, std::vector<Star*> & Stars)
	: map(Map), players(Players), stars(Stars), scale(1)
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
		if (player->jumpStrength <= 0)
			applyGravity(player, x, y);
		else
			applyJump(player, x, y);
		collideWalls(player, x, y);
		y += map.speed;
		collideScreen(player, x, y);
		player->x = x;
		player->y = y;
		player->nextFrameY = y;
		starCollisions(player);
		if (player->onTheFloor)
			player->speedScale *= 0.8;
		else
			player->speedScale *= 0.85;
	}
}

void	PhysicsEngine::starCollisions(Player * player)
{
	for(int i = 0; i < stars.size(); i++)
	{
		if (!(	player->x + player->getWidth()	< stars[i]->x	||
				stars[i]->x + stars[i]->size	< player->x		||
				player->y + player->getWidth()	< stars[i]->y	||
				stars[i]->y + stars[i]->size	< player->y))
		{
			stars.erase(stars.begin() + i);
			player->scale += 0.05;
			if (player->scale > 1)
				player->scale = 1;
		}
	}
}

void	PhysicsEngine::applyGravity(Player * player, float & x, float & y)
{
	int mapHeight = mapHeightForPlayer(player);

	if (player->side == e_color::BLACK && x + player->getWidth() != mapHeight)
	{
		x += player->fallSpeed * player->loopTime * player->scale;
		if (x + player->getWidth() > mapHeight)
			x = mapHeight - player->getWidth();
		player->fallSpeed *= 1.1;
		player->onTheFloor = false;
	}
	else if (player->side == e_color::WHITE && x != mapHeight)
	{
		x -= player->fallSpeed * player->loopTime * player->scale;
		if (x < mapHeight)
			x = mapHeight;
		player->fallSpeed *= 1.1;
		player->onTheFloor = false;

	}
	if (player->fallSpeed > player->maxFallSpeed)
		player->fallSpeed = player->maxFallSpeed;
	if (((player->side == e_color::WHITE && x == mapHeight) ||
		(player->side == e_color::BLACK && x + player->getWidth() == mapHeight)))
	{
		player->onTheFloor = true;
		player->currentJumpTime = 0;
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
	int height;
	bool tmp = false;
	if (player->side == WHITE)
		height = 0;
	else
		height = Settings::WIDTH;
	for (int i = map.plus; i < map.map.size() / 2; ++i)
	{

		if (!tmp && (map.map[std::make_pair(BLACK, i)]->y <= player->y + player->getWidth() - 1))
			{
				height = map.map[std::make_pair(BLACK, i)]->width;
				tmp = true;
			}
		if (map.map[std::make_pair(BLACK, i)]->y + map.map[std::make_pair(BLACK, i)]->height < player->y)
			{
				break;
			}
		if (tmp && 
				(	(player->side == e_color::BLACK && map.map[std::make_pair(BLACK, i)]->width < height) || 
					(player->side == e_color::WHITE && map.map[std::make_pair(BLACK, i)]->width > height)))
			{
				height = map.map[std::make_pair(BLACK, i)]->width;
			}
	}
	return (height);
}

int		PhysicsEngine::mapHeightForPoint(float x, float y, e_color side)
{
	int height = 0;
	if (side == BLACK)
		height = Settings::WIDTH;

	for (int i = map.plus; i < map.map.size() / 2; ++i)
	{

		if (map.map[std::make_pair(BLACK, i)]->y <= y && 
			map.map[std::make_pair(BLACK, i)]->y + map.map[std::make_pair(BLACK, i)]->height >= y &&
			((side == BLACK &&  map.map[std::make_pair(BLACK, i)]->width < height) || (side == WHITE &&  map.map[std::make_pair(BLACK, i)]->width > height)))
			{
				height = map.map[std::make_pair(BLACK, i)]->width;
			}
	}
	return (height);
}


void		PhysicsEngine::collideScreen(Player * player, float & x, float & y)
{
	player->collideScreen = false;
	if (y < 0)
		y = 0;
	if (x < 0)
	{
		x = 0;
		player->collideScreen = true;
	}
	else if (x + player->getWidth() > Settings::WIDTH)
	{
		x = Settings::WIDTH - player->getWidth();
		player->collideScreen = true;
	}
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
		if ((player->side == WHITE && newHeightX > player->x && x < newHeightX) ||
			(player->side == BLACK && newHeightX < (player->x + player->getWidth() - 1) && (x + player->getWidth() - 1) > newHeightX))
		{
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
		if ((player->side == WHITE && newHeightX > player->x && x < newHeightX) ||
			(player->side == BLACK && newHeightX < (player->x + player->getWidth() - 1) && (x + player->getWidth() - 1) > newHeightX))
		{
			y = newHeightY - 1;
			player->collideDown = true;
		}
	}
}
