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
	numofplatforms = 5;
	numofcubes = 4;
	paused = false;
	indimensionsmenu = false;
	curdimension = NORMAL;
	
	//Default boundaries
	platform[0].Reset(0, 0, width, 8);
	platform[1].Reset(0, 0, 8, height);
	platform[2].Reset(0, height - 8, width, 8);
	platform[3].Reset(width - 8, 0, 8, height);
	platform[4].Reset(112, 104, 16, 16);
	
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
Draws background of level
*/
void Level::Draw()
{
	//Level/screen offset.
	if (player.Getx() < SCREEN_WIDTH / 2)
	{
		BackgroundOffsetx = 0;
	}
	else if (player.Getx() > width - (SCREEN_WIDTH / 2))
	{
		BackgroundOffsetx = width - SCREEN_WIDTH;	
	}
	else
	{
		BackgroundOffsetx = -((SCREEN_WIDTH / 2) - player.Getx());
	}
	
	if (player.Gety() < SCREEN_HEIGHT / 2)
	{
		BackgroundOffsety = 0;
	}
	else if (player.Gety() > height - (SCREEN_HEIGHT / 2))
	{
		BackgroundOffsety = height - SCREEN_HEIGHT;	
	}
	else
	{
		BackgroundOffsety = -((SCREEN_HEIGHT / 2) - player.Gety());
	}

	REG_BG2HOFS = BackgroundOffsetx;
	REG_BG3HOFS = BackgroundOffsetx / 2;	
	REG_BG2VOFS = BackgroundOffsety;
	REG_BG3VOFS = BackgroundOffsety / 2;
	
	if (curdimension != prevdimension)
	{
		DrawBackground(curdimension);
	}
	
	//Clear dimensions menu
	SetTile(29, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16, 0);			//Normal icon space
	SetTile(29, SCREEN_WIDTH / 16, (SCREEN_HEIGHT / 16) - 1, 0);	//Fluffy icon space
	SetTile(29, SCREEN_WIDTH / 16, (SCREEN_HEIGHT / 16) + 1, 0);	//Heavy icon space
	//Clear icon layer
	SetTile(30, SCREEN_WIDTH / 16, SCREEN_HEIGHT / 16, 0);			//Normal icon
	SetTile(30, SCREEN_WIDTH / 16, (SCREEN_HEIGHT / 16) - 1, 0);	//Fluffy icon
	SetTile(30, SCREEN_WIDTH / 16, (SCREEN_HEIGHT / 16) + 1, 0);	//Heavy icon
	
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
Updates all gba objects in Level
*/
void Level::UpdateObjects()
{
	uint16_t facing = 0;
	if (player.direction == player.LEFT)
	{
		facing = ATTR1_HFLIP;
	}
	
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
	for (int i = 0; i < numofcubes; i++)
	{
		SetObject(cube[i].GetObjNum(),
		  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | cube[i].visible
			| ATTR0_Y(CubeScreenyPosition(cube[i], BackgroundOffsety)),
		  ATTR1_SIZE(0) | ATTR1_X(CubeScreenxPosition(cube[i], BackgroundOffsetx)),
		  ATTR2_ID8(0) | ATTR2_PRIO(2));
	}
}

//REORGANIZE THIS INTO ENTITY
int Level::CubeScreenxPosition(Entity &cube, int BackgroundOffsetx)
{
	if (cube.Getx() - BackgroundOffsetx < cube.GetWidth())
	{
		return (cube.Getx() - BackgroundOffsetx + 512);
	}
	else
	{
		return (cube.Getx() - BackgroundOffsetx);
	}
}

int Level::CubeScreenyPosition(Entity &cube, int BackgroundOffsety)
{
	int newposition;
	
	if (cube.Gety() - BackgroundOffsety < cube.GetHeight())
	{
		newposition = (cube.Gety() - BackgroundOffsety + 256);
	}
	else
	{
		newposition = (cube.Gety() - BackgroundOffsety);
	}
	
	//************* GET WORKING *********************
	if (newposition > SCREEN_HEIGHT)
	{
		cube.visible = ATTR0_HIDE;
	}
	else
	{
		cube.visible = 0;
	}
	return newposition;
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
			//for (int screenblock = 25; screenblock < 29; screenblock++)
			//{
				//SetTile(screenblock, x, y, 4);
			//}
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