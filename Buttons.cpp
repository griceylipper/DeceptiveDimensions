//Buttons.cpp

#include "Buttons.h"

//Constructor
Buttons::Buttons()
{
	current = REG_KEYINPUT;
	previous = 0;
}

void Buttons::Update()
{
	previous = current;
	current = REG_KEYINPUT;
}

bool Buttons::AIsHeld()
{
	if ((current & KEY_A) == 0)
	{
		return true;
	}
	return false;
}

bool Buttons::BIsHeld()
{
	if ((current & KEY_B) == 0)
	{
		return true;
	}
	return false;
}

bool Buttons::LIsHeld()
{
	if ((current & KEY_L) == 0)
	{
		return true;
	}
	return false;
}

bool Buttons::RIsHeld()
{
	if ((current & KEY_R) == 0)
	{
		return true;
	}
	return false;
}

bool Buttons::UpIsHeld()
{
	if ((current & KEY_UP) == 0)
	{
		return true;
	}
	return false;
}

bool Buttons::DownIsHeld()
{
	if ((current & KEY_DOWN) == 0)
	{
		return true;
	}
	return false;
}

bool Buttons::LeftIsHeld()
{
	if ((current & KEY_LEFT) == 0)
	{
		return true;
	}
	return false;
}

bool Buttons::RightIsHeld()
{
	if ((current & KEY_RIGHT) == 0)
	{
		return true;
	}
	return false;
}

bool Buttons::StartIsHeld()
{
	if ((current & KEY_START) == 0)
	{
		return true;
	}
	return false;
}

bool Buttons::SelectIsHeld()
{
	if ((current & KEY_SELECT) == 0)
	{
		return true;
	}
	return false;
}

bool Buttons::AJustPressed()
{
	if (((current & KEY_A) == 0) && ((previous & KEY_A) != 0))
	{
		return true;
	}
	return false;
}

bool Buttons::BJustPressed()
{
	if (((current & KEY_B) == 0) && ((previous & KEY_B) != 0))
	{
		return true;
	}
	return false;
}

bool Buttons::LJustPressed()
{
	if (((current & KEY_L) == 0) && ((previous & KEY_L) != 0))
	{
		return true;
	}
	return false;
}

bool Buttons::RJustPressed()
{
	if (((current & KEY_R) == 0) && ((previous & KEY_R) != 0))
	{
		return true;
	}
	return false;
}

bool Buttons::UpJustPressed()
{
	if (((current & KEY_UP) == 0) && ((previous & KEY_UP) != 0))
	{
		return true;
	}
	return false;
}

bool Buttons::DownJustPressed()
{
	if (((current & KEY_DOWN) == 0) && ((previous & KEY_DOWN) != 0))
	{
		return true;
	}
	return false;
}

bool Buttons::LeftJustPressed()
{
	if (((current & KEY_LEFT) == 0) && ((previous & KEY_LEFT) != 0))
	{
		return true;
	}
	return false;
}

bool Buttons::RightJustPressed()
{
	if (((current & KEY_RIGHT) == 0) && ((previous & KEY_RIGHT) != 0))
	{
		return true;
	}
	return false;
}

bool Buttons::StartJustPressed()
{
	if (((current & KEY_START) == 0) && ((previous & KEY_START) != 0))
	{
		return true;
	}
	return false;
}

bool Buttons::SelectJustPressed()
{
	if (((current & KEY_SELECT) == 0) && ((previous & KEY_SELECT) != 0))
	{
		return true;
	}
	return false;
}
