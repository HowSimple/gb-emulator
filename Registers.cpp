#include "Registers.h"

Registers::Registers()
{
	af = 0;
	f.zero = 0;
	f.halfc = 0;
	f.subt = 0;
	f.carry = 0;
	bc = 0;
	de = 0;
	hl = 0;
	a = 0;
	b = 0;
	c = 0;
	d = 0;
	e = 0;
	h = 0;
	l = 0; sp = 0; pc = 0;
}

void Registers::set_carry(bool x)
{
	f.carry = x;
}
void Registers::set_halfc(bool x)
{
	f.halfc = x;
}
void Registers::set_zero(bool x)
{
	f.zero = x;
}
void Registers::set_sub(bool x)
{
	f.subt = x;
}
bool Registers::get_carry()
{
	return f.carry;
}
bool Registers::get_halfc()
{
	return f.halfc;
}
bool Registers::get_zero()
{
	return f.zero;
}
bool Registers::get_sub()
{
	return f.subt;
}