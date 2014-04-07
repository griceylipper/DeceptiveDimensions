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
	
	StepAxis(x, xVel, level);
	StepAxis(y, yVel, level);
}

//Steps an object in direction axis
void Entity::StepAxis(int &axis, int &axisVel, Level level)
{
	axis += (axisVel >> 3);	//Use of shift operation fixes problems with dividing when -4 < Vel < 4
	
	for (int i = 0; i < level.numofplatforms; i++)
	{
		MoveBackIfColliding(axis, axisVel, level.platform[i]);
	}
	
	if (objnum != 0)	//Guard against doing collision detection between an object and itself
	{
		MoveBackIfColliding(axis, axisVel, level.player);
	}
	
	for (int i = 0; i < level.numofcubes; i++)
	{
		if (i + 1 != objnum)	//Same object guard
		{
			MoveBackIfColliding(axis, axisVel, level.cube[i]);
		}
	}
}

//Moves the entity backwards if the entity is colliding with another object
void Entity::MoveBackIfColliding(int &position, int &axisVel, Object obstacle)
{
	//If not colliding with any obstacle allow movement
	if (IsColliding(obstacle) && (axisVel < 0 || axisVel >= BITSHIFT))	
	{	
		do
		{
			position -= (PlusOrMinus(axisVel));		//Move the entity backwards by one pixel
		}
		while (IsColliding(obstacle));				//until it no longer collides
		
		//Only set velocity to stationary if entity has collided with an obstacle
		axisVel = STATIONARY;
	}
}

//Set velocities to terminal if they exceed them.
void Entity::ApplyTerminal()
{
	if (abs(xVel) > terminalx)
	{
		if (xVel > STATIONARY)
		{
			xVel = terminalx;
		}
		else
		{
			//Bit shift negative bias means character goes to the left quicker without offset. 
			xVel = -terminalx + (2 * BITSHIFT);
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
			yVel = -terminaly + (2 * BITSHIFT);
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