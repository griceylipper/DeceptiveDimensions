//Level.cpp

#include "Level.h"

//Constructor
Level::Level()
{
	x = 0;
	y = 0;
	width = 256;
	height = 256;
	numofplatforms = 5;
	numofcubes = 3;
	
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
	cube[1].Reset(24, 72, 8, 8, 0, 0, 4, 1, 2);
	cube[2].Reset(32, 80, 8, 8, 0, 0, 4, 1, 3);
	
	for (int i = 0; i < numofcubes; i++)
	{
		SetObject(cube[i].GetObjNum(),
		  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(cube[i].Gety()),
		  ATTR1_SIZE(0) | ATTR1_X(cube[i].Getx()),
		  ATTR2_ID8(0));
	}
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
}

void Level::UpdateObjects()
{	
	if (player.isholding)
	{
		//Allows for height change when carrying cubes on the head
		SetObject(player.GetObjNum(),
		  ATTR0_SHAPE(2) | ATTR0_8BPP | ATTR0_REG
		    | ATTR0_Y(player.Gety() + cube[player.cubeheld].GetHeight()),	
		  ATTR1_SIZE(0) | ATTR1_X(player.Getx()),
		  ATTR2_ID8(0));
	}
	else
	{
		SetObject(player.GetObjNum(),
		  ATTR0_SHAPE(2) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(player.Gety()),
		  ATTR1_SIZE(0) | ATTR1_X(player.Getx()),
		  ATTR2_ID8(0));	
	}
	for (int i = 0; i < numofcubes; i++)
	{
		SetObjectX(cube[i].GetObjNum(), cube[i].Getx());
		SetObjectY(cube[i].GetObjNum(), cube[i].Gety());
	}
}

//Steps all entities in level
void Level::MoveObjects(Buttons &buttons)
{
	player.ReadButtons(buttons, *this);
	player.ApplyVelocity(*this);
	player.CheckOnScreen();
	
	//Temporary box respawn stuff
	if (buttons.LJustPressed())
	{
		cube[0].Reset(16, 8, 8, 8, 0, 0, 4, 1, 1);
	}
	if (buttons.RJustPressed())
	{
		cube[1].Reset(16, 16, 8, 8, 0, 0, 4, 1, 2);
	}
	
	for (int i = 0; i < numofcubes; i++)
	{
		cube[i].ApplyVelocity(*this);
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