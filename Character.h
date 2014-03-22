//Character.h

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Entity.h"
#include "Level.h"
#include "gba.h"

class Character : public Entity
{
	private:
		int accel;
		int decel;
		bool isonplatform;
	
	public:
		//Data
		int spawnx;
		int spawny;
		
		//Functions
		Character(int, int, int, int, int, int, int, int, int, int, int);
		void Reset(int, int, int, int, int, int, int, int, int, int, int);
		void ReadButtons(uint16_t, uint16_t, Level);
		void Jump();
		void CheckOnScreen();
		void Spawn();
};

#endif