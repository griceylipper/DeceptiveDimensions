//JumpingState.cpp

JumpingState::JumpingState()
{
	canjump = false;
}

virtual void JumpingState::HandleInput(Character &player, Buttons buttons)
{
	//Jumping
	canjump = false;
	for (int i = 0; i < level.numofplatforms; i++)
	{
		if (player.IsAbove(level.platform[i]))
		{
			onplatform = true;
			break;
		}
	}
	if (!canjump)
	{
		for (int i = 0; i < level.numofcubes; i++)
		{
			if (player.IsAbove(level.cube[i]))
			{
				onplatform = true;
				break;
			}
		}
	}
}