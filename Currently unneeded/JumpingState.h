//JumpingState.h

#ifndef _JUMPINGSTATE_H
#define _JUMPINGSTATE_H

class JumpingState : public CharacterState
{
	public:
		JumpingState();
		virtual void HandleInput(Character &, Level);
	
	private:
		bool canjump = false;
};

#endif