//Character.cpp

#include "Character.h"
#include "Level.h"

Character::Character()
{
	Reset(116, 76, 8, 16, 0, 0, 4, 1, 0, 16, 16);
}

Character::Character(int a, int b, int w, int h, int xV, int yV, int g, int W, int o, int sx,
					 int sy)
{
	Reset(a, b, w, h, xV, yV, g, W, o, sx, sy);
}

void Character::Reset(int a, int b, int w, int h, int xV, int yV, int g, int W, int o, int sx,
					  int sy)
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
	spawnx = sx;
	spawny = sy;
	
	onplatform = false;
	terminalx = 30;
	terminaly = 160;
	accel = 2;
	decel = 3;
}

void Character::ReadButtons(uint16_t curButtons, uint16_t prevButtons, Level level)
{
	//Sideways motion. Gives character slight slideyness.
	//Accelerating
	if ((curButtons & KEY_LEFT) == 0)
	{
		xVel -= accel;
	}
	else if ((curButtons & KEY_RIGHT) == 0)
	{
		xVel += accel;
	}
	//Decelerating
	else
	{
		if (xVel > STATIONARY)
		{
			xVel -= decel;
		}
		else if (xVel < STATIONARY)
		{
			xVel += decel;
		}
		else
		{
			xVel = STATIONARY;
		}
	}
	
	//Jumping
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
			if (IsAbove(level.cube[i]))
			{
				onplatform = true;
				break;
			}
		}
	}
	
	if (((curButtons & KEY_A) == 0) && ((prevButtons & KEY_A) != 0) && (yVel >= 0) && (yVel < 8)
		  && onplatform)
	{
		Jump();
	}
	
	//Temporary spawning
	if (((curButtons & KEY_B) == 0) && ((prevButtons & KEY_B) != 0))
	{
		Spawn();
	}
}

//Makes Character jump in direction opposite to gravity.
void Character::Jump()
{
	yVel = gravity * -10;
}

//Make sure that character stays on screen.
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

//Teleports character to spawn location
void Character::Spawn()
{
	Move(spawnx, spawny);
	xVel = 0;
	yVel = 0;
}