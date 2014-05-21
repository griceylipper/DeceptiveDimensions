//Character.cpp

#include "Character.h"
#include "Level.h"

/**
Default constructor
*/
Character::Character()
{
	Reset(116, 76, 16, 32, 0, 0, 4, true, 0, 16, 16);
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
	terminaly = 64;
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
		TryJumping(level);
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
	
	if (buttons.UpJustPressed() && IsColliding(level.doorswitch.door)
		&& level.doorswitch.doorcuropen)
	{
		level.levelcomplete = true;
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
		if (IsTouching(level.cube[i]) && level.curdimension != HEAVY)
		{
			int cubeprevx = level.cube[i].Getx();
			int cubeprevy = level.cube[i].Gety();
			level.cube[i].Move(x, y - level.cube[i].GetHeight());
			if (!level.cube[i].IsCollidingLevel(level))
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
			else
			{
				level.cube[i].Move(cubeprevx, cubeprevy);
			}
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
void Character::TryJumping(Level &level)
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
	
	//Jump
	if (onplatform)
	{
		yVel = -40;
	}
}

/**
Returns true if character is standing on a cube.
*/
void Character::CheckIfOnMovingPlatform(Level &level)
{
	isoncube = false;
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
			isoncube = true;
			oncubenum = i;
			oncubex = level.cube[i].Getx();
			oncubey = level.cube[i].Gety();
			break;
		}
	}
}

/**
Moves player by amount that moving platform moves.
*/
void Character::MoveWithCube(Entity &movingplatform)
{
	//Calculate how far platform has moved after stepping
	int deltax = movingplatform.Getx() - oncubex;
	int deltay = movingplatform.Gety() - oncubey;
	
	//Move player by that amount
	x += deltax;
	y += deltay;
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