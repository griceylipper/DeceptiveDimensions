//SpikeRow.h

#ifndef _SPIKEROW_H
#define _SPIKEROW_H

#include "Object.h"


class SpikeRow : public Object
{
	private:
		//void DrawSingleSpike(int, int, int);

	public:
		//Data
		int orientation;
		
		//Functions
		SpikeRow();		
		SpikeRow(int, int, int, int, int);
		void Reset();
		void Reset(int, int, int, int, int);
		//void Draw();
};

#endif