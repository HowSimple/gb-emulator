#include "Registers.h"

Registers::Registers()
{
	//af = 0;
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
void Registers::op_ld(u8& target, u8 const source) // load source to target 
{
	target = source; // 1 cycle
}

void Registers::op_ld(u16& target, u16 source) // load source to target 
{
	target = source; // 1 cycle
}

void Registers::op_cpl(u8& target) //  set target to complement of target
{
	target = ~target; // 1 cycle
}


void Registers::op_swap(u8& target) // rotate upper/lower 4bits in target
{
	target = target << 4;
}
void Registers::op_swap(u16& target) // rotate upper/lower 8bits in target
{
	target = target << 8;
}

// arithmetic instructions
void Registers::op_add(u8& target, u8 source) // adds value at source to target 
{
	update_carry(target, source);
	update_halfc(target, source);
	target += source;
	update_zero(target);
}
void Registers::op_sub(u8& target, u8 source) // adds value at source to target 
{
	set_sub(1);
	update_carry(target, source);
	update_halfc(target, source);
	target -= source;
	update_zero(target);
}

void Registers::op_adc(u8& target, u8 source) // adds value at source and carry to target. 
{
	set_sub(0);
	update_carry(target, source);
	update_halfc(target, source);
	target += source;
	update_zero(target);

}



void Registers::op_inc(u8& target) // increment target
{
	//update_carry(target, 0x1);
	//update_halfc(target, source);
	target++;
	update_zero(target);
}

void Registers::op_dec(u8& target) // decrement target 
{
	target -= 1; // 1 cycle
}

void Registers::op_dec(u16& target) // decrement target 
{
	target -= 1; // 1 cycle
}





// logical instructions
void Registers::op_xor(u8& target, u8 source) // adds value at source to target 
{
	target = target ^ source;
	update_zero(target);
}
void Registers::op_or(u8& target, u8 source) // adds value at source to target 
{
	target = target | source;
	update_zero(target);
}
void Registers::op_and(u8& target, u8 source) // adds value at source to target 
{
	target = target & source;
	update_zero(target);
	set_halfc(1);
}


// misc instructions


