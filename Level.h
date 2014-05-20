//Level.h

#ifndef _LEVEL_H
#define _LEVEL_H

//Included dependencies
#include "Object.h"
#include "Entity.h"
#include "Character.h"
#include "Buttons.h"
#include "DoorSwitch.h"

class Level : public Object		//x and y coordinates in object refer to offset so that the level is
								//displayed correctly
{
	private:
		//Data
		bool paused;
		bool indimensionsmenu;
		
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
		Object platform[MAXPLATFORMS];
		Entity cube[MAXCUBES];
		Character player;
		DoorSwitch doorswitch;
		int numofplatforms;
		int numofcubes;
		int backgroundoffsetx;
		int backgroundoffsety;
		enum dimension {NORMAL, FLUFFY, HEAVY, SLOWMOTION, ANTIGRAVITY};
		dimension curdimension;
		dimension prevdimension;
		
		//Methods
		Level();
		void TakeInput(Buttons &buttons);
		void Draw();
		void DrawBackground(dimension);
		void MoveObjects();
		void UpdateLevelObjects();
		void FillScreenblock(int, int);			
		int DimensionTileOffset(dimension);
};

#endif