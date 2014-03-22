//Entity.cpp

#include "Entity.h"
#include "Level.h"
#include <cstdlib>

// //Functions
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
	terminalx = 24;
	terminaly = 128;
}

//Applies the acceleration of gravity to the objects current velocity
void Entity::ApplyGravity()
{
	yVel += gravity * 0.5;	//Higher multiplier = higher gravity; lowest practical value = 0.25
}

//Applies the velocities of objects to their positions
void Entity::ApplyVelocity(Object obstacle)
{
	ApplyTerminal();
	x += (xVel >> 3);	//Use of shift operation fixes problems with dividing when -4 < Vel < 4
	while (true)
	{
		if (!IsColliding(obstacle))	//If not colliding with any obstacle, allow movement
		{
			break;
		}
		else
		{
			x -= (PlusOrMinus(xVel));	//Move the entity back until it is no longer colliding
		}
		xVel = STATIONARY;
	}

	y += (yVel >> 3);
	while (true)
	{
		if (!IsColliding(obstacle))
		{
			break;
		}
		else
		{
			y -= (PlusOrMinus(yVel));
		}
		yVel = STATIONARY;
	}
}

void Entity::ApplyVelocity(Level level)
{
	ApplyTerminal();
	x += (xVel >> 3);	//Use of shift operation fixes problems with dividing when -4 < Vel < 4
	for (int i = 0; i < level.numofplatforms; i++)
	{
		while (true)
		{
			if (!IsColliding(level.platform[i]))	//If not colliding with any obstacle, allow movement
			{
				break;
			}
			else
			{
				x -= (PlusOrMinus(xVel));	//Move the entity back until it is no longer colliding
			}
			xVel = STATIONARY;
		}
	}
	
	y += (yVel >> 3);
	for (int i = 0; i < level.numofplatforms; i++)
	{
		while (true)
		{
			if (!IsColliding(level.platform[i]))
			{
				break;
			}
			else
			{
				y -= (PlusOrMinus(yVel));
			}
			yVel = STATIONARY;
		}
	}
}

//Set velocities = terminal if they exceed them.
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
			xVel = -terminalx + 16; //Bit shift negative bias means character goes to the left quicker without offset. 
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
			yVel = -terminaly + 16;
		}
	}
}

//Reverses the direction of gravity. Used in the Reverse Gravity Dimension
void Entity::ReverseGravity()
{
	gravity *= -1;
}

//Returns objnum
int Entity::GetObjNum()
{
	return objnum;
}

//Returns sign of x
int Entity::PlusOrMinus(int x)
{
	if (x > 0)
	{
		return 1;
	}
	else if (x < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}