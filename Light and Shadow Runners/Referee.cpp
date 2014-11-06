#include "Referee.h"
#include <iostream>

Referee::Referee(std::vector<Player *> &PlayerList, float &LoopTime)
	:playerList(PlayerList), loopTime(LoopTime)
{
	actionManager[UP] = &Referee::moveUp;
	actionManager[DOWN] = &Referee::moveDown;
	actionManager[LEFT] = &Referee::moveLeft;
	actionManager[RIGHT] = &Referee::moveRight;

	releaseActionManager[UP] = &Referee::RmoveUp;
	releaseActionManager[DOWN] = &Referee::RmoveDown;
	releaseActionManager[LEFT] = &Referee::RmoveLeft;
	releaseActionManager[RIGHT] = &Referee::RmoveRight;
}


Referee::~Referee(void)
{
}

void Referee::playerMove()
{
	for (int i = 0; i < playerList.size(); i++)
		{reducePlayerSize(playerList[i]);
			for (int i2 = 0; i2 < this->playerList[i]->inputMap.size(); i2++)
			{
			if (this->playerList[i]->inputMap[i2] == true)
				(this->*(actionManager[(e_input)i2]))(playerList[i]);
			else
				(this->*(releaseActionManager[(e_input)i2]))(playerList[i]);
			}	
		}
}


void Referee::moveLeft(Player *src)
{
	if(src->home == true && src->color == WHITE);
		//src->changeSide(src);
	else if (src->color == WHITE && src->home == false)
		jump(src);
	else if (src->color == BLACK && src->home == true)
		jump(src);
	else if (src->color == BLACK && src->home == false);
		//src->changeSide(src)
	
	return;
}


void Referee::moveRight(Player *src)
{
	if(src->home == true && src->color == WHITE)
		jump(src);
	else if (src->color == WHITE && src->home == false);
		//src->changeSide(src);
	else if (src->color == BLACK && src->home == true);
	//src->changeSide(src);
	else if (src->color == BLACK && src->home == false)
		jump(src);
	return;
}

void Referee::moveUp(Player *src)
{
	src->y -= src->speed  * this->loopTime;
	return;
}

void Referee::moveDown(Player *src)
{	src->y += src->speed  * this->loopTime;
	return;
	   
}				   




// release button Action

void Referee::RmoveLeft(Player *src)
{
	return;
}


void Referee::RmoveRight(Player *src)
{
	return;
}

void Referee::RmoveUp(Player *src)
{	
	return;
}

void Referee::RmoveDown(Player *src)
{				   
	return;		   
}				   

void Referee::moveMapLine(Player *src)
{				   
	if (src->color == WHITE && src->home == false);
	//src->scale -=  downSideSpeed * loopTime;	
	//map->PushWhiteSide();
	else if (src->color == BLACK && src->home == false);
	//src->scale -=  downSideSpeed * loopTime;	
	//map->PushBlackSide();
	return;		   
}				   

bool Referee::killPlayer()
{
	for (int i = 0; i < playerList.size(); i++)
		{
			if (playerList[i]->scale <= 0.1)
				playerList.erase(playerList.begin() + i);
			else if (playerList[i]->y  > Settings::HEIGHT)
				playerList.erase(playerList.begin() + i);
			else if (i == 0 && playerList[i]->x + playerList[i]->width > Settings::WIDTH)
				playerList.erase(playerList.begin() + i);
			else if (i == 1 && playerList[i]->x > Settings::WIDTH)
				playerList.erase(playerList.begin() + i);

		}
	if (playerList.size() < 2)
			return true;
	else
		return false;
}	

void Referee::jump(Player *src)
	{
		if (src->color == WHITE)
			std::cout << "JUMP WHITE" <<std::endl;
		else
				std::cout << "JUMP BLACK" <<std::endl;
}

void Referee::changeSide(Player *src)
		{
		if (src->home == true)
			src->home = false;
		else
			src->home = true;
}

void Referee::reducePlayerSize(Player *src)
{
	//have to change the ratio of reduce to match a proper gameplay
	if (src->home == false)
		src->scale -= 0.1 * loopTime;
}

