#pragma once

#include "Player.h"
#include "Event.h"
#include "PhysicsEngine.h"
#include "Settings.h"
#include "Map.h"
//#include <vector>

class Referee
{
private:
	Map &map;
	std::vector<Player *> &playerList;
	float &loopTime;
	std::map<e_input, void(Referee:: *)(Player *src)> actionManager;
	std::map<e_input, void(Referee:: *)(Player *src)> releaseActionManager;
	float correctWidth;
public:

	Referee(std::vector<Player *> &PlayerList, float &LoopTime, Map &Map);

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
	void Rjump(Player *src);
	void changeSide(Player *src);
	void moveMapLine();
	int killPlayer();
	void reducePlayerSize(Player *src);
	void getCoins(Player *src);
};

