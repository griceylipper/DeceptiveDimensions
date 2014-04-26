//main.cpp

/*

DECEPTIVE DIMENSIONS
	A Quantum Conundrum Demake
		Roy Mullay 2014
	
*** REFERENCES ***
http://www.gamedev.net/page/resources/_/technical/game-programming/the-guide-to-implementing-2d-platformers-r2936
http://www.coranac.com/tonc/text/fixed.htm
http://www.gameprogrammingpatterns.com/
******************
	
*** TO DO LIST: ***

(Note - this is a VERY ROUGH order of how I want to do things;
 follow it roughly, but do not treat this order as gospel!)

Bug fixes:


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
	
2014/04/25
-Implemented boxes which can now be picked up! Finally!
	-Old code was nearly right, but I needed to go back and make sure every derivative function was
	called by reference instead of value
	-When a box is picked up, player's height must be increased to account for the cube on the head
	-The player must also be moved down and up as it picks up and drops cubes, since the player is
	referenced from its top left hand corner.
-Cleaned up the way levels had to pass themselves as arguments
	-Now uses *this to refer to itself in it's methods
-Added enum to Level for the maximum number of cubes and platforms in a level
	-Used to dereference player from a cube it has just dropped
-Added GetWidth() and GetHeight() methods to the object class
-Made some of the Entity methods use a const reference to the levels being passed to it

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
#include "Buttons.h"

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
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ;
	
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 0;
	
	REG_BG1CNT = BG_CBB(0) | BG_SBB(29) | BG_8BPP | BG_REG_32x32;
	REG_BG1HOFS = 0;
	REG_BG1VOFS = 0;

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
	level1.Draw();
	
	Buttons buttons;

	int frameCounter = 0;
	
	//Main loop
	while (true)
	{
		buttons.Update();
		
		level1.MoveObjects(buttons);
		//level1.Draw();
		level1.UpdateObjects();

		frameCounter = Increment(frameCounter);
		
		WaitVSync();
		FlipBuffers();
		UpdateObjects();
	}

	return 0;
}

//Functions
int Increment(int counter)
{
	counter++;
	if (counter % 60 == 0)
	{
		counter = 0;
	}
	return counter;
}