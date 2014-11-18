#pragma once

#include <math.h>

class Vector2d
{
public:
	float	x;
	float	y;

public:
	Vector2d(float, float);
	~Vector2d(void);
	#pragma region void add();
	void	add(float, float);
	void	add(float);
	void	add(Vector2d&);
	#pragma endregion
	#pragma region void div();
	void	div(float, float);
	void	div(float);
	void	div(Vector2d&);
	#pragma endregion
	void normalize(void);
private:
	float	getNorm(void);
};