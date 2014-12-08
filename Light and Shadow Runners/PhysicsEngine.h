#pragma once

#include	<vector>
#include	<iterator>
#include	"Settings.h"
#include	"Vector2d.h"
#include	"Map.h"
#include	"Player.h"
#include	"Star.h"

#define		SCALE	(1)

typedef std::map<std::pair<e_color, int>, Rect*>::iterator mapIterator;


class PhysicsEngine
{
public:
	Map &			map;
	std::vector<Player*> &	players;
	std::vector<Star*> & stars;
private:
	float			scale;

public:
	PhysicsEngine(Map &, std::vector<Player*> &, std::vector<Star*> &);
	~PhysicsEngine(void);
	void			Update(void);
private:
	void			starCollisions(Player * player);
	void			applyGravity(Player*, float&, float&);
	void			applyJump(Player*, float&, float&);
	void			collideWalls(Player*, float&, float&);
	void			collideScreen(Player*, float&, float&);
	int				mapHeightForPlayer(Player*);
	int				mapHeightForPoint(float, float, e_color);
};

