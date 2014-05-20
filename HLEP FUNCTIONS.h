//Main loop
while (true)
{
	...
	
	level1.MoveObjects(buttons);
	level1.Draw();
	level1.UpdateLevelObjects();

	...
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
	
	...
}

/**
Draws the background of the level;
*/
void Level::DrawBackground(dimension curdimension)
{
	...
	
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
	
	...
	
	SetObject(player.GetObjNum(),
	  ATTR0_SHAPE(2) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(player.drawy),
	  ATTR1_SIZE(0) | ATTR1_X(player.drawx) | facing,
	  ATTR2_ID8(0) | ATTR2_PRIO(2));
	
	//Draw cubes
	for (int i = 0; i < numofcubes; i++)
	{
		SetObject(cube[i].GetObjNum(),
		  ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG
			| ATTR0_Y(cube[i].drawy),
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
Determines the background offsets that keep the player in the middle of the screen
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

class Entity : public Object
{	
	private:
		//Methods
		int GetScreenAxis(int &, int &, const int, int &, const int);

	public:	
		//Data
		int drawx;
		int drawy;
		
		//Methods
		void SetScreenPosition(int &, int &);
};