//Character.cpp

#include "Character.h"
#include "Level.h"

/**
Default constructor
*/
Character::Character()
{
	Reset(116, 76, 8, 16, 0, 0, 4, true, 0, 16, 16);
}
/**
Constructor which allows setting of all parameters at once.
*/
Character::Character(int a, int b, int w, int h, int xV, int yV, int g, bool H, int o, int sx,
					 int sy)
{
	Reset(a, b, w, h, xV, yV, g, H, o, sx, sy);
}

/**
Allows setting of all parameters at once
*/
void Character::Reset(int a, int b, int w, int h, int xV, int yV, int g, bool H, int o, int sx,
					  int sy)
{
	x = a;
	y = b;
	width = w;
	height = h;
	xVel = xV;
	yVel = yV;
	gravity = g;
	heavy = H;
	objnum = o;
	spawnx = sx;
	spawny = sy;
	
	onplatform = false;
	isholding = false;
	terminalx = 27;
	terminaly = 160;
	decel = 3;
	accel = 2;
	direction = RIGHT;
}

/**
Takes input from buttons to move character
*/
void Character::ReadButtons(Buttons &buttons, Level &level)
{
	//Sideways motion. Gives character slight slideyness.
	Movement(buttons);
	
	//Jumping
	if (buttons.AJustPressed())
	{
		Jump(level);
	}
	
	//Picking up / dropping things
	if (buttons.BJustPressed())
	{
		ManipulateCube(level);
	}
	
	//Throwing things
	if (buttons.RJustPressed())
	{
		ThrowCube(level);
	}
}

/**
Makes player pick up a cube if it is next to one, and drop a cube if it is holding one
*/
void Character::ManipulateCube(Level &level)
{
	if (isholding == false)
	{
		PickUp(level);
	}
	else
	{
		Drop(level);
		//If cube successfully dropped
		if (!isholding)
		{
			//End player's collision avoidance on cube just picked up
			cubeheld = level.MAXCUBES + 1;
		}
	}
}

/**
Picks up first cube adjacent to the character
*/
void Character::PickUp(Level &level)
{
	for (int i = 0; i < level.numofcubes; i++)
	{
		if (IsTouching(level.cube[i]))
		{
			isholding = true;
			cubeheld = i;
			level.cube[i].isheld = true;
			//Make player taller when carrying cube
			height += level.cube[i].GetHeight();
			//Move player up so that added height doesn't reach into the floor
			y -= level.cube[i].GetHeight();
			break;
		}
	}
}

/**
Drops cube being held by character
*/
void Character::Drop(Level &level)
{
	//Move cube to drop position
	if (direction == LEFT)
	{
		level.cube[cubeheld].Move(x - width, level.cube[cubeheld].Gety());
	}
	else
	{
		level.cube[cubeheld].Move(x + width, level.cube[cubeheld].Gety());
	}
	
	//If cube is not colliding with anything in level
	if (level.cube[cubeheld].IsCollidingLevel(level) == false)
	{
		//Let go of cube
		isholding = false;
		level.cube[cubeheld].isheld = false;
		height -= level.cube[cubeheld].GetHeight();
		y += level.cube[cubeheld].GetHeight();
		//Stops player immediately running underneath a cube just placed
		//xVel = STATIONARY;
		xVel = 0;
	}
	//Move back if colliding
	else
	{
		if (direction == LEFT)
		{
			level.cube[cubeheld].Move(x + width, level.cube[cubeheld].Gety());
		}
		else
		{
			level.cube[cubeheld].Move(x - width, level.cube[cubeheld].Gety());
		}
	}
}

/**
Throws cube held by character in direction currently facing
*/
void Character::ThrowCube(Level &level)
{
	if (isholding)
	{
		Drop(level);
		
		//If cube successfully thrown
		if (!isholding)
		{
			level.cube[cubeheld].GetThrown(level.player);
			//End player's collision avoidance on cube that was picked up
			cubeheld = level.MAXCUBES + 1;
		}
	}
}

/**
Takes input from buttons to move character
*/
void Character::Movement(Buttons &buttons)
{
	//Accelerating
	if (buttons.LeftIsHeld())
	{
		xVel -= accel;
		direction = LEFT;
	}
	else if (buttons.RightIsHeld())
	{
		xVel += accel;
		direction = RIGHT;
	}
	//Decelerating
	else
	{
		ApplyResistance();
	}
}

/**
Makes character jump in direction opposite to gravity.
*/
void Character::Jump(Level &level)
{
	onplatform = false;
	for (int i = 0; i < level.numofplatforms; i++)
	{
		if (IsAbove(level.platform[i]))
		{
			onplatform = true;
			break;
		}
	}
	if (!onplatform)
	{
		for (int i = 0; i < level.numofcubes; i++)
		{
			//Avoid checking if it is above a cube it is holding
			//(Without guard player is "above" cube because of height changes made to character)
			if (i == cubeheld)
			{
				continue;
			}
			if (IsAbove(level.cube[i]))
			{
				onplatform = true;
				break;
			}
		}
	}
	
	if (onplatform)
	{
		yVel = -44;
	}
}

/**
Make sure that the character stays on screen.
*/
void Character::CheckOnScreen()
{
	if (x < 0)
	{
		x = 0;
		xVel = 0;
	}
	
	if (GetRight() > SCREEN_WIDTH)
	{
		x = SCREEN_WIDTH - width;
		xVel = 0;
	}
	
	if (y < 0)
	{
		y = 0;
		yVel = 0;
	}
	
	if (GetBottom() > SCREEN_HEIGHT)
	{
		y = SCREEN_HEIGHT - height;
		yVel = 0;
	}
}

/**
Teleports character to spawn location
*/
void Character::Spawn()
{
	Move(spawnx, spawny);
	xVel = 0;
	yVel = 0;
}