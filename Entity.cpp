//Entity.cpp

#include "Level.h"
#include "Entity.h"
#include <cstdlib>

// //Functions
Entity::Entity()
{
	x = 0;
	y = 0;
	width = 8;
	height = 8;
	xVel = STATIONARY;
	yVel = STATIONARY;
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
void Entity::ApplyVelocity(Level level)
{
	ApplyTerminal();
	
	x += (xVel >> 3);	//Use of shift operation fixes problems with dividing when -4 < Vel < 4
	for (int i = 0; i < level.numofplatforms; i++)
	{
		MoveBackIfColliding(x, xVel, level.platform[i]);
	}
	
	// for (int i = 0; i < level.numofcubes; i++)
	// {
		// MoveBackIfColliding(level.cube[i]);
	// }
	
	//Ditto for y
	y += (yVel >> 3);	//Use of shift operation fixes problems with dividing when -4 < Vel < 4
	
	for (int i = 0; i < level.numofplatforms; i++)
	{
		MoveBackIfColliding(y, yVel, level.platform[i]);
	}
	
	// for (int i = 0; i < level.numofcubes; i++)
	// {
		// MoveBackIfColliding(y, yVel, level.cube[i]);
	// }
}

void Entity::MoveBackIfColliding(int &position, int &axisVel, Object obstacle)
{
	if (IsColliding(obstacle))	//If not colliding with any obstacle, allow movement
	{	
		while (true)	//Read comment below for why I'm doing this
		{
			position -= (PlusOrMinus(axisVel));				//Move the entity back 
			if (!IsColliding(obstacle))	//until it is no longer colliding
			{
				break;
			}
		}
		axisVel = STATIONARY;	//This way I only set velocity to stationary if player has collided with an obstacle
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