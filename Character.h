//Character.h

#ifndef _CHARACTER_H
#define _CHARACTER_H

//Included dependencies
#include "Entity.h"
#include "Buttons.h"

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
		int cubeheld;
		bool isholding;
		
		//Functions
		Character();
		Character(int, int, int, int, int, int, int, int, int, int, int);
		void Reset(int, int, int, int, int, int, int, int, int, int, int);
		void ReadButtons(Buttons &, Level &);
		void Jump();
		void CheckOnScreen();
		void Spawn();
};

#endif