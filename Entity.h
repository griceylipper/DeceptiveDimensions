//Entity.h

#ifndef _ENTITY_H
#define _ENTITY_H

#include "Object.h"

class Entity : public Object
{	
	private:
		void ApplyTerminal();
		void Reset(int, int, int, int, int, int, int, int, int);
	
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
		//Methods
		Entity(int, int, int, int, int, int, int, int, int);
		void ApplyGravity();
		void ApplyVelocity();
		void ReverseGravity();
		int GetObjNum();
		
};

#endif