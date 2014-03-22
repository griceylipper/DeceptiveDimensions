//Entity.h

#ifndef _ENTITY_H
#define _ENTITY_H

#include "Object.h"
#include "Level.h"

class Entity : public Object
{	
	private:
		void ApplyTerminal();
		void Reset(int, int, int, int, int, int, int, int, int);
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
		
		//Methods
		Entity();
		
	public:
		//Data
		enum {STATIONARY = 4};		//Constant for xVel/yVel for stationary (offset due to bit shifting)
									//Is there a better way to define constants in classes?
		
		//Methods
		Entity(int, int, int, int, int, int, int, int, int);
		void ApplyGravity();
		void ApplyVelocity(Object);
		void ApplyVelocity(Level);
		void ReverseGravity();
		int GetObjNum();
		
};

#endif