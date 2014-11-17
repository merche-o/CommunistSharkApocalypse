#include "Vector2d.h"

Vector2d::Vector2d(float X, float Y)
	: x(X), y(Y)
{
}

Vector2d::~Vector2d(void)
{
}

#pragma region Vector2d::add()
void	Vector2d::add(float x, float y)
{
	this->x += x;
	this->y += y;
}
void	Vector2d::add(float nb)
{
	this->x += nb;
	this->y += nb;
}
void	Vector2d::add(Vector2d & vector2d)
{
	this->x += vector2d.x;
	this->y += vector2d.y;
}
#pragma endregion

#pragma region Vector2d::div()
void	Vector2d::div(float x, float y)
{
	this->x /= x;
	this->y /= y;
}
void	Vector2d::div(float nb)
{
	this->x /= nb;
	this->y /= nb;
}
void	Vector2d::div(Vector2d & vector2d)
{
	this->x /= vector2d.x;
	this->y /= vector2d.y;
}
#pragma endregion

float	Vector2d::getNorm()
{
	return (sqrt(pow(this->x, 2) + pow(this->y, 2)));
}

void	Vector2d::normalize()
{00
	float norm = this->getNorm();
	this->x /= norm;
	this->y /= norm;
}