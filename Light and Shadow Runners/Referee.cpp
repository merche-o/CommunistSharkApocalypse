#include "Referee.h"
#include <iostream>


Referee::Referee(std::vector<Player *> &PlayerList, float &LoopTime, Map &Map)
	:playerList(PlayerList), loopTime(LoopTime), physics(Map, PlayerList), map(Map)
{
	actionManager[UP] = &Referee::moveUp;
	actionManager[DOWN] = &Referee::moveDown;
	actionManager[LEFT] = &Referee::moveLeft;
	actionManager[RIGHT] = &Referee::moveRight;

	releaseActionManager[UP] = &Referee::RmoveUp;
	releaseActionManager[DOWN] = &Referee::RmoveDown;
	releaseActionManager[LEFT] = &Referee::RmoveLeft;
	releaseActionManager[RIGHT] = &Referee::RmoveRight;
	correctWidth = 0;
}


Referee::~Referee(void)
{
}

void Referee::playerMove()
{
	physics.Update();
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

void Referee::getCoins(Player *src)
{
	//maybe Have to change value
	src->scale += 1 * loopTime;
}

void Referee::moveLeft(Player *src)
{
	
	if(src->home == true && src->color == WHITE)
		this->changeSide(src);
	else if (src->color == WHITE && src->home == false)
		jump(src);
	else if (src->color == BLACK && src->home == true)
		jump(src);
	else if (src->color == BLACK && src->home == false)
		this->changeSide(src);
	return;
}


void Referee::moveRight(Player *src)
{
	
	if(src->home == true && src->color == WHITE)
		jump(src);
	else if (src->color == WHITE && src->home == false)
		this->changeSide(src);
	else if (src->color == BLACK && src->home == true)
		this->changeSide(src);
	else if (src->color == BLACK && src->home == false)
		jump(src);
	return;
}

void Referee::moveUp(Player *src)
{
	if (src->inDash == 0)
		src->inDash = 1;
	if (src->inDash == 2 && src->tmpTime < 0.2)
		{
			src->inDash = 3;
			std::cout << "DASH UP" << std::endl;
}
	src->y -= src->speed  * this->loopTime;
	return;
}

void Referee::moveDown(Player *src)
{	
	if (src->inDash == 0)
		src->inDash = -1;
	if (src->inDash == -2 && src->tmpTime < 0.2)
		{
			src->inDash = -3;
			std::cout << "DASH DOWN" << std::endl;
			}
	src->y += src->speed  * this->loopTime;
	return;
	   
}				   




// release button Action

void Referee::RmoveLeft(Player *src)
{
//	src->t
	
	return;
}


void Referee::RmoveRight(Player *src)
{
	return;
}

void Referee::RmoveUp(Player *src)
{	if(src->inDash == 1)
	{
		src->tmpTime = 0;
		src->inDash = 2;
		src->tmpTime += src->loopTime;
	}
	else if (src->inDash == 2)
		{
			src->tmpTime += loopTime;
		}
	 if (src->inDash > 0 && src->tmpTime > 0.5)
		{
			
			src->inDash = 0;
			src->tmpTime = 0;
	}
	 if (src->inDash == 0)
		src->tmpTime = 0;
	 if (src->inDash == 3)
		src->tmpTime += src->loopTime;
	
	return;
}

void Referee::RmoveDown(Player *src)
{			
	if(src->inDash == -1)
	{
		src->tmpTime = 0;
		src->inDash = -2;
		src->tmpTime += src->loopTime;
	}
	else if (src->inDash == -2)
		{
			src->tmpTime += loopTime;
		}
	 if (src->inDash < 0 && src->tmpTime > 0.5)
		{
			src->inDash = 0;
			src->tmpTime = 0;
	}
	 if (src->inDash == 0)
		src->tmpTime = 0;
	 if (src->inDash == -3)
		src->tmpTime += src->loopTime;
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

int Referee::killPlayer()
{
	for (int i = 0; i < playerList.size(); i++)
		{
			if (playerList[i]->scale <= 0.1){
				playerList.erase(playerList.begin() + i);
				return i;
			}
			else if (playerList[i]->y  > Settings::HEIGHT){
				playerList.erase(playerList.begin() + i);
				return i;
			}
				
			else if (i == 0 && playerList[i]->x + playerList[i]->width > Settings::WIDTH){
				playerList.erase(playerList.begin() + i);
				return i;	
			}
			else if (i == 1 && playerList[i]->x > Settings::WIDTH){
				playerList.erase(playerList.begin() + i);
				return i;
			}
		}

	

		return -1;
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
	{
		if( src->color == BLACK)
			src->x = Settings::WIDTH - (src->x + src->width) ;
		if (src->color == WHITE)
			src->x = -(src->x+ src->width - (Settings::WIDTH + correctWidth));
		src->home = false;
	}
	else if (src->home == false)
	{
		if (src->color == BLACK)
			src->x = -(src->x + src->width - Settings::WIDTH);
		if (src->color == WHITE)
			src->x = Settings::WIDTH +   correctWidth  - (src->x +src->width );
		src->home = true;
	}
			
}

void Referee::reducePlayerSize(Player *src)
{
	//have to change the ratio of reduce to match a proper gameplay
	if (src->home == false)
		{	
			src->scale -= 0.1 * loopTime;
			if (src->color == WHITE)
				{
					correctWidth +=  0.1 * loopTime * src->width;
					src->x += 0.1 * loopTime * src->width;
					
				}
		}
		
}

