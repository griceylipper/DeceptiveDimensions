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

//Returns true if Object a collides with calling object
bool Object::IsColliding(Object a)
{
	//If any sides of a are outside calling object
	if (a.GetBottom() <= Gety())
	{
		return false;
	}
	if (a.Gety() >= GetBottom())
	{
		return false;
	}
	if (a.GetRight() <= Getx())
	{
		return false;
	}
	if (a.Getx() >= GetRight())
	{
		return false;
	}
	
	//If none of the sides of a are outside calling object,
	return true;
}

//The same as IsColliding(), expect it also returns true if two objects edges are adjacent
bool Object::IsTouching(Object a)
{
	//If any sides of a are outside calling object
	if (a.GetBottom() < Gety())
	{
		return false;
	}
	if (a.Gety() > GetBottom())
	{
		return false;
	}
	if (a.GetRight() < Getx())
	{
		return false;
	}
	if (a.Getx() > GetRight())
	{
		return false;
	}
	
	//If none of the sides of a are outside calling object,
	return true;
}

//Returns true if calling object is directly above object a
bool Object::IsAbove(Object a)
{
	if ((a.GetRight() > Getx()) && (a.Getx() < GetRight()) && IsTouching(a))
	{
		return true;
	}
	return false;
}

//Moves object to coordinates (a, b)
void Object::Move(int a, int b)
{
	x = a;
	y = b;
}

//Returns x-position of object
int Object::Getx()
{
	return x;
}

//Returns y-position of object
int Object::Gety()
{
	return y;
}

//Returns width of object
int Object::GetWidth()
{
	return width;
}

//Returns height of object
int Object::GetHeight()
{
	return height;
}

//Returns x-position of right hand edge of the Object
int Object::GetRight()
{
	return x + width;
}

//Returns y-position of bottom edge of the Object
int Object::GetBottom()
{
	return y + height;
}