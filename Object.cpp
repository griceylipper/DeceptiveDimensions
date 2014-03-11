//Object.cpp

#include "Object.h"

//Constructor
Object::Object()
{
	Reset();
}

//Overloaded constructor
Object::Object(int a, int b, int w, int h)
{
	Reset(a, b, w, h);
}

//Default Object data values
void Object::Reset()
{
	x = 0;
	y = 0;
	width = 8;
	height = 8;
}

//Allows setting of all four fields with a single method
void Object::Reset(int a, int b, int w, int h)
{
	x = a;
	y = b;
	width = w;
	height = h;
}

//Moves object to coordinates (a, b)
void Object::Move(int a, int b)
{
	x = a;
	y = b;
}

//Returns x-position of right hand edge of the Object
int Object::Right()
{
	return x + width;
}

//Returns y-position of bottom edge of the Object
int Object::Bottom()
{
	return y + height;
}