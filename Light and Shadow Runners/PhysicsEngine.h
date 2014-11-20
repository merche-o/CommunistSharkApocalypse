#pragma once

#include	<vector>
#include	<iterator>
#include	"Settings.h"
#include	"Vector2d.h"
#include	"Map.h"
#include	"Player.h"

#define		SCALE	(1)

typedef std::map<std::pair<e_color, int>, Rect*>::iterator mapIterator;


class PhysicsEngine
{
public:
	Map &			map;
	std::vector<Player*> &	players;
private:
	float			scale;

public:
	PhysicsEngine(Map &, std::vector<Player*> &);
	~PhysicsEngine(void);
	void			Update(void);
private:
	void			applyGravity(Player*, float&, float&, int);
	void			applyJump(Player*, float&, float&);
	int				getMapHeight(Player*);
};

