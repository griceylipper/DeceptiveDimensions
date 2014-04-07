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
	numofcubes = 2;
	
	//Default boundaries
	platform[0].Reset(0, 0, SCREEN_WIDTH, 8);
	platform[1].Reset(0, 0, 8, SCREEN_HEIGHT);
	platform[2].Reset(0, SCREEN_HEIGHT - 8, SCREEN_WIDTH, 8);
	platform[3].Reset(SCREEN_WIDTH - 8, 0, 8, SCREEN_HEIGHT);
	platform[4].Reset(112, 104, 16, 16);
	
	//Player
	player.Reset(116, 76, 8, 16, 0, 0, 4, 1, 0, 16, 16);	
	
	//Test cubes
	cube[0].Reset(16, 64, 8, 8, 0, 0, 4, 1, 1);
	cube[1].Reset(80, 72, 8, 8, 0, 0, 4, 1, 2);
}

//Draws level
void Level::Draw()
{
	FillScreenblock(30, 3);
	
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
	
	SetObject(player.GetObjNum(),
	  ATTR0_SHAPE(2) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(player.Gety()),
	  ATTR1_SIZE(0) | ATTR1_X(player.Getx()),
	  ATTR2_ID8(0));
	
	for (int i = 0; i < numofcubes; i++)
	{
		SetObject(cube[i].GetObjNum(),
		  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(cube[i].Gety()),
		  ATTR1_SIZE(0) | ATTR1_X(cube[i].Getx()),
		  ATTR2_ID8(0));
	}
}

//Steps all entities in level
void Level::MoveObjects(uint16_t curButtons, uint16_t prevButtons, Level level)
{
	player.ReadButtons(curButtons, prevButtons, level);
	player.ApplyGravity();
	player.ApplyVelocity(level);
	
	//Temporary box respawn stuff
	if (((curButtons & KEY_L) == 0) && ((prevButtons & KEY_L) != 0))
	{
		cube[0].Reset(16, 16, 8, 8, 0, 0, 4, 1, 1);
	}
	if (((curButtons & KEY_R) == 0) && ((prevButtons & KEY_R) != 0))
	{
		cube[1].Reset(16, 16, 8, 8, 0, 0, 4, 1, 2);
	}
	
	for (int i = 0; i < numofcubes; i++)
	{
		cube[i].ApplyGravity();
		cube[i].ApplyVelocity(level);
	}
}

void Level::FillScreenblock(int screenblock, int tile)
{
	for (int y = 0; y < 32; ++y)
	{
		for (int x = 0; x < 32; ++x)
		{
			SetTile(screenblock, x, y, tile);
		}
	}
}