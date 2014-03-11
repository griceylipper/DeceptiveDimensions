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
	accel = 2;
	decel = 3;
}

void Character::ReadButtons(uint16_t curButtons, uint16_t prevButtons)
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
		if (xVel > 0)
		{
			xVel -= decel;
		}
		else if (xVel < 0)
		{
			xVel += decel;
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