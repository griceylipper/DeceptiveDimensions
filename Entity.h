//Entity.h

#ifndef _ENTITY_H
#define _ENTITY_H

//Included dependancies
#include "Object.h"

//Forward declared dependancies
class Level;

class Entity : public Object
{	
	private:
		//Methods
		void ApplyTerminal();
		void MoveBackIfColliding(int &, int &, Object);
		int PlusOrMinus(int);
	
	protected:
		//Data
		int xVel;
		int yVel;
		int gravity;
		int objnum;
		int weight;
		int terminalx;
		int terminaly;
		
	public:
		//Data
		enum {STATIONARY = 4};		//Constant for xVel/yVel for stationary (offset due to bit shifting)
									//Is there a better way to define constants in classes?
		
		//Methods
		Entity();
		Entity(int, int, int, int, int, int, int, int, int);
		void ApplyGravity();
		void ApplyVelocity(Object);
		void ApplyVelocity(Level);
		void ReverseGravity();
		int GetObjNum();
		void Reset(int, int, int, int, int, int, int, int, int);
};

#endif