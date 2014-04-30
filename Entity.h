//Entity.h

#ifndef _ENTITY_H
#define _ENTITY_H

//Included dependencies
#include "Object.h"

//Forward declared dependencies
class Character;
class Level;

class Entity : public Object
{	
	private:
		//Methods
		void ApplyTerminal();
		void MoveBackIfColliding(int &, int &, const Object &);
		void StepAxis(int &, int &, const Level &);
		int PlusOrMinus(int);
		void ApplyGravity();
	
	protected:
		//Data
		int xVel;
		int yVel;
		int gravity;
		int objnum;
		int weight;
		int terminalx;
		int terminaly;
		int decel;
		
		//Constants for when xVel/yVel is stationary (offset due to bit shifting)
		//Is there a better way to define constants in classes?
		//enum {BITSHIFT = 8, STATIONARY = BITSHIFT / 2};
	
		//Methods
		void ApplyResistance();

	public:	
		//Data
		bool isheld;
		
		//Methods
		Entity();
		Entity(int, int, int, int, int, int, int, int, int);
		void ApplyVelocity(Level &);
		void ReverseGravity();
		int GetObjNum();
		void Reset(int, int, int, int, int, int, int, int, int);
		bool IsCollidingLevel(const Level &);
		void GetThrown(const Character &);
};

#endif