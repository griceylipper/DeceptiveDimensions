//main.cpp

/*

DECEPTIVE DIMENSIONS
	A Quantum Conundrum Demake
		Roy Mullay 2014
	
*** REFERENCES ***
http://www.gamedev.net/page/resources/_/technical/game-programming/the-guide-to-implementing-2d-platformers-r2936
http://www.coranac.com/tonc/text/fixed.htm
******************
	
*** TO DO LIST: ***

(Note - this is a VERY ROUGH order of how I want to do things;
 follow it roughly, but do not treat this order as gospel!)

Bug fixes:

Clean-up:
-Work out how to do collision detection for cubes without testing collision on themselves
-Create function which outputs which side of an object another object is on for use in jumping
-Figure out constructors for classes - which are really necessary?
-Start making data and methods private in classes.
-Finalise interaction between GBA objects and my own Objects
-ANNOTATE MORE CODE - This will be good practice to retain understanding of this after a break in coding.

New features:

-Get player animation working
-Redraw player sprite
	-Give player outline so it is clearer against background.
-Add more background graphics.
	-Maybe ask whether Kirsteen can provide graphics
	-Implement scrolling backgrounds
		-Make player stay in middle of screen when moving around level.
-Implement Entities which can be picked up.
-Implement physics for moving platforms.
-Implement dimensions

*******************

*** CHANGE LOG ***
	
2014/03/31
-Deleted redundant SpikeRow class from previous game
-Fixed problems with circular inclusion
	-Fixed by use of forward declaration in Character and Entity classes
-Cleaned up Entity::ApplyVelocity code
	-Made a new function called MoveBackIfColliding()
	-Position and Velocity variables are passed to it by reference
-Test cubes added to Level class
	-They do very little at the moment, and are represented by the decapitated head of the player
-The player now a member of the Level class
	-Movement of all objects is now handled by Level::MoveObjects
		-This contains old player movement code which used to be in the main
		-The main is SO TINY now
-New Music considerations.txt file
	-List of music I would like to implement for the different dimensions if possible
	-Not important at all right now

*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "gba.h"
#include "font.h"
#include "sprite.h"
//#include "spritesheet2.h"
#include "background.h"
#include "Object.h"
#include "Entity.h"
#include "Character.h"
#include "Level.h"

//Function prototypes
int Increment(int);
void SetObject(Entity);
void FillScreenblock(int, int);
void DrawText(int, int, const char[]);

// A blank tile.
// See the palette below for what the colour numbers mean.
const uint8_t blank_tile[64] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
};

int main()
{
	// Set display options.
	// DCNT_MODE0 sets mode 0, which provides four tiled backgrounds.
	//   (But we've not actually turned any of them on... yet.)
	// DCNT_OBJ enables objects.
	// DCNT_OBJ_1D make object tiles mapped in 1D (which makes life easier).
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ;
	
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 0;
	
	// Set up the object palette.
	SetPaletteObj(0, RGB(0, 0, 0)); // black (but actually transparent)
	SetPaletteObj(1, RGB(0, 0, 0)); // black
	SetPaletteObj(2, RGB(31, 31, 31)); // white
	SetPaletteObj(3, RGB(31, 31, 0)); // yellow
	SetPaletteObj(4, RGB(31, 0, 0)); // red

	// (Charblocks 4 and 5 are for object tiles;
	// 8bpp tiles 0-255 are in CB 4, tiles 256-511 in CB 5.)
	
	//Custom spritesheet loading
	LoadPaletteObjData(0, spritePal, sizeof spritePal);
	//LoadPaletteObjData(0, spritesheet2Pal, sizeof spritesheet2Pal);
	LoadPaletteBGData(0, backgroundPal, sizeof backgroundPal);
	LoadTileData(4, 0, spriteTiles, sizeof spriteTiles);
	//LoadTileData(4, 0, spritesheet2Tiles, sizeof spritesheet2Tiles);
	LoadTileData(0, 0, backgroundTiles, sizeof backgroundTiles);
	
	//Background
	FillScreenblock(30, 3);
	
	ClearObjects();
	
	//Character player(116, 76, 8, 16, 0, 0, 4, 1, 0, 16, 16);
	Level level1;

	uint16_t prevButtons = 0;
	
	int frameCounter = 0;
	
	//Main loop
	while (true)
	{
		uint16_t curButtons = REG_KEYINPUT;
		
		level1.MoveObjects(curButtons, prevButtons, level1);
		level1.Draw();

		frameCounter = Increment(frameCounter);
		
		prevButtons = curButtons;
		
		WaitVSync();
		UpdateObjects();
	}

	return 0;
}

//Functions
void SetObject(Entity a)
{
	SetObject(a.GetObjNum(),
	  ATTR0_SHAPE(2) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(a.Gety()),
	  ATTR1_SIZE(0) | ATTR1_X(a.Getx()),
	  ATTR2_ID8(0));
}

void FillScreenblock(int screenblock, int tile)
{
	for (int y = 0; y < 32; ++y)
	{
		for (int x = 0; x < 32; ++x)
		{
			SetTile(screenblock, x, y, tile);
		}
	}
}

int Increment(int counter)
{
	counter++;
	if (counter % 60 == 0)
	{
		counter = 0;
	}
	return counter;
}