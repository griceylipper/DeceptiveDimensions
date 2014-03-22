//Level.cpp

#include "Level.h"
#include "gba.h"

//Constructor
Level::Level()
{
	x = 0;
	y = 0;
	width = 256;
	height = 256;
	numofplatforms = 5;
	
	//Default boundaries
	platform[0].Reset(0, 0, SCREEN_WIDTH, 8);
	platform[1].Reset(0, 0, 8, SCREEN_HEIGHT);
	platform[2].Reset(0, SCREEN_HEIGHT - 8, SCREEN_WIDTH, 8);
	platform[3].Reset(SCREEN_WIDTH - 8, 0, 8, SCREEN_HEIGHT);
	platform[4].Reset(112, 104, 16, 16);
}

void Level::Draw()
{
	for (int i = 0; i < numofplatforms; i++)
	{
		for (int y = platform[i].Gety() / 8 ; y < platform[i].GetBottom() / 8; y ++)
		{
			for (int x = platform[i].Getx() / 8; x < platform[i].GetRight() / 8; x ++)
			{
				SetTile(30, x, y, 0);
			}
		}
	}
}