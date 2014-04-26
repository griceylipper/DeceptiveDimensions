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
		
	public:
		//Methods
		Object();
		Object(int, int, int, int);
		void Move(int, int);
		void Reset(int, int, int, int);
		int Getx();
		int Gety();
		int GetWidth();
		int GetHeight();
		int GetRight();
		int GetBottom();
		bool IsColliding(Object);
		bool IsAbove(Object);
};

#endif