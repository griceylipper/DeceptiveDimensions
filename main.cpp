//main.cpp

/**

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
-Implement physics for moving platforms.
-Implement dimensions

*******************

*** CHANGE LOG ***
	
2014/05/16
-Introduced Doxygen style comments to classes and methods.

*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "gba.h"
#include "font.h"
#include "spritesheet3.h"
#include "TitleScreen.h"
//#include "spritesheet2.h"
#include "backgroundnewnew.h"
#include "Object.h"
#include "Entity.h"
#include "Character.h"
#include "Level.h"
#include "Buttons.h"
#include "DoorSwitch.h"

//Function prototypes
int Increment(int);
void DrawText(int, int, const char[]);

// A blank tile.
// See the palette below for what the colour numbers mean.
// const uint8_t blank_tile[64] = {
	// 0, 0, 0, 0, 0, 0, 0, 0,
	// 0, 0, 0, 0, 0, 0, 0, 0,
	// 0, 0, 0, 0, 0, 0, 0, 0,
	// 0, 0, 0, 0, 0, 0, 0, 0,
	// 0, 0, 0, 0, 0, 0, 0, 0,
	// 0, 0, 0, 0, 0, 0, 0, 0,
	// 0, 0, 0, 0, 0, 0, 0, 0,
	// 0, 0, 0, 0, 0, 0, 0, 0,
// };

int main()
{
	// Set display options.
	// DCNT_MODE0 sets mode 0, which provides four tiled backgrounds.
	// DCNT_OBJ enables objects.
	// DCNT_OBJ_1D make object tiles mapped in 1D (which makes life easier).
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_OBJ;
	
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32 | BG_PRIO(0);
	
	REG_BG1CNT = BG_CBB(0) | BG_SBB(29) | BG_8BPP | BG_REG_32x32 | BG_PRIO(1);
	
	REG_BG2CNT = BG_CBB(0) | BG_SBB(25) | BG_8BPP | BG_REG_64x64 | BG_PRIO(2);
	REG_BG2HOFS = 0;
	REG_BG2VOFS = 0;
	
	REG_BG3CNT = BG_CBB(0) | BG_SBB(24) | BG_8BPP | BG_REG_32x32 | BG_PRIO(3);
	REG_BG3HOFS = 0;
	REG_BG3VOFS = 0;

	// (Charblocks 4 and 5 are for object tiles;
	// 8bpp tiles 0-255 are in CB 4, tiles 256-511 in CB 5.)
	
	//Custom spritesheet loading
	// LoadPaletteBGData(0, TitleScreenPal, sizeof TitleScreenPal);
	// LoadTileData(0, 0, TitleScreenTiles, sizeof TitleScreenTiles);
	
	ClearObjects();
	
	Buttons buttons;
	int frameCounter = 0;
	
	// for (int y = 0; y < (SCREEN_HEIGHT / 8); y++)
	// {
		// for (int x = 0; x < (SCREEN_WIDTH / 8); x++)
		// {
			// SetTile(25, x, y, x + (y * (SCREEN_WIDTH / 8)));
		// }
	// }
	
	// //Title screen (under construction)
	// while (true)
	// {
		// if (buttons.StartJustPressed())
		// {
			// break;
		// }
	// }
	
	LoadPaletteObjData(0, spritesheet3Pal, sizeof spritesheet3Pal);
	LoadPaletteBGData(0, backgroundnewnewPal, sizeof backgroundnewnewPal);
	LoadTileData(4, 0, spritesheet3Tiles, sizeof spritesheet3Tiles);
	LoadTileData(0, 0, backgroundnewnewTiles, sizeof backgroundnewnewTiles);
	
	Level level1;
	
	for (int screenblock = 21; screenblock < 31; screenblock++)
	{
		level1.FillScreenblock(screenblock, 0);
	}
	
	level1.DrawBackground(level1.curdimension);
	
	//Main game loop
	while (true)
	{
		buttons.Update();
		
		level1.MoveObjects(buttons);
		level1.Draw();
		level1.UpdateLevelObjects();

		frameCounter = Increment(frameCounter);
		
		WaitVSync();
		FlipBuffers();
	}

	return 0;
}

//Functions
/**
Increments counter by 1, and resets to 0 when counter == 60.
 */
int Increment(int counter)
{
	counter++;
	if (counter % 60 == 0)
	{
		counter = 0;
	}
	return counter;
}