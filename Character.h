//Character.h

#ifndef _CHARACTER_H
#define _CHARACTER_H

//Included dependancies
#include "Entity.h"
#include "gba.h"

//Forward declared dependancies
class Level;

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
		Character();
		Character(int, int, int, int, int, int, int, int, int, int, int);
		void Reset(int, int, int, int, int, int, int, int, int, int, int);
		void ReadButtons(uint16_t, uint16_t, Level);
		void Jump();
		void CheckOnScreen();
		void Spawn();
};

#endif