//Buttons.h

#ifndef _BUTTONS_H
#define _BUTTONS_H

//Included dependencies
#include "gba.h"

/**
Encapsulates the state of current and previous buttons, and provides functions for updating the 
state variables, and for checking whether any button is being held or is just pressed.
*/
struct Buttons
{
	//Data
	uint16_t current;		//State of buttons in current frame
	uint16_t previous;		//State of buttons in previous frame
	
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