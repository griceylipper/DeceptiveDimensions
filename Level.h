//Level.h

#ifndef _LEVEL_H
#define _LEVEL_H

#include "Object.h"

class Level : public Object		//x and y coordinates in object refer to 
								//offset so that the level is displayed correctly
{
	public:
		//Data
		Object platform[50];
		int numofplatforms;
		
		//Methods
		Level();
		void Draw();
};

#endif