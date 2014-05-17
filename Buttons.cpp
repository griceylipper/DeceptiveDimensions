//Buttons.cpp

#include "Buttons.h"

/**
Constructor
*/
Buttons::Buttons()
{
	current = REG_KEYINPUT;
	previous = 0;
}

/**
Updates the state of the current and previous button states
*/
void Buttons::Update()
{
	previous = current;
	current = REG_KEYINPUT;
}

/**
Returns true if A button is being held in current frame
*/
bool Buttons::AIsHeld()
{
	if ((current & KEY_A) == 0)
	{
		return true;
	}
	return false;
}

/**
Returns true if B button is being held in current frame
*/
bool Buttons::BIsHeld()
{
	if ((current & KEY_B) == 0)
	{
		return true;
	}
	return false;
}

/**
Returns true if L button is being held in current frame
*/
bool Buttons::LIsHeld()
{
	if ((current & KEY_L) == 0)
	{
		return true;
	}
	return false;
}

/**
Returns true if R button is being held in current frame
*/
bool Buttons::RIsHeld()
{
	if ((current & KEY_R) == 0)
	{
		return true;
	}
	return false;
}

/**
Returns true if Up button is being held in current frame
*/
bool Buttons::UpIsHeld()
{
	if ((current & KEY_UP) == 0)
	{
		return true;
	}
	return false;
}

/**
Returns true if Down button is being held in current frame
*/
bool Buttons::DownIsHeld()
{
	if ((current & KEY_DOWN) == 0)
	{
		return true;
	}
	return false;
}

/**
Returns true if Left button is being held in current frame
*/
bool Buttons::LeftIsHeld()
{
	if ((current & KEY_LEFT) == 0)
	{
		return true;
	}
	return false;
}

/**
Returns true if Right button is being held in current frame
*/
bool Buttons::RightIsHeld()
{
	if ((current & KEY_RIGHT) == 0)
	{
		return true;
	}
	return false;
}

/**
Returns true if Start button is being held in current frame
*/
bool Buttons::StartIsHeld()
{
	if ((current & KEY_START) == 0)
	{
		return true;
	}
	return false;
}

/**
Returns true if Select button is being held in current frame
*/
bool Buttons::SelectIsHeld()
{
	if ((current & KEY_SELECT) == 0)
	{
		return true;
	}
	return false;
}

/**
Returns true if A button is being held in current frame, but not in the previous frame
*/
bool Buttons::AJustPressed()
{
	if (((current & KEY_A) == 0) && ((previous & KEY_A) != 0))
	{
		return true;
	}
	return false;
}

/**
Returns true if B button is being held in current frame, but not in the previous frame
*/
bool Buttons::BJustPressed()
{
	if (((current & KEY_B) == 0) && ((previous & KEY_B) != 0))
	{
		return true;
	}
	return false;
}

/**
Returns true if L button is being held in current frame, but not in the previous frame
*/
bool Buttons::LJustPressed()
{
	if (((current & KEY_L) == 0) && ((previous & KEY_L) != 0))
	{
		return true;
	}
	return false;
}

/**
Returns true if R button is being held in current frame, but not in the previous frame
*/
bool Buttons::RJustPressed()
{
	if (((current & KEY_R) == 0) && ((previous & KEY_R) != 0))
	{
		return true;
	}
	return false;
}

/**
Returns true if Up button is being held in current frame, but not in the previous frame
*/
bool Buttons::UpJustPressed()
{
	if (((current & KEY_UP) == 0) && ((previous & KEY_UP) != 0))
	{
		return true;
	}
	return false;
}

/**
Returns true if Down button is being held in current frame, but not in the previous frame
*/
bool Buttons::DownJustPressed()
{
	if (((current & KEY_DOWN) == 0) && ((previous & KEY_DOWN) != 0))
	{
		return true;
	}
	return false;
}

/**
Returns true if Left button is being held in current frame, but not in the previous frame
*/
bool Buttons::LeftJustPressed()
{
	if (((current & KEY_LEFT) == 0) && ((previous & KEY_LEFT) != 0))
	{
		return true;
	}
	return false;
}

/**
Returns true if Right button is being held in current frame, but not in the previous frame
*/
bool Buttons::RightJustPressed()
{
	if (((current & KEY_RIGHT) == 0) && ((previous & KEY_RIGHT) != 0))
	{
		return true;
	}
	return false;
}

/**
Returns true if Start button is being held in current frame, but not in the previous frame
*/
bool Buttons::StartJustPressed()
{
	if (((current & KEY_START) == 0) && ((previous & KEY_START) != 0))
	{
		return true;
	}
	return false;
}

/**
Returns true if Select button is being held in current frame, but not in the previous frame
*/
bool Buttons::SelectJustPressed()
{
	if (((current & KEY_SELECT) == 0) && ((previous & KEY_SELECT) != 0))
	{
		return true;
	}
	return false;
}
