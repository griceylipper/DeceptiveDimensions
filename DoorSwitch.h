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
		Object door;				//The bounding box of the door
		Object pressureplate;		//The bounding box of the pressure plate
		bool doorcuropen;			//Whether or not the door is currently open
		bool doorprevopen;			//Whether or not the door was open in the previous frame
		
		enum dimension {NORMAL, FLUFFY, HEAVY, SLOWMOTION, ANTIGRAVITY};
		
		//Methods
		DoorSwitch();
		void CheckPressurePlate(Level &);
};

#endif