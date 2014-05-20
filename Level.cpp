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
	numofplatforms = 13;
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
	platform[8].Reset(16, 432, 16, 16);
	platform[9].Reset(32, 472, 16, 16);
	platform[10].Reset(48, 128, width - 48, 8);
	platform[11].Reset(16, 176, 16, 16);
	platform[12].Reset(32, 216, 16, 16);
	
	//Player
	player.Reset(116, 76, 8, 16, 0, 0, 4, 1, 0, 16, 16);
	
	//Test cubes
	cube[0].Reset(16, 64, 8, 8, 0, 0, 4, true, 1);
	cube[1].Reset(24, 72, 8, 8, 0, 0, 4, true, 2);
	cube[2].Reset(32, 80, 8, 8, 0, 0, 4, true, 3);
	cube[3].Reset(40, 88, 8, 8, 0, 0, 4, true, 4);
	
	//Door/Switch placement
	doorswitch.door.Reset(width - 32, height - 24, 16, 16);
	doorswitch.pressureplate.Reset(width - 48, height - 8, 16, 16);
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
		
		for (int i = 0; i < numofcubes; i++)
		{
			cube[i].ApplyVelocity(*this);
		}
	}
	
	doorswitch.CheckPressurePlate(*this);
	
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
	prevdimension = curdimension;
	
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
	
	if (doorswitch.doorcuropen)
	{
		SetTile(28, (doorswitch.door.Getx() / 8) - 32, (doorswitch.door.Gety() / 8) - 32, 74);
		SetTile(28, (doorswitch.door.Getx() / 8) -31, (doorswitch.door.Gety() / 8) - 32, 74);
	}
	else
	{
		SetTile(28, (doorswitch.door.Getx() / 8) - 32, (doorswitch.door.Gety() / 8) - 32, 0);
		SetTile(28, (doorswitch.door.Getx() / 8) -31, (doorswitch.door.Gety() / 8) - 32, 0);
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
	int wallpapertiles[4];
	
	if (curdimension == NORMAL)
	{
		wallpapertiles[0] = 4;
		wallpapertiles[1] = 5;
		wallpapertiles[2] = 20;
		wallpapertiles[3] = 21;
	}
	else if (curdimension == FLUFFY)
	{
		wallpapertiles[0] = 8;
		wallpapertiles[1] = 8;
		wallpapertiles[2] = 8;
		wallpapertiles[3] = 8;
	}
	else
	{
		wallpapertiles[0] = 6;
		wallpapertiles[1] = 7;
		wallpapertiles[2] = 22;
		wallpapertiles[3] = 23;
	}
	
	//Wallpaper
	for (int y = 0; y < 64; y += 2)
	{
		for (int x = 0; x < 64; x += 2)
		{
			// SetTileInCorrectScreenblock(x, y, wallpapertiles[0]);
			// SetTileInCorrectScreenblock(x + 1, y, wallpapertiles[1]);
			// SetTileInCorrectScreenblock(x, y + 1, wallpapertiles[2]);
			// SetTileInCorrectScreenblock(x + 1, y + 1, wallpapertiles[3]);
			SetTileInCorrectScreenblock(25, x, y, wallpapertiles[0]);
			SetTileInCorrectScreenblock(25, x + 1, y, wallpapertiles[1]);
			SetTileInCorrectScreenblock(25, x, y + 1, wallpapertiles[2]);
			SetTileInCorrectScreenblock(25, x + 1, y + 1, wallpapertiles[3]);
		}
	}
	
	//Platforms
	for (int i = 0; i < numofplatforms; i++)
	{
		for (int y = platform[i].Gety() / 8; y < platform[i].GetBottom() / 8; y++)
		{
			for (int x = platform[i].Getx() / 8; x < platform[i].GetRight() / 8; x++)
			{
				SetTileInCorrectScreenblock(25, x, y, 103);
			}
		}
	}
	
	//Switch
	for (int y = doorswitch.pressureplate.Gety() / 8;
		y < doorswitch.pressureplate.GetBottom() / 8; y++)
	{
		for (int x = doorswitch.pressureplate.Getx() / 8;
			x < doorswitch.pressureplate.GetRight() / 8; x++)
		{
			SetTile(28, x - 32, y - 32, 3);
		}
	}
}

/**
Sets a tile tilenumber at position (x, y) in the correct screenblock.
*/
void Level::SetTileInCorrectScreenblock(int startingscreenblock, int x, int y, int tilenumber)
{
	if (x < 32)
	{
		if (y < 32)
		{
			SetTile(startingscreenblock, x, y, tilenumber);
		}
		else
		{
			SetTile(startingscreenblock + 2, x, y - 32, tilenumber);
		}
	}
	else
	{
		if (y < 32)
		{
			SetTile(startingscreenblock + 1, x - 32, y, tilenumber);
		}
		else
		{
			SetTile(startingscreenblock + 3, x - 32, y - 32, tilenumber);
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
	REG_BG2VOFS = backgroundoffsety;
	
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
		  ATTR2_ID8(3) | ATTR2_PRIO(2));
	}
	
	UpdateObjects();
}

/**
Calculate the offsets of screen based on where the player is in the level and what it's holding
*/
void Level::DetermineBackgroundOffsets()
{
	//Background x offset
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
	
	//Background y offset
	int holdingcubeoffset = 0;		//Offset compensating for player height change when holding item
	if (player.isholding)
	{
		holdingcubeoffset = cube[player.cubeheld].GetHeight();
	}
	
	if (player.Gety() + holdingcubeoffset < SCREEN_HEIGHT / 2)
	{
		backgroundoffsety = 0;
	}
	else if (player.Gety() + holdingcubeoffset > height - (SCREEN_HEIGHT / 2))
	{
		backgroundoffsety = height - SCREEN_HEIGHT;	
	}
	else
	{
		backgroundoffsety = -((SCREEN_HEIGHT / 2) - player.Gety()) + holdingcubeoffset;
	}
}

/**
Determines the offsets that keep the player in the middle of the screen
*/
void Level::ApplyEntityOffsets()
{
	//Player offsets
	player.drawx = player.Getx() - backgroundoffsetx;	
	player.drawy = player.Gety() - backgroundoffsety;
	
	//Cube offsets
	for (int i = 0; i < numofcubes; i++)
	{
		cube[i].SetScreenPosition(*this);
	}
}

/**
Fills screenblock with a single tile.
*/
void Level::FillScreenblock(int screenblock, int tile)
{
	for (int y = 0; y < 32; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			SetTile(screenblock, x, y, tile);
		}
	}
}