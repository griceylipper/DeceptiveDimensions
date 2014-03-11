//SpikeRow.cpp

#include "SpikeRow.h"

//Functions
SpikeRow::SpikeRow()
{
	Reset();
}

SpikeRow::SpikeRow(int x, int y, int w, int h, int o)
{
	Reset(x, y, w, h, o);
}

void SpikeRow::Reset()
{
	Object::Reset();
	orientation = 0;
}

void SpikeRow::Reset(int x, int y, int w, int h, int o)
{
	Object::Reset(x, y, w, h);
	orientation = o;
}