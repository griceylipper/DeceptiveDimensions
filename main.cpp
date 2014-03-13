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
-Do jumping properly
-Figure out constructors for classes - which are really necessary?
-Start making data and methods private in classes.
-Finalise interaction between GBA objects and my own Objects
-ANNOTATE MORE CODE - This will be good practice to retain understanding of this after a break in coding.

New features:

-Get player animation working
-Add platforms
	-Ask for advice on whether to create separate classes for them or just use Object class
	-Figure out how to go about drawing them
-Consider having a collision box for player that is smaller than character graphics
-Add background graphics.
	-Take a look at Prince of Persia - work out if oblique angle is practical to implement using tiles.
	-Maybe ask whether Kirsteen can provide graphics
	-Implement scrolling backgrounds
		-Make player stay in middle of screen when moving around level.
-Implement Entities which can be picked up.
-Implement physics for moving platforms.
-Implement dimensions

*******************

*** CHANGE LOG ***
	
2014/03/12
-Added IsColliding function to Character class
-Restricted jumping so double jumping is impossible - a temporary method for the moment
-Stopped player randomly drifting left across the floor
	-Note: this sometimes happens when you press the RIGHT button - WTF?!
	-Probably related: stop player from travelling faster left to right than right to left
	-These were problems because of bit shift negative bias.
*/

#include <stdint.h>
#include <stdlib.h>
#include "gba.h"
#include "font.h"
#include "sprite.h"
#include "Object.h"
#include "Entity.h"
#include "Character.h"

//Function prototypes
void SetObject(Entity);

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

// A red box as a tile.
// (If you're making a game with lots of these, it's easier to convert
// them from graphics files than to write them out by hand like this!)
const uint8_t red_box_tile[64] = {
	1, 1, 1, 1, 1, 1, 1, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	1, 3, 3, 3, 3, 3, 3, 2,
	2, 2, 2, 2, 2, 2, 2, 2,
};

// A smiley face.
const uint8_t smiley_tile[64] = {
	0, 0, 3, 3, 3, 3, 0, 0,
	0, 3, 3, 3, 3, 3, 3, 0,
	3, 3, 1, 3, 3, 1, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 3, 3, 3, 3, 3, 3, 3,
	3, 1, 3, 3, 3, 3, 1, 3,
	0, 3, 1, 1, 1, 1, 3, 0,
	0, 0, 3, 3, 3, 3, 0, 0,
};

int main()
{
	// Set display options.
	// DCNT_MODE0 sets mode 0, which provides four tiled backgrounds.
	//   (But we've not actually turned any of them on... yet.)
	// DCNT_OBJ enables objects.
	// DCNT_OBJ_1D make object tiles mapped in 1D (which makes life easier).
	REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ;
	
	// Set up the object palette.
	SetPaletteObj(0, RGB(0, 0, 0)); // black (but actually transparent)
	SetPaletteObj(1, RGB(0, 0, 0)); // black
	SetPaletteObj(2, RGB(31, 31, 31)); // white
	SetPaletteObj(3, RGB(31, 31, 0)); // yellow
	SetPaletteObj(4, RGB(31, 0, 0)); // red

	// Load the tiles for the objects into charblock 4.
	// (Charblocks 4 and 5 are for object tiles;
	// 8bpp tiles 0-255 are in CB 4, tiles 256-511 in CB 5.)
	//LoadTile8(4, 1, smiley_tile);
	
	//Custom spritesheet loading
	LoadPaletteObjData(0, spritePal, sizeof spritePal);
	LoadTileData(4, 0, spriteTiles, sizeof spriteTiles);
	
	ClearObjects();
	
	Character player(116, 76, 8, 16, 0, 0, 4, 1, 0, 8, 8);
	Object platform(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH, 1);

	uint16_t prevButtons = 0;
	
	int frameCounter = 0;
	
	//Main loop
	while (true)
	{
		uint16_t curButtons = REG_KEYINPUT;
		
		player.ReadButtons(curButtons, prevButtons, platform);
		player.ApplyGravity();
		player.ApplyVelocity();
		player.CheckOnScreen();
		
		SetObject(player.GetObjNum(),
		  ATTR0_SHAPE(2) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(player.Gety()),
		  ATTR1_SIZE(0) | ATTR1_X(player.Getx()),
		  ATTR2_ID8(0));

		frameCounter++;
		
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