//Level.h

#ifndef _LEVEL_H
#define _LEVEL_H

#include "Object.h"
#include "Entity.h"
#include "Character.h"
#include "gba.h"

class Level : public Object		//x and y coordinates in object refer to offset so that the level is
								//displayed correctly
{
	private:
		//Methods
		void FillScreenblock(int, int);
		
	public:
		//Data
		Object platform[50];
		Entity cube[2];
		Character player;
		int numofplatforms;
		int numofcubes;
		
		//Methods
		Level();
		void Draw();
		void MoveObjects(uint16_t, uint16_t, Level);
};

#endif