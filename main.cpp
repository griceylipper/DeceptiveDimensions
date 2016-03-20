//main.cpp

/**

DECEPTIVE DIMENSIONS
	A Quantum Conundrum Demake
		Roy Mullay 2014
	
*** REFERENCES ***
http://higherorderfun.com/blog/2012/05/20/the-guide-to-implementing-2d-platformers/
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


*******************

*** CHANGE LOG ***
	
2014/05/16
-Introduced Doxygen style comments to classes and methods.

*/

#include <string.h>
#include "gba.h"
#include "font.h"
#include "spritesheet4.h"
//#include "TitleScreen.h"
#include "backgroundnewnew.h"
#include "Object.h"
#include "Entity.h"
#include "Character.h"
#include "Level.h"
#include "Buttons.h"
#include "DoorSwitch.h"

//Function prototypes
void DrawText(int, int, const char[]);

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
	
	ClearObjects();
	
	SetPaletteBG(1, RGB(31, 31, 31)); // white
	
	//Load each tile in font_bold into it's corresponding position in charblock 0
	for (int i = 0; i < 128; i++)
	{
		LoadTile8(0, i, font_bold[i]);
	}
	
	DrawText(5, (SCREEN_HEIGHT / 16) - 2, "DECEPTIVE DIMENSIONS");
	DrawText(5, (SCREEN_HEIGHT / 16), "Press start to begin");
	
	Buttons buttons;
	int framecounter = 0;
	
	//Title screen (under construction)
	while (true)
	{
		buttons.Update();
		
		if (buttons.StartJustPressed())
		{
			break;
		}
		
		WaitVSync();	
	}
	
	while (true)
	{
		//Load Custom spritesheet
		LoadPaletteObjData(0, spritesheet4Pal, sizeof spritesheet4Pal);
		LoadPaletteBGData(0, backgroundnewnewPal, sizeof backgroundnewnewPal);
		LoadTileData(4, 0, spritesheet4Tiles, sizeof spritesheet4Tiles);
		LoadTileData(0, 0, backgroundnewnewTiles, sizeof backgroundnewnewTiles);
		
		int levelnumber = 1;
		
		Level level(levelnumber);
		
		for (int screenblock = 21; screenblock < 31; screenblock++)
		{
			level.FillScreenblock(screenblock, 0);
		}
		
		level.DrawBackground(level.curdimension);
		
		bool gamerunning = true;
		
		//Main game loop
		while (gamerunning)
		{
			buttons.Update();
			
			gamerunning = level.CheckIfLevelComplete();
			level.TakeInput(buttons);
			level.MoveObjects();
			level.Draw();
			level.UpdateLevelObjects(framecounter);

			framecounter++;
			
			WaitVSync();
			FlipBuffers();
		}
		
		//Reload each tile in font_bold into it's corresponding position in charblock 0
		for (int i = 0; i < 128; i++)
		{
			LoadTile8(0, i, font_bold[i]);
		}
		
		SetPaletteBG(0, RGB(0, 0, 0)); // black
		SetPaletteBG(1, RGB(31, 31, 31)); // white		
		
		for (int screenblock = 25; screenblock < 31; screenblock++)
		{
			for (int y = 0; y < 32; y++)
			{
				for (int x = 0; x < 32; x++)
				{
					SetTile(screenblock, x, y, 0);
				}
			}
		}
		
		level.player.drawx = SCREEN_WIDTH;
		
		SetObject(level.player.GetObjNum(),
		  ATTR0_SHAPE(2) | ATTR0_8BPP | ATTR0_HIDE,
		  ATTR1_SIZE(2) | ATTR1_X(level.player.drawx),
		  ATTR2_ID8(0) | ATTR2_PRIO(2));
		
		UpdateObjects();
		
		DrawText(6, (SCREEN_HEIGHT / 16) - 2, "That's all folks!!");
		DrawText(3, (SCREEN_HEIGHT / 16), "Press start to try again");
		
		while (true)
		{
			buttons.Update();
			
			if (buttons.StartJustPressed())
			{
				break;
			}
			
			WaitVSync();
		}
	}
}

/**
Outputs string string to screen at position (x, y)
*/
void DrawText(int x, int y, const char string[])
{
	for (int i = 0; i < int(strlen(string)); i++)
	{
		SetTile(30, x, y, string[i]);
		x++;
	}
}