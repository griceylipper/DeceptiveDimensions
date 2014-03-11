//Entity.cpp

#include "Entity.h"
#include <cstdlib>

//Functions
Entity::Entity()
{
	x = 0;
	y = 0;
	width = 8;
	height = 8;
	xVel = 0;
	yVel = 0;
	gravity = 10;
	weight = 1;
	objnum = 0;
	terminalx = 30;
	terminaly = 160;
}

//Constructor which allows setting of all eight data values
Entity::Entity(int a, int b, int w, int h, int xV, int yV, int g, int W, int o)
{
	Reset(a, b, w, h, xV, yV, g, W, o);
}

//Reset for all eight data values
void Entity::Reset(int a, int b , int w, int h, int xV, int yV, int g, int W, int o)
{
	x = a;
	y = b;
	width = w;
	height = h;
	xVel = xV;
	yVel = yV;
	gravity = g;
	weight = W;
	objnum = o;
	terminalx = 30;
	terminaly = 160;
}

//Applies the acceleration of gravity to the objects current velocity
void Entity::ApplyGravity()
{
	yVel += (gravity / 2.5);
}

//Applies the velocities of objects to their positions
void Entity::ApplyVelocity()
{
	ApplyTerminal();
	x += (xVel / 10);
	y += (yVel / 10);
}

void Entity::ApplyTerminal()
{
	if (abs(xVel) > terminalx)
	{
		if (xVel > 0)
		{
			xVel = terminalx;
		}
		else
		{
			xVel = -terminalx;
		}
	}
	if (abs(yVel) > terminaly)
	{
		if (yVel > 0)
		{
			yVel = terminaly;
		}
		else
		{
			yVel = -terminaly;
		}
	}
}

//Reverses the direction of gravity. Used in the Reverse Gravity Dimension
void Entity::ReverseGravity()
{
	gravity *= -1;
}