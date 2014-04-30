//Entity.cpp

#include "Level.h"
#include "Character.h"
#include "Entity.h"
#include <cstdlib>

//Default constructor
Entity::Entity()
{
	x = 0;
	y = 0;
	width = 8;
	height = 8;
	//xVel = STATIONARY;
	xVel = 0;
	//yVel = STATIONARY;
	yVel = 0;
	gravity = 10;
	weight = 1; 
	objnum = 9; 
	terminalx = 30;
	terminaly = 128;
	isheld = false;
	decel = 1;  
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
	terminaly = 128;
	isheld = false;
	decel = 1;
}

//Returns true if entity is colliding with any other object in Level level
bool Entity::IsCollidingLevel(const Level &level)
{
	for (int i = 0; i < level.numofplatforms; i++)
	{
		if (IsColliding(level.platform[i]))
		{
			return true;
		}
	}
	
	if (objnum != 0)	//Guard against doing collision detection between player object and itself
	{
		if (IsColliding(level.player))
		{
			return true;
		}
	}
	
	for (int i = 0; i < level.numofcubes; i++)
	{
		if ((objnum != i + 1) && i != level.player.cubeheld)	//Same object guard for cubes
		{
			if (IsColliding(level.cube[i]))
			{
				return true;
			}
		}
	}
	
	return false;
}

//Applies resistance to entities in the x-axis
void Entity::ApplyResistance()
{
	//if (xVel > STATIONARY)
	if (xVel > 0)
	{
		xVel -= decel;
	}
	//else if (xVel < STATIONARY)
	else if (xVel < 0)
	{
		xVel += decel;
	}
}

//Applies the acceleration of gravity to the objects current velocity
void Entity::ApplyGravity()
{
	yVel += gravity * 0.5;	//Higher multiplier = higher gravity; lowest practical value = 0.25
}

//Applies the velocities of objects to their positions
void Entity::ApplyVelocity(Level &level)
{
	if (isheld)
	{
		Move(level.player.Getx(), level.player.Gety());
		//xVel = STATIONARY;
		xVel = 0;
		//yVel = STATIONARY;
		yVel = 0;
	}
	else
	{
		if (objnum != 0)
		{
			ApplyResistance();
		}
		ApplyGravity();
		ApplyTerminal();
		StepAxis(x, xVel, level);
		StepAxis(y, yVel, level);
	}
}

//Steps an entity in direction axis
void Entity::StepAxis(int &axis, int &axisVel, const Level &level)
{
	//Using bit shift operations instead of division fixes continuity problems when axisVel is 
	//around zero. Adding four offsets the way numbers are always bit shifted towards -ve infinity.
	axis += ((axisVel + 4) >> 3);
	
	for (int i = 0; i < level.numofplatforms; i++)
	{
		MoveBackIfColliding(axis, axisVel, level.platform[i]);
	}
	
	if (objnum != 0)	//Guard against doing collision detection between player object and itself
	{
		MoveBackIfColliding(axis, axisVel, level.player);
	}
	
	for (int i = 0; i < level.numofcubes; i++)
	{
		if ((objnum != i + 1) && i != level.player.cubeheld)	//Same object guard for cubes
		{
			MoveBackIfColliding(axis, axisVel, level.cube[i]);
		}
	}
}

//Moves the entity backwards if the entity is colliding with another object
void Entity::MoveBackIfColliding(int &position, int &axisVel, const Object &obstacle)
{
	//If not colliding with any obstacle allow movement
	//if (IsColliding(obstacle) && (axisVel < 0 || axisVel >= BITSHIFT))
	if (IsColliding(obstacle) && (axisVel < -4 || axisVel >= 4))
	{	
		do
		{
			position -= (PlusOrMinus(axisVel));		//Move the entity backwards by one pixel
		}
		while (IsColliding(obstacle));				//until it no longer collides
		
		//Only set velocity to stationary if entity has collided with an obstacle
		//axisVel = STATIONARY;
		axisVel = 0;
	}
}

//Set velocities to terminal if they exceed them.
void Entity::ApplyTerminal()
{
	if (abs(xVel) > terminalx)
	{
		//if (xVel > STATIONARY)
		if (xVel > 0)
		{
			xVel = terminalx;
		}
		else
		{
			//Bit shift negative bias means character goes to the left quicker without offset. 
			//xVel = -terminalx + (2 * BITSHIFT);
			xVel = -terminalx;
		}
	}
	if (abs(yVel) > terminaly)
	{
		//if (yVel > STATIONARY)
		if (yVel > 0)
		{
			yVel = terminaly;
		}
		else
		{
			//yVel = -terminaly + (2 * BITSHIFT);
			yVel = -terminaly;
		}
	}
}

//Throws entity in direction direction
void Entity::GetThrown(const Character &player)
{
	if (player.direction == player.RIGHT)
	{
		xVel = 30;
	}
	else
	{
		//xVel = -30 + BITSHIFT;
		xVel = -30;
	}
	yVel = gravity * -4;
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