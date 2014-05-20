//Object.h

#ifndef _OBJECT_H
#define _OBJECT_H

/**
2D bodies which have a position, a width and a height.
*/
class Object
{	
	protected:
		//Data
		int x;			//Position of left edge in level
		int y;			//Position of top edge in level
		int width;		//Width of object in pixels
		int height;		//Height of object in pixels
		
		//Methods	
		void Reset();
		bool IsTouching(Object);
		bool IsColliding(Object);
		
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
		bool IsAbove(Object);
};

#endif