#include "Registers.h"



void Registers::update_halfc(u8 target, u8 source)
{
	f.halfc = (	(((target & 0xf) + (source & 0xf)) & 0x10) == 0x10);
}
void Registers::update_halfc(u16 target, u16 source)
{
	f.halfc = (	(((target & 0xff) + (source & 0xff)) & 0x80) == 0x80);
}
void Registers::update_carry(u8 target, u8 source)
{
	f.carry= (	(((target & 0xf) + (source & 0xf)) & 0x10) == 0x10);
}
void Registers::update_carry(u16 target, u16 source)
{
	f.carry= (	(((target & 0xff) + (source & 0xff)) & 0x80) == 0x80);
}
void Registers::update_zero(u16 target)
{
	f.zero= (target == 0);
}
void Registers::update_zero(u8 target)
{
	f.zero =(target == 0);
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
u1 Registers::get_carry()
{
	return f.carry;
}
u1 Registers::get_halfc()
{
	return f.halfc;
}
u1 Registers::get_zero()
{
	return f.zero;
}
u1 Registers::get_sub()
{
	return f.subt;
}