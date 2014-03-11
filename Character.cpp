//Character.cpp

#include "Character.h"
#include "gba.h"

Character::Character(int a, int b, int w, int h, int xV, int yV, int g, int W, int o, int sx, int sy)
{
	Reset(a, b, w, h, xV, yV, g, W, o, sx, sy);
}

void Character::Reset(int a, int b, int w, int h, int xV, int yV, int g, int W, int o, int sx, int sy)
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
	
	terminalx = 30;
	terminaly = 160;
}

void Character::ApplyButtons(uint16_t curButtons, uint16_t prevButtons)
{
	//Sideways motion. Gives character slight slideyness.
	//Accelerating
	if ((curButtons & KEY_LEFT) == 0)
	{
		xVel -= 1;
	}
	else if ((curButtons & KEY_RIGHT) == 0)
	{
		xVel += 1;
	}
	//Decelerating
	else
	{
		if (xVel > 0)
		{
			xVel -= 1;
		}
		else if (xVel < 0)
		{
			xVel += 1;
		}
		else
		{
			xVel = 0;
		}
	}
	
	//Jumping
	if (((curButtons & KEY_A) == 0) && ((prevButtons & KEY_A) != 0))
	{
		Jump();
	}
	
	//Temporary gravity reversal - will be restricted to entities in future
	if (((curButtons & KEY_B) == 0) && ((prevButtons & KEY_B) != 0))
	{
		ReverseGravity();
	}
}

//Makes Character jump in direction opposite to gravity.
void Character::Jump()
{
	yVel = gravity * -10;
}