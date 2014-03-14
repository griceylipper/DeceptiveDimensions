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
		Object();		
		void Reset();
		void Reset(int, int, int, int);
		bool IsColliding(Object);
		bool IsTouching(Object);
		
	public:
		//Methods
		Object(int, int, int, int);
		void Move(int, int);
		int Getx();
		int Gety();
		int GetRight();
		int GetBottom();
};

#endif