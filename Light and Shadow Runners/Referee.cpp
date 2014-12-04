#include "Referee.h"
#include <iostream>


Referee::Referee(std::vector<Player *> &PlayerList, float &LoopTime, Map &Map)
	:playerList(PlayerList), loopTime(LoopTime), map(Map)
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
	for (int i = 0; i < playerList.size(); i++)
		{
			playerList[i]->nextFrameY = playerList[i]->y + (playerList[i]->maxSpeed * playerList[i]->speedScale)  * this->loopTime;
			reducePlayerSize(playerList[i]);
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

	src->speedScale -= 0.25 * src->scale;
	src->speedScale *= 1.15;
	if (src->speedScale < -1)
		src->speedScale = -1;

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

{
	src->speedScale += 0.25 * src->scale;
	src->speedScale *= 1.15;
	if (src->speedScale > 1)
		src->speedScale = 1;

	return;
	   
}				   




// release button Action

void Referee::RmoveLeft(Player *src)
{

	if (src->color == WHITE && src->home == false)
		Rjump(src);
	if (src->color == BLACK && src->home == true)
		Rjump(src);

	
	return;
}


void Referee::RmoveRight(Player *src)
{
	if(src->home == true && src->color == WHITE)
		Rjump(src);
	else if (src->color == BLACK && src->home == false)
		Rjump(src);

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
	/*for (int i = 0; i < playerList.size(); i++)
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
		}*/

	

		return -1;
}	

void Referee::jump(Player *src)
{
	if ((src->collideUp || src->collideDown) && src->JumpIsReleased && !src->onTheFloor)
	{
		if (src->jumpStrength < 1000)
			src->jumpStrength = 1000;
		src->speedScale = 1 * src->scale + 0.1;
		if (src->speedScale > 1)
			src->speedScale = 1;
		if (src->collideDown)
			src->speedScale *= -1;
		src->fallSpeed = src->initFallSpeed;
	}


	if (src->isJumping || (src->onTheFloor && src->JumpIsReleased))
		{
			if (src->currentJumpTime > src->maxJumpTime)
			{
				src->currentJumpTime = 0;
				src->isJumping = false;
			}
			else
			{
				src->currentJumpTime += src->loopTime;
				src->onTheFloor = false;
				src->isJumping = true;
				src->jumpStrength = src->initJumpStrength;
			}
		}
	src->JumpIsReleased = false;
}

void Referee::Rjump(Player *src)
{
	src->isJumping = false;
	src->JumpIsReleased = true;
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
			src->x = Settings::WIDTH +   correctWidth  - (src->x +src->width);
		src->home = true;
	}
	if (src->side == BLACK)
		src->side = WHITE;
	else
		src->side = BLACK;
			
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

