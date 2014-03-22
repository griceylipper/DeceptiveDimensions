//Object.h

#ifndef _OBJECT_H
#define _OBJECT_H

class Object
{	
	protected:
		//Data
		int x;			//Position of left edge
		int y;			//Position of top edge
		int width;		//Width of object in pixels
		int height;		//Height of object in pixels
		
		//Methods	
		void Reset();
		bool IsTouching(Object);
		void Move(int, int);
		
	public:
		//Methods
		Object();
		Object(int, int, int, int);
		void Reset(int, int, int, int);
		int Getx();
		int Gety();
		int GetRight();
		int GetBottom();
		bool IsColliding(Object);
};

#endif