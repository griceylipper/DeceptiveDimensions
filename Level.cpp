//Level.cpp

#include "Level.h"

/**
Constructor
*/
Level::Level(int inputlevel)
{
	x = 0;
	y = 0;
	width = 512;
	height = 512;
	levelnumber = inputlevel;
	levelcomplete = false;
	curdimension = NORMAL;
	prevdimension = NORMAL;
	
	numofplatforms = 10;
	
	//Default boundaries
	platform[0].Reset(0, 0, width, 16);
	platform[1].Reset(0, 0, 16, height);
	platform[2].Reset(0, height - 16, width, 16);
	platform[3].Reset(width - 16, 0, 16, height);
	
	platform[4].Reset(0, 352, width, 16);
	platform[5].Reset(0, 176, width, 16);
	platform[6].Reset(432, 144, 16, 16);
	platform[7].Reset(208, 464, 64, 16);
	
	numofcubes = 3;
	
	cube[0].Reset(432, 160, 16, 16, 0, 0, 4, true, 1);
	
	player.Reset(48, 464, 16, 32, 0, 0, 4, true, 0, 16, 16);
	
	doorswitch.door.Reset(448, 464, 16, 32);
	doorswitch.pressureplate.Reset(432, 176, 16, 8);
}

/**
Switches level if it is complete. Return value signals endgame in main
*/
bool Level::CheckIfLevelComplete()
{
	if (levelcomplete)
	{
		levelnumber++;
		
		prevdimension = NORMAL;
		curdimension = NORMAL;
		paused = false;
		indimensionsmenu = false;
		
		for (int i = 0; i < numofplatforms; i++)
		{
			platform[i].Reset(0, 0, 16, 16);
		}
		//Place cubes above level boundary when not in use
		for (int i = 0; i < numofcubes + 1; i++)
		{
			cube[i].Reset(16 * i, -16, 16, 16, 0, 0, 4, true, i + 1);
		}
		
		//Default boundaries
		platform[0].Reset(0, 0, width, 16);
		platform[1].Reset(0, 0, 16, height);
		platform[2].Reset(0, height - 16, width, 16);
		platform[3].Reset(width - 16, 0, 16, height);
		
		if (levelnumber == 2)
		{
			platform[4].Reset(0, 352, width, 16);
			
			cube[0].Reset(416, 464, 16, 16, 0, 0, 4, true, 1);
			
			player.Reset(48, 464, 16, 32, 0, 0, 4, true, 0, 16, 16);
			
			doorswitch.door.Reset(448, 464, 16, 32);
			doorswitch.pressureplate.Reset(352, 496, 16, 8);
		}
		else if (levelnumber == 3)
		{
			platform[4].Reset(224, 448, 32, 48);
			platform[5].Reset(256, 464, 16, 32);
			platform[6].Reset(0, 352, width, 16);
			
			cube[0].Reset(112, 480, 16, 16, 0, 0, 4, true, 1);
			cube[1].Reset(128, 480, 16, 16, 0, 0, 4, true, 2);
			
			player.Reset(48, 464, 16, 32, 0, 0, 4, true, 0, 16, 16);
			
			doorswitch.door.Reset(448, 464, 16, 32);
			doorswitch.pressureplate.Reset(352, 496, 16, 8);	
		}
		else if (levelnumber == 4)
		{
			platform[4].Reset(272, 432, 16, 16);
			platform[5].Reset(288, 416, 16, 32);
			platform[6].Reset(304, 400, 16, 48);
			platform[7].Reset(320, 384, 48, 64);
			platform[8].Reset(432, 384, 32, 48);
			platform[9].Reset(0, 176, width, 16);
			
			cube[0].Reset(112, 480, 16, 16, 0, 0, 4, true, 1);
			cube[1].Reset(352, 368, 16, 16, 0, 0, 4, true, 2);
			cube[2].Reset(240, 480, 16, 16, 0, 0, 4, true, 3);
			
			player.Reset(48, 464, 16, 32, 0, 0, 4, true, 0, 16, 16);
			
			doorswitch.door.Reset(448, 464, 16, 32);
			doorswitch.pressureplate.Reset(440, 384, 16, 8);
		}
		else if (levelnumber == 5)
		{
			platform[4].Reset(432, 464, 64, 16);
			platform[5].Reset(0, 352, width, 16);
			
			cube[0].Reset(288, 480, 16, 16, 0, 0, 4, true, 1);
			
			player.Reset(48, 464, 16, 32, 0, 0, 4, true, 0, 16, 16);
			
			doorswitch.door.Reset(352, 464, 16, 32);
			doorswitch.pressureplate.Reset(448, 496, 16, 8);
		}
		else if (levelnumber == 6)
		{
			platform[4].Reset(224, 80, 80, 416);
			
			cube[0].Reset(96, 480, 16, 16, 0, 0, 4, true, 1);
			cube[1].Reset(352, 480, 16, 16, 0, 0, 4, true, 2);
			
			player.Reset(48, 464, 16, 32, 0, 0, 4, true, 0, 16, 16);
			
			doorswitch.door.Reset(448, 464, 16, 32);
			doorswitch.pressureplate.Reset(416, 496, 16, 8);
		}
		else if (levelnumber == 7)
		{
			platform[4].Reset(224, 16, 80, 208);
			platform[5].Reset(224, 272, 80, 224);
			
			cube[0].Reset(96, 480, 16, 16, 0, 0, 4, true, 1);
			cube[1].Reset(336, 480, 16, 16, 0, 0, 4, true, 2);
			
			player.Reset(48, 464, 16, 32, 0, 0, 4, true, 0, 16, 16);
			
			doorswitch.door.Reset(448, 464, 16, 32);
			doorswitch.pressureplate.Reset(352, 496, 16, 8);
		}
		else
		{
			return false;
		}
		DrawBackground(curdimension);
		UpdateLevelObjects(0);
		levelcomplete = false;
		return true;
	}
}

/**
Deals with dimensions menu control and pause
*/
void Level::TakeInput(Buttons &buttons)
{
	if (buttons.LIsHeld() && !paused && !player.isholding)
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
	}
	
	if (indimensionsmenu)
	{
		DimensionMenuControl(buttons);
	}
}

/**
Steps all entities in level
*/
void Level::MoveObjects()
{
	if (!paused && !indimensionsmenu)
	{
		//Check if player is on a cube
		player.CheckIfOnMovingPlatform(*this);
		
		//Anti-gravity works differently to other dimensions, so this is a little complicated.
		//If the player is on a cube, move the player in the direction the cube would be moving
		if (curdimension == ANTIGRAVITY && player.isoncube)
		{
			player.ReverseGravity();
			player.ApplyVelocity(*this);
			player.ReverseGravity();
		}
		
		//Step all cubes with exceptions
		for (int i = 0; i < numofcubes; i++)
		{
			//If cube is being held or is below the player in anti-gravity, skip collision detection
			//for now
			if ((player.isholding && i == player.cubeheld)
				|| (curdimension == ANTIGRAVITY && i == player.oncubenum))
			{
				continue;
			}
			cube[i].ApplyVelocity(*this);
		}
		
		//Move player by amount which cube it is standing on has moved
		if (curdimension != ANTIGRAVITY) 
		{
			//If player is on a cube, move the player to where the cube has been moved to
			if (player.isoncube)
			{
				player.MoveWithCube(cube[player.oncubenum]);
			}
			//Step player as normal
			player.ApplyVelocity(*this);
		}
		else
		{
			//In anti-gravity, if the player is not on a cube, apply velocity as normal for both
			//remaining cube and then the player
			if (!player.isoncube)
			{
				cube[player.oncubenum].ApplyVelocity(*this);
				player.ApplyVelocity(*this);
			}
			//If the player is on a cube, move the cube up to where the player's feet are
			else
			{
				cube[player.oncubenum].Move(cube[player.oncubenum].Getx(), player.GetBottom());
			}
		}

		//Move cube being held by player
		if (player.isholding)
		{
			cube[player.cubeheld].ApplyVelocity(*this);
		}
		
		doorswitch.CheckPressurePlate(*this);
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
	else if (buttons.LeftJustPressed())
	{
		if (curdimension == NORMAL)
		{
			curdimension = SLOWMOTION;
		}
		else if (curdimension == ANTIGRAVITY)
		{
			curdimension = NORMAL;
			//Reverse gravity for all cubes in level
			ApplyAntigravity();
		}
	}
	else if (buttons.RightJustPressed())
	{
		if (curdimension == NORMAL)
		{
			curdimension = ANTIGRAVITY;
			//Reverse gravity for all cubes in level
			ApplyAntigravity();
		}
		else if (curdimension == SLOWMOTION)
		{
			curdimension = NORMAL;
		}
	}
}

/**
Applies antigrivity on all cubes in level
*/
void Level::ApplyAntigravity()
{
	for (int i = 0; i < numofcubes; i++)
	{
		cube[i].ReverseGravity();
	}
}

/**
Draws background of the level
*/
void Level::Draw()
{	
	if (curdimension != prevdimension)
	{
		DrawBackground(curdimension);
	}
	
	DrawDoor();
	
	//Clear dimensions menu and cursor
	for (int screenblock = 29; screenblock < 31; screenblock++)
	{
		for (int y = 0; y < 6; y++)
		{
			for (int x = 0; x < 6; x++)
			{
				SetTile(screenblock, x, y, 0);
			}
		}
	}
	
	if (indimensionsmenu)
	{
		DrawDimensionsMenu();
		DrawDimensionsCursor();
	}
}

/**
Draws the icons of the dimensions in the dimensions menu
*/
void Level::DrawDimensionsMenu()
{
	int wallpapertiles[4] = {1, 2, 17, 18};
	
	//Normal icon
	SetTile(29, 2, 2, wallpapertiles[0]);
	SetTile(29, 3, 2, wallpapertiles[1]);
	SetTile(29, 2, 3, wallpapertiles[2]);
	SetTile(29, 3, 3, wallpapertiles[3]);
	
	for (int i = 0; i < 4; i++)
	{
		wallpapertiles[i] += 2;
	}
	
	//Fluffy icon
	SetTile(29, 2, 0, wallpapertiles[0]);
	SetTile(29, 3, 0, wallpapertiles[1]);
	SetTile(29, 2, 1, wallpapertiles[2]);
	SetTile(29, 3, 1, wallpapertiles[3]);
	
	for (int i = 0; i < 4; i++)
	{
		wallpapertiles[i] += 2;
	}
	
	//Heavy icon
	SetTile(29, 2, 4, wallpapertiles[0]);
	SetTile(29, 3, 4, wallpapertiles[1]);
	SetTile(29, 2, 5, wallpapertiles[2]);
	SetTile(29, 3, 5, wallpapertiles[3]);
	
	for (int i = 0; i < 4; i++)
	{
		wallpapertiles[i] += 2;
	}
	
	//Slow motion icon
	SetTile(29, 0, 2, wallpapertiles[0]);
	SetTile(29, 1, 2, wallpapertiles[1]);
	SetTile(29, 0, 3, wallpapertiles[2]);
	SetTile(29, 1, 3, wallpapertiles[3]);
	
	for (int i = 0; i < 4; i++)
	{
		wallpapertiles[i] += 2;
	}
	
	//Anti gravity icon
	SetTile(29, 4, 2, wallpapertiles[0]);
	SetTile(29, 5, 2, wallpapertiles[1]);
	SetTile(29, 4, 3, wallpapertiles[2]);
	SetTile(29, 5, 3, wallpapertiles[3]);
}

/**
Draws the cursor for selecting dimensions in the dimensions menu
*/
void Level::DrawDimensionsCursor()
{
	int cursorx = 0;
	int cursory = 0;
	if (curdimension == NORMAL)
	{
		cursorx = 2;
		cursory = 2;
	}
	else if (curdimension == FLUFFY)
	{
		cursorx = 2;
		cursory = 0;
	}
	else if (curdimension == HEAVY)
	{
		cursorx = 2;
		cursory = 4;
	}
	else if (curdimension == SLOWMOTION)
	{
		cursorx = 0;
		cursory = 2;
	}
	else
	{
		cursorx = 4;
		cursory = 2;
	}
	
	SetTile(30, cursorx, cursory, 11);
	SetTile(30, cursorx + 1, cursory, 12);
	SetTile(30, cursorx, cursory + 1, 27);
	SetTile(30, cursorx + 1, cursory + 1, 28);
}

/**
Draws the level's door.
*/
void Level::DrawDoor()
{
	int doortiles[8] = {67, 68, 83, 84, 83, 84, 83, 84};
	int doortileoffset = 0;
	
	if (!doorswitch.doorcuropen)
	{
		doortileoffset = 2;
	}
	
	for (int i = 0; i < 8; i++)
	{
		doortiles[i] += doortileoffset;
	}
	
	//Set tiles for door.
	SetTileInCorrectScreenblock(25, (doorswitch.door.Getx() / 8), (doorswitch.door.Gety() / 8), doortiles[0]);
	SetTileInCorrectScreenblock(25, (doorswitch.door.Getx() / 8) + 1, (doorswitch.door.Gety() / 8), doortiles[1]);
	SetTileInCorrectScreenblock(25, (doorswitch.door.Getx() / 8), (doorswitch.door.Gety() / 8) + 1, doortiles[2]);
	SetTileInCorrectScreenblock(25, (doorswitch.door.Getx() / 8) + 1, (doorswitch.door.Gety() / 8) + 1, doortiles[3]);
	SetTileInCorrectScreenblock(25, (doorswitch.door.Getx() / 8), (doorswitch.door.Gety() / 8) + 2, doortiles[4]);
	SetTileInCorrectScreenblock(25, (doorswitch.door.Getx() / 8) + 1, (doorswitch.door.Gety() / 8) + 2, doortiles[5]);
	SetTileInCorrectScreenblock(25, (doorswitch.door.Getx() / 8), (doorswitch.door.Gety() / 8) + 3, doortiles[6]);
	SetTileInCorrectScreenblock(25, (doorswitch.door.Getx() / 8) + 1, (doorswitch.door.Gety() / 8) + 3, doortiles[7]);
}

/**
Draws the background of the level;
*/
void Level::DrawBackground(dimension curdimension)
{
	//Dimensions graphics are set out regularly, so I can do this:
	int wallpapertiles[4] = {1, 2, 17, 18};
	int platformtiles[4] = {33, 34, 49, 50};
	
	int dimensiontileoffset = 0;
	
	if (curdimension == FLUFFY)
	{
		dimensiontileoffset = 2;
	}
	else if (curdimension == HEAVY)
	{
		dimensiontileoffset = 4;
	}
	else if (curdimension == SLOWMOTION)
	{
		dimensiontileoffset = 6;
	}
	else if (curdimension == ANTIGRAVITY)
	{
		dimensiontileoffset = 8;
	}
	
	for (int i = 0; i < 4; i++)
	{
		wallpapertiles[i] += dimensiontileoffset;
		platformtiles[i] += dimensiontileoffset;
	}
	
	//Wallpaper
	for (int y = 0; y < 64; y += 2)
	{
		for (int x = 0; x < 64; x += 2)
		{
			SetTileInCorrectScreenblock(25, x, y, wallpapertiles[0]);
			SetTileInCorrectScreenblock(25, x + 1, y, wallpapertiles[1]);
			SetTileInCorrectScreenblock(25, x, y + 1, wallpapertiles[2]);
			SetTileInCorrectScreenblock(25, x + 1, y + 1, wallpapertiles[3]);
		}
	}
	
	//Platforms
	for (int i = 0; i < numofplatforms; i++)
	{
		for (int y = platform[i].Gety() / 8; y < platform[i].GetBottom() / 8; y += 2)
		{
			for (int x = platform[i].Getx() / 8; x < platform[i].GetRight() / 8; x += 2)
			{
				SetTileInCorrectScreenblock(25, x, y, platformtiles[0]);
				SetTileInCorrectScreenblock(25, x + 1, y, platformtiles[1]);
				SetTileInCorrectScreenblock(25, x, y + 1, platformtiles[2]);
				SetTileInCorrectScreenblock(25, x + 1, y + 1, platformtiles[3]);
			}
		}
	}
	
	//Switch
	for (int y = doorswitch.pressureplate.Gety() / 8;
		y < doorswitch.pressureplate.GetBottom() / 8; y++)
	{
		for (int x = doorswitch.pressureplate.Getx() / 8;
			x < doorswitch.pressureplate.GetRight() / 8; x += 2)
		{
			SetTileInCorrectScreenblock(25, x, y, 65);
			SetTileInCorrectScreenblock(25, x + 1, y, 66);
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
void Level::UpdateLevelObjects(int framecounter)
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
	
	int playertileoffset = 0;
	if (player.IsMoving())
	{
		if ((framecounter % 15 == 0) && ((!paused) || (!indimensionsmenu)))
		{
			player.animationframe = !player.animationframe;
		}
		
		if (player.animationframe == true)
		{
			playertileoffset = 2;
		}
		else
		{
			playertileoffset = 4;
		}
	}
	
	if (player.isholding)
	{
		//Allows for height change when carrying cubes on the head
		SetObject(player.GetObjNum(),
		  ATTR0_SHAPE(2) | ATTR0_8BPP | ATTR0_REG
		    | ATTR0_Y(player.drawy + cube[player.cubeheld].GetHeight()),	
		  ATTR1_SIZE(2) | ATTR1_X(player.drawx) | facing,
		  ATTR2_ID8(playertileoffset) | ATTR2_PRIO(2));
	}
	else
	{
		SetObject(player.GetObjNum(),
		  ATTR0_SHAPE(2) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(player.drawy),
		  ATTR1_SIZE(2) | ATTR1_X(player.drawx) | facing,
		  ATTR2_ID8(playertileoffset) | ATTR2_PRIO(2));
	}
	
	int cubetile = 6 + DimensionTileOffset(curdimension);
	
	//Draw cubes
	for (int i = 0; i < numofcubes; i++)
	{
		SetObject(cube[i].GetObjNum(),
		  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(cube[i].drawy),
		  ATTR1_SIZE(1) | ATTR1_X(cube[i].drawx),
		  ATTR2_ID8(cubetile) | ATTR2_PRIO(2));
	}
	
	UpdateObjects();
}

/**
Returns the value of offset to be applied to a tile number depending on the current dimension
*/
int Level::DimensionTileOffset(dimension curdimension)
{
	int dimensiontileoffset = 0;
	
	if (curdimension == FLUFFY)
	{
		dimensiontileoffset = 2;
	}
	else if (curdimension == HEAVY)
	{
		dimensiontileoffset = 4;
	}
	else if (curdimension == SLOWMOTION)
	{
		dimensiontileoffset = 6;
	}
	else if (curdimension == ANTIGRAVITY)
	{
		dimensiontileoffset = 8;
	}	
	
	return dimensiontileoffset;
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