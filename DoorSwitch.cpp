//DoorSwitch.cpp

#include "DoorSwitch.h"
#include "Level.h"

/**
Constructor
*/
DoorSwitch::DoorSwitch()
{
	doorcuropen = false;
	doorprevopen = false;
}

/**
Updates the open / closed state of the door by reading the switch
*/
void DoorSwitch::CheckPressurePlate(Level &level)
{
	doorprevopen = doorcuropen;
	doorcuropen = false;
	if (pressureplate.IsBelow(level.player))
	{
		doorcuropen = true;
	}
	
	if (!doorcuropen)
	{
		for (int i = 0; i < level.numofcubes; i++)
		{
			if (pressureplate.IsBelow(level.cube[i]))
			{
				doorcuropen = true;
				break;
			}
		}
	}
}