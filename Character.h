//Character.h

#ifndef _CHARACTER_H
#define _CHARACTER_H

//Included dependencies
#include "Entity.h"
#include "gba.h"

//Forward declared dependencies
class Level;

class Character : public Entity
{
	private:
		int accel;
		int decel;
		bool onplatform;
	
	public:
		//Data
		int spawnx;
		int spawny;
		
		//Functions
		Character();
		Character(int, int, int, int, int, int, int, int, int, int, int);
		void Reset(int, int, int, int, int, int, int, int, int, int, int);
		void ReadButtons(uint16_t, uint16_t, Level);
		void Jump();
		void CheckOnScreen();
		void Spawn();
};

#endif