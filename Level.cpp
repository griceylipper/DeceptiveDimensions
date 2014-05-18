//Level.cpp

#include "Level.h"

/**
Constructor
*/
Level::Level()
{
	x = 0;
	y = 0;
	width = 512;
	height = 512;
	numofplatforms = 8;
	numofcubes = 4;
	paused = false;
	indimensionsmenu = false;
	curdimension = NORMAL;
	
	//Default boundaries
	platform[0].Reset(0, 0, width, 8);
	platform[1].Reset(0, 0, 8, height);
	platform[2].Reset(0, height - 8, width, 8);
	platform[3].Reset(width - 8, 0, 8, height);
	platform[4].Reset(48, 256, width - 48, 8);
	platform[5].Reset(16, 304, 16, 16);
	platform[6].Reset(32, 344, 16, 16);
	platform[7].Reset(48, 384, width - 48, 8);
	
	//Player
	player.Reset(116, 76, 8, 16, 0, 0, 4, 1, 0, 16, 16);
	
	//Test cubes
	cube[0].Reset(16, 64, 8, 8, 0, 0, 4, true, 1);
	cube[1].Reset(24, 72, 8, 8, 0, 0, 4, true, 2);
	cube[2].Reset(32, 80, 8, 8, 0, 0, 4, true, 3);
	cube[3].Reset(40, 88, 8, 8, 0, 0, 4, true, 4);
}

/**
Steps all entities in level
*/
void Level::MoveObjects(Buttons &buttons)
{
	if (buttons.LIsHeld() && !paused)
	{
		indimensionsmenu = true;
	}
	else
	{
		indimensionsmenu = false;
	}
	
	if (buttons.StartJustPressed() && !buttons.LIsHeld())
	{
		paused = !paused;
	}	
	
	if (!paused && !indimensionsmenu)
	{
		player.ReadButtons(buttons, *this);
		player.ApplyVelocity(*this);
		//player.CheckOnScreen();
		
		for (int i = 0; i < numofcubes; i++)
		{
			cube[i].ApplyVelocity(*this);
		}
	}
	
	if (indimensionsmenu)
	{
		DimensionMenuControl(buttons);
	}
}

/**
Deals with button presses in dimensions menu
*/
void Level::DimensionMenuControl(Buttons &buttons)
{
	if (buttons.UpJustPressed())
	{
		if (curdimension == NORMAL)
		{
			curdimension = FLUFFY;
		}
		else if (curdimension == HEAVY)
		{
			curdimension = NORMAL;
		}
	}
	else if (buttons.DownJustPressed())
	{
		if (curdimension == NORMAL)
		{
			curdimension = HEAVY;
		}
		else if (curdimension == FLUFFY)
		{
			curdimension = NORMAL;
		}
	}
	prevdimension = curdimension;
}

/**
Draws background of level
*/
void Level::Draw()
{	
	if (curdimension != prevdimension)
	{
		DrawBackground(curdimension);
	}
	
	//Clear dimensions menu and cursor
	for (int screenblock = 29; screenblock < 31; screenblock++)
	{
		SetTile(screenblock, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16, 0);			//Normal icon space
		SetTile(screenblock, SCREEN_WIDTH / 16, (SCREEN_HEIGHT / 16) - 1, 0);	//Fluffy icon space
		SetTile(screenblock, SCREEN_WIDTH / 16, (SCREEN_HEIGHT / 16) + 1, 0);	//Heavy icon space
	}
	
	if (indimensionsmenu)
	{
		SetTile(29, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16, 4);			//Normal icon
		SetTile(29, SCREEN_WIDTH / 16, (SCREEN_HEIGHT / 16) - 1, 8);	//Fluffy icon
		SetTile(29, SCREEN_WIDTH / 16, (SCREEN_HEIGHT / 16) + 1, 22);	//Heavy icon
		
		//Cursor
		if (curdimension == NORMAL)
		{
			SetTile(30, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16, 74);
		}
		else if (curdimension == FLUFFY)
		{
			SetTile(30, SCREEN_WIDTH / 16, (SCREEN_HEIGHT / 16) - 1, 74);
		}
		else
		{
			SetTile(30, SCREEN_WIDTH / 16, (SCREEN_HEIGHT / 16) + 1, 74);
		}
	}
}

/**
Draws the background of the level;
*/
void Level::DrawBackground(dimension curdimension)
{
	//Wallpaper
	for (int y = 0; y < 32; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			SetTile(24, x, y, 4);
		}
	}
	
	//Platforms
	for (int i = 0; i < numofplatforms; i++)
	{
		for (int y = platform[i].Gety() / 8 ; y < platform[i].GetBottom() / 8; y++)
		{
			for (int x = platform[i].Getx() / 8; x < platform[i].GetRight() / 8; x++)
			{
				if (x < 32)
				{
					if (y < 32)
					{
						SetTile(25, x, y, 103);
					}
					else
					{
						SetTile(27, x, y - 32, 103);
					}
				}
				else
				{
					if (y < 32)
					{
						SetTile(26, x - 32, y, 103);
					}
					else
					{
						SetTile(28, x - 32, y - 32, 103);
					}
				}
			}
		}
	}
}

/**
Updates all gba objects in Level
*/
void Level::UpdateLevelObjects()
{
	DetermineBackgroundOffsets();
	ApplyEntityOffsets();
	
	REG_BG2HOFS = backgroundoffsetx;
	REG_BG3HOFS = backgroundoffsetx / 2;	
	REG_BG2VOFS = backgroundoffsety;
	REG_BG3VOFS = backgroundoffsety / 2;
	
	uint16_t facing = 0;
	
	if (player.direction == player.LEFT)
	{
		facing = ATTR1_HFLIP;
	}
	
	if (player.isholding)
	{
		//Allows for height change when carrying cubes on the head
		SetObject(player.GetObjNum(),
		  ATTR0_SHAPE(2) | ATTR0_8BPP | ATTR0_REG
		    | ATTR0_Y(player.drawy + cube[player.cubeheld].GetHeight()),	
		  ATTR1_SIZE(0) | ATTR1_X(player.drawx) | facing,
		  ATTR2_ID8(0) | ATTR2_PRIO(2));
	}
	else
	{
		SetObject(player.GetObjNum(),
		  ATTR0_SHAPE(2) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(player.drawy),
		  ATTR1_SIZE(0) | ATTR1_X(player.drawx) | facing,
		  ATTR2_ID8(0) | ATTR2_PRIO(2));
	}
	
	//Draw cubes
	for (int i = 0; i < numofcubes; i++)
	{
		SetObject(cube[i].GetObjNum(),
		  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(cube[i].drawy),
		  ATTR1_SIZE(0) | ATTR1_X(cube[i].drawx),
		  ATTR2_ID8(0) | ATTR2_PRIO(2));
	}
}

/**
Calculate the offsets of screen based on where the player is in the level
*/
void Level::DetermineBackgroundOffsets()
{
	if (player.Getx() < SCREEN_WIDTH / 2)
	{
		backgroundoffsetx = 0;
	}
	else if (player.Getx() > width - (SCREEN_WIDTH / 2))
	{
		backgroundoffsetx = width - SCREEN_WIDTH;	
	}
	else
	{
		backgroundoffsetx = -((SCREEN_WIDTH / 2) - player.Getx());
	}
	
	if (player.Gety() < SCREEN_HEIGHT / 2)
	{
		backgroundoffsety = 0;
	}
	else if (player.Gety() > height - (SCREEN_HEIGHT / 2))
	{
		backgroundoffsety = height - SCREEN_HEIGHT;	
	}
	else
	{
		backgroundoffsety = -((SCREEN_HEIGHT / 2) - player.Gety());
	}
}

/**
Determines the offsets that keep the player in the middle of the screen
*/
void Level::ApplyEntityOffsets()
{
	//Player offsets
	if (player.Getx() <= SCREEN_WIDTH / 2)
	{
		player.drawx = player.Getx();
	}
	else if ((player.Getx() > SCREEN_WIDTH / 2) && (player.Getx() < width - SCREEN_WIDTH / 2))
	{
		player.drawx = SCREEN_WIDTH / 2;
	}
	else
	{
		player.drawx = player.Getx() - width + SCREEN_WIDTH;
	}
	
	if (player.Gety() <= SCREEN_HEIGHT / 2)
	{
		player.drawy = player.Gety();
	}
	else if ((player.Gety() > SCREEN_HEIGHT / 2) && (player.Gety() < height - SCREEN_HEIGHT / 2))
	{
		player.drawy = SCREEN_HEIGHT / 2;
	}
	else
	{
		player.drawy = player.Gety() - height + SCREEN_HEIGHT;
	}

	//Cube offsets
	for (int i = 0; i < numofcubes; i++)
	{
		cube[i].SetScreenPosition(backgroundoffsetx, backgroundoffsety);
	}
}

/**
Fills screenblock with a single tile.
*/
void Level::FillScreenblock(int screenblock, int screenblocksize, int tile)
{
	for (int y = 0; y < screenblocksize; y++)
	{
		for (int x = 0; x < screenblocksize; x++)
		{
			SetTile(screenblock, x, y, tile);
		}
	}
}