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
-Strange graphical glitch at right side of top edge
	-Seems to change with altering entity velocities

Clean-up:
-Figure out constructors for classes - which are really necessary?
-Start making data and methods private in classes.
-Finalise interaction between GBA objects and my own Objects
-ANNOTATE MORE CODE - This will be good practice to retain understanding of this after a break in
 coding.

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
	
2014/04/07
-Worked out how to do collision detection for cubes without testing collision on themselves
-Added StepAxis() function to Entity to further clean up ApplyVelocity() code
-Added another enum to Entity called BITSHIFT
	-Basically a cop out to get rid of some of the magic numbers related to bitshifting
-Created function which outputs true when one object is directly above another for use in jumping
-Moved FillScreenblock() function to Level class
-Realised I had no FlipBuffers() in the main (woops!), so that's been added
-Formatted all files such that no line is no more than 100 characters long
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

	// (Charblocks 4 and 5 are for object tiles;
	// 8bpp tiles 0-255 are in CB 4, tiles 256-511 in CB 5.)
	
	//Custom spritesheet loading
	LoadPaletteObjData(0, spritePal, sizeof spritePal);
	//LoadPaletteObjData(0, spritesheet2Pal, sizeof spritesheet2Pal);
	LoadPaletteBGData(0, backgroundPal, sizeof backgroundPal);
	LoadTileData(4, 0, spriteTiles, sizeof spriteTiles);
	//LoadTileData(4, 0, spritesheet2Tiles, sizeof spritesheet2Tiles);
	LoadTileData(0, 0, backgroundTiles, sizeof backgroundTiles);

	
	ClearObjects();
	
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
		FlipBuffers();
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

int Increment(int counter)
{
	counter++;
	if (counter % 60 == 0)
	{
		counter = 0;
	}
	return counter;
}