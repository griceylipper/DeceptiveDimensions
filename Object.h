//Object.h

#ifndef _OBJECT_H
#define _OBJECT_H

class Object
{	
	public:
		//Data
		int x;			//Position of left edge
		int y;			//Position of top edge
		int width;		//Width of object in pixels
		int height;		//Height of object in pixels
		
		//Functions
		Object();
		Object(int, int, int, int);
		void Reset();
		void Reset(int, int, int, int);
		void Move(int, int);
		int Right();
		int Bottom();
};

#endif