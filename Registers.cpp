#pragma once
#include "Registers.h"



_16b Registers::get_af()
{
	_16b af = (a << 8) | b;
	return af;
}

void Registers::set_af(_16b data)
{
	a = data << a;
	f = data >> f;
}
