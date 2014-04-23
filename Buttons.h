//Buttons.h

#ifndef _BUTTONS_H
#define _BUTTONS_H

//Included dependencies
#include "gba.h"

class Buttons
{
	public:
		//Data
		uint16_t current;
		uint16_t previous;
		
		//Methods
		Buttons();
		void Update();
		
		bool AIsHeld();
		bool BIsHeld();
		bool LIsHeld();
		bool RIsHeld();
		bool UpIsHeld();
		bool DownIsHeld();
		bool LeftIsHeld();
		bool RightIsHeld();
		bool StartIsHeld();
		bool SelectIsHeld();
		
		bool AJustPressed();
		bool BJustPressed();
	    bool LJustPressed();
		bool RJustPressed();
		bool UpJustPressed();
		bool DownJustPressed();
		bool LeftJustPressed();
		bool RightJustPressed();
		bool StartJustPressed();
		bool SelectJustPressed();
};

#endif