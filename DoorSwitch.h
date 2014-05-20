//DoorSwitch.h

#ifndef _DOORSWITCH_H
#define _DOORSWITCH_H

//Included dependencies
#include "Object.h"

//Forward declared dependencies
class Level;

class DoorSwitch
{
	public:
		//Data
		Object door;
		Object pressureplate;
		bool doorcuropen;
		bool doorprevopen;
		
		//Methods
		DoorSwitch();
		void CheckPressurePlate(Level &);
};

#endif