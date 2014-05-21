//Level.h

#ifndef _LEVEL_H
#define _LEVEL_H

//Included dependencies
#include "Object.h"
#include "Entity.h"
#include "Character.h"
#include "Buttons.h"
#include "DoorSwitch.h"

/**
Object which contains all other objects and entities, and provides functions for all features of
main game loop.
*/
class Level : public Object	
{
	private:
		//Data
		bool paused;				//Whether or not the game is paused
		bool indimensionsmenu;		//Whether or not the game has the dimensions menu open
		
		//Methods
		void DimensionMenuControl(Buttons &);
		void ApplyEntityOffsets();
		void DetermineBackgroundOffsets();
		void SetTileInCorrectScreenblock(int, int, int, int);
		void DrawDoor();
		void DrawDimensionsMenu();
		void DrawDimensionsCursor();
		void ApplyAntigravity();
		
	public:
		//Data
		enum {MAXCUBES = 20, MAXPLATFORMS = 50};
		Object platform[MAXPLATFORMS];		//Platforms by which the player and cubes are bounded
		Entity cube[MAXCUBES];				//Cubes which the player can manipulate
		Character player;					//The player character
		DoorSwitch doorswitch;				//The door and switch which are connected
		int numofplatforms;					//Number of platforms in the level
		int numofcubes;						//Number of cubes in the level
		int backgroundoffsetx;				//The x value by which the background layer is offset
		int backgroundoffsety;				//The y value by which the background layer is offset
		enum dimension {NORMAL, FLUFFY, HEAVY, SLOWMOTION, ANTIGRAVITY};
		dimension curdimension;				//The current dimension of the level
		dimension prevdimension;			//The dimension of the level in the previous frame
		bool levelcomplete;					//Whether or not a level has just been completed
		int levelnumber;					//The number of the current level
		
		//Methods
		Level(int);
		void TakeInput(Buttons &buttons);
		void Draw();
		void DrawBackground(dimension);
		void MoveObjects();
		void UpdateLevelObjects(int);
		void FillScreenblock(int, int);			
		int DimensionTileOffset(dimension);
		bool CheckIfLevelComplete();
};

#endif