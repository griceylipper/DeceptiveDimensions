//Entity.h

#ifndef _ENTITY_H
#define _ENTITY_H

//Included dependencies
#include "Object.h"
#include "gba.h"

//Forward declared dependencies
class Character;
class Level;

/**
An Object which can move to areas unoccupied by other Objects in Level.
*/
class Entity : public Object
{	
	private:
		//Methods
		void ApplyTerminal();
		void MoveBackIfColliding(int &, int &, const Object &);
		void StepAxis(int &, int &, const Level &);
		void ApplyGravity();
		int PlusOrMinus(int);
		
	protected:
		//Data
		int xVel;			//Velocity in x direction. Not equal to number of pixels moved per frame
		int yVel;			//Velocity in y direction. Not equal to number of pixels moved per frame
		int gravity;		//Velocity applied every frame to yVel.
		int decel;			//Velocity applied every frame to xVel in opposite direction to motion
		int terminalx;		//Maximum velocity in the x direction
		int terminaly;		//Maximum velocity in the y direction		
		int objnum;			//Used as object number with GBA SetObject() and as general identifier
		bool heavy;			//Weight of entity. Only heavy entities can activate switches
		
		// Constants for when xVel/yVel is stationary (offset due to bit shifting)
		// Is there a better way to define constants in classes?
		// enum {BITSHIFT = 8, STATIONARY = BITSHIFT / 2};
	
		//Methods
		void ApplyResistance();

	public:	
		//Data
		int drawx;
		int drawy;
		bool isheld;		//Whether or not the Entity is being held by a Character
		uint16_t visible;
		
		//Methods
		Entity();
		Entity(int, int, int, int, int, int, int, bool, int);
		void ApplyVelocity(Level &);
		void ReverseGravity();
		int GetObjNum();
		void Reset(int, int, int, int, int, int, int, bool, int);
		bool IsCollidingLevel(const Level &);
		void GetThrown(const Character &);
};

#endif