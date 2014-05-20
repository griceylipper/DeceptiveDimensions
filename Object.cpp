//Object.cpp

#include "Object.h"

/**
Default constructor. Constructs an object at (0, 0) of width and height of 8 pixels
*/
Object::Object()
{
	x = 0;
	y = 0;
	width = 8;
	height = 8;
}

/**
Overloaded constructor. Constructs an object at (a, b) of width w and height h
*/
Object::Object(int a, int b, int w, int h)
{
	Reset(a, b, w, h);
}

/**
Moves object to (a, b) and resizes it to width w and height h
*/
void Object::Reset(int a, int b, int w, int h)
{
	x = a;
	y = b;
	width = w;
	height = h;
}

/**
Returns true if Object obstacle collides with this object
*/
bool Object::IsColliding(Object obstacle)
{
	//If any sides of obstacle are outside this object
	if (obstacle.GetBottom() <= Gety())
	{
		return false;
	}
	if (obstacle.Gety() >= GetBottom())
	{
		return false;
	}
	if (obstacle.GetRight() <= Getx())
	{
		return false;
	}
	if (obstacle.Getx() >= GetRight())
	{
		return false;
	}
	
	//If none of the sides of obstacle are outside this object,
	return true;
}

/**
Returns true if Object obstacle collides with or is adjacent to this object
*/
bool Object::IsTouching(Object obstacle)
{
	//If any sides of obstacle are outside this object
	if (obstacle.GetBottom() < Gety())
	{
		return false;
	}
	if (obstacle.Gety() > GetBottom())
	{
		return false;
	}
	if (obstacle.GetRight() < Getx())
	{
		return false;
	}
	if (obstacle.Getx() > GetRight())
	{
		return false;
	}
	
	//If none of the sides of obstacle are outside this object,
	return true;
}

/**
Returns true if this object is touching the top side of an Object obstacle
*/
bool Object::IsAbove(Object obstacle)
{
	if (obstacle.GetRight() > Getx()
		&& obstacle.Getx() < GetRight()
		&& IsTouching(obstacle))
	{
		return true;
	}
	return false;
}

// /**
// Returns true if this object is touching bottom side of an Object obstacle
// */
// bool Object::IsBelow(Object obstacle)
// {
	// if (obstacle.GetRight() > Getx()
		// && obstacle.Getx() < GetRight()
// }

/**
Moves object to coordinates (a, b)
*/
void Object::Move(int a, int b)
{
	x = a;
	y = b;
}

/**
Returns x-position of object
*/
int Object::Getx()
{
	return x;
}

/**
Returns y-position of object
*/
int Object::Gety()
{
	return y;
}

/**
Returns width of object
*/
int Object::GetWidth()
{
	return width;
}

/**
Returns height of object
*/
int Object::GetHeight()
{
	return height;
}

/**
Returns x-position of right hand edge of the Object
*/
int Object::GetRight()
{
	return x + width;
}

/**
Returns y-position of bottom edge of the Object
*/
int Object::GetBottom()
{
	return y + height;
}