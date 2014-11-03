#include "Referee.h"


Referee::Referee(std::vector<Player *> &PlayerList, float &LoopTime)
	:playerList(PlayerList), loopTime(LoopTime)
{
	actionManager[UP] = &Referee::moveUp;
	actionManager[DOWN] = &Referee::moveDown;
	actionManager[LEFT] = &Referee::moveLeft;
	actionManager[RIGHT] = &Referee::moveRight;

	releaseActionManager[UP] = &Referee::RmoveUp;
	releaseActionManager[DOWN] = &Referee::moveDown;
	releaseActionManager[LEFT] = &Referee::RmoveLeft;
	releaseActionManager[RIGHT] = &Referee::RmoveRight;
}


Referee::~Referee(void)
{
}

void Referee::playerMove()
{
	for (int i = 0; i < playerList.size(); i++)
		{
			for (int i2 = 0; i2 < this->playerList[i]->inputMap.size(); i2++)
			{
			if (this->playerList[i]->inputMap[i2] == true)
				(this->*(actionManager[(e_input)i]))(playerList[i]);
			else
				(this->*(releaseActionManager[(e_input)i]))(playerList[i]);
			}	
		}
}


void Referee::moveLeft(Player *src)
{
	/*if(src->home == true && src->color == WHITE);
		//src->changeSide();
	else if (src->side == S_WHITE);
		//src->changeSide();
	*/
	return;
}


void Referee::moveRight(Player *src)
{
/*	if(src->side == S_WHITE);
		//src->jump();
	else if (src->side == S_BLACK);
		//src->changeSide();*/
	return;
}

void Referee::moveUp(Player *src)
{
	src->y -= src->speed * this->loopTime;
	return;
}

void Referee::moveDown(Player *src)
{				
	src->y += src->speed * this->loopTime;
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
			if(playerList[i]->scale <= 0.1)
				playerList.erase(playerList.begin() + i);
		}
	if (playerList.size() < 2)
	return false;
	else
		return true;
}	