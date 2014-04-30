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
		//Data
		int accel;
		bool onplatform;

		//Methods
		void Movement(Buttons &);
		void ManipulateCube(Level &);
		void PickUp(Level &);
		void Drop(Level &);
		void ThrowCube(Level &);
		
	public:
		//Data
		int spawnx;
		int spawny;
		int cubeheld;
		bool isholding;
		enum {LEFT = true, RIGHT = false};
		bool direction;
		
		//Methods
		Character();
		Character(int, int, int, int, int, int, int, int, int, int, int);
		void Reset(int, int, int, int, int, int, int, int, int, int, int);
		void ReadButtons(Buttons &, Level &);
		void Jump(Level &);
		void CheckOnScreen();
		void Spawn();
};

#endif