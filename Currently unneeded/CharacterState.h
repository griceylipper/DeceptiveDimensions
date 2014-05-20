//CharacterState.h

#ifndef _CHARACTERSTATE_H
#define _CHARACTERSTATE_H

class CharacterState
{
	public:
		//Data
		static JumpingState jumping;
		static StandingState standing;
		
		virtual ~CharacterState();
		virtual void HandleInput(Character &, Buttons);
		virtual void Update(Character &);
};

#endif