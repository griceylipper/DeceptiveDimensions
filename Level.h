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
		enum {MAXCUBES = 20, MAXPLATFORMS = 50};
		Object platform[MAXPLATFORMS];
		Entity cube[MAXCUBES];
		Character player;
		int numofplatforms;
		int numofcubes;
		
		//Methods
		Level();
		void Draw();
		void MoveObjects(Buttons &);
		void UpdateObjects();
};

#endif