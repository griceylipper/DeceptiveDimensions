//Character.h

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Entity.h"
#include "gba.h"

class Character : public Entity
{
	private:
		int accel;
		int decel;
	
	public:
		//Data
		int spawnx;
		int spawny;
		
		//Functions
		Character(int, int, int, int, int, int, int, int, int, int, int);
		void Reset(int, int, int, int, int, int, int, int, int, int, int);
		void ReadButtons(uint16_t, uint16_t, Object);
		void Jump();
		void CheckOnScreen();
		void Spawn();
};

#endif