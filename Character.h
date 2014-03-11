//Character.h

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Entity.h"
#include "gba.h"

class Character : public Entity
{
	public:
		//Data
		int spawnx;
		int spawny;
		
		//Functions
		Character(int, int, int, int, int, int, int, int, int, int, int);
		void Reset(int, int, int, int, int, int, int, int, int, int, int);
		void ApplyButtons(uint16_t, uint16_t);
		void Jump();
};

#endif