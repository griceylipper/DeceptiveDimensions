//StandingState.h

#ifndef _STANDINGSTATE_H
#define _STANDINGSTATE_H

class StandingState : public CharacterState
{
	public:
		StandingState();
		virtual void HandleInput(Character &, Level);
	
	private:
		bool canjump;
};

#endif