//Entity.h

#ifndef _ENTITY_H
#define _ENTITY_H

#include "Object.h"

class Entity : public Object
{	
	private:
		//Data

		
		//Methods
		void ApplyTerminal();

	public:
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
		Entity(int, int, int, int, int, int, int, int, int);
		void Reset(int, int, int, int, int, int, int, int, int);
		void ApplyGravity();
		void ApplyVelocity();
		void ReverseGravity();
};

#endif