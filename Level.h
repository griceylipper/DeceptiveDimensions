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
		//Methods
		void FillScreenblock(int, int);
		
	public:
		//Data
		Object platform[50];
		Entity cube[20];
		Character player;
		int numofplatforms;
		int numofcubes;
		
		//Methods
		Level();
		void Draw();
		void MoveObjects(Buttons, Level);
		void UpdateObjects();
};

#endif