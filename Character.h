//Character.h

#ifndef _CHARACTER_H
#define _CHARACTER_H

//Included dependencies
#include "Entity.h"
#include "Buttons.h"

//Forward declared dependencies
class Level;

/**
An Entity which can be controlled using buttons, and can pick up other entities in Level.
*/
class Character : public Entity
{
	private:
		//Data
		int accel;				//Rate of acceleration in the x direction when a button is held
		bool onplatform;		//True if the character is on a platform from which it can jump

		//Methods
		void Movement(Buttons &);
		void ManipulateCube(Level &);
		void PickUp(Level &);
		void Drop(Level &);
		void ThrowCube(Level &);
		
	public:
		//Data
		int spawnx;				//Value of x-position at which character spawns
		int spawny;				//Value of y-position at which character spawns
		int cubeheld;			//ID number for the cube the character is currently holding
		bool isholding;			//True if the character is holding an item
		bool isoncube;			//True if character is currently standing on a cube
		int oncubenum;			//Number of cube currently stood on
		int oncubex;			//x-position of cube currently stood on
		int oncubey;			//y-position of cube currently stood on
		enum {LEFT = true, RIGHT = false};
		bool direction;			//Direction in which the player is facing
		
		
		//Methods
		Character();
		Character(int, int, int, int, int, int, int, bool, int, int, int);
		void Reset(int, int, int, int, int, int, int, bool, int, int, int);
		void ReadButtons(Buttons &, Level &);
		void TryJumping(Level &);
		void CheckIfOnMovingPlatform(Level &);
		void MoveWithCube(Entity &);
		void CheckOnScreen();
		void Spawn();
};

#endif