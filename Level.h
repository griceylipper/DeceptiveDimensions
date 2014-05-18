//Level.h

#ifndef _LEVEL_H
#define _LEVEL_H

//Included dependencies
#include "Object.h"
#include "Entity.h"
#include "Character.h"
#include "Buttons.h"

class Level : public Object		//x and y coordinates in object refer to offset so that the level is
								//displayed correctly
{
	private:
		//Data
		int backgroundoffsetx;
		int backgroundoffsety;
		bool paused;
		bool indimensionsmenu;
		
		//Methods
		void DimensionMenuControl(Buttons &);
		void FillScreenblock(int, int, int);
		void ApplyEntityOffsets();
		void DetermineBackgroundOffsets();
		
	public:
		//Data
		enum {MAXCUBES = 20, MAXPLATFORMS = 50};
		Object platform[MAXPLATFORMS];
		Entity cube[MAXCUBES];
		Character player;
		int numofplatforms;
		int numofcubes;
		enum dimension {NORMAL, FLUFFY, HEAVY, SLOWMOTION, ANTIGRAVITY};
		dimension curdimension;
		dimension prevdimension;
		
		//Methods
		Level();
		void Draw();
		void DrawBackground(dimension);
		void MoveObjects(Buttons &);
		void UpdateLevelObjects();
};

#endif