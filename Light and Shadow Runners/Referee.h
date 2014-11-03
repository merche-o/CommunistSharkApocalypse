#pragma once

#include "Player.h"
#include "Event.h"
#include "PhysicsEngine.h"
//#include <vector>

class Referee
{
private:
	PhysicsEngine physics;
	std::vector<Player *> &playerList;
	float &loopTime;
	std::map<e_input, void(Referee:: *)(Player *src)> actionManager;
	std::map<e_input, void(Referee:: *)(Player *src)> releaseActionManager;
public:
	Referee(std::vector<Player *> &PlayerList, float &LoopTime);
	~Referee(void);
	void playerMove();

	void moveLeft(Player *src);
	void moveRight(Player *src);
	void moveUp(Player *src);
	void moveDown(Player *src);

	//ReleaseAction
	void RmoveLeft(Player *src);
	void RmoveRight(Player *src);
	void RmoveDown(Player *src);
	void RmoveUp(Player *src);

	//GamePlay
	void jump(Player *src);
	void changeSide(Player *src);
	void moveMapLine(Player *src);
	bool killPlayer();
};

