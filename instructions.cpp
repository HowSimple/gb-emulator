
#include "Gameboy.h"
#include "Registers.h"
#include "instructions.h"
class instructions
{
	_8b carry;

	void set_carry(_8b reg)
	{
		carry = reg;
	}
	instructions(_8b reg)
	{
		set_carry(reg);
	}
	

	// arithmetic instructions
	void op_add(_8b& target, _8b& const source) // adds value at source to target 
	{
		target += source; // 1 cycle
	}

	void op_adc(_8b& target, _8b& const source, _1b& carry) // adds value at source and carry to target. 
	{
		target += source; // 1 cycle
	}
	void op_cp(_8b& target, _8b& const value) // subtract value from target 
	{
		target -= value; // 1 cycle
	}
	void op_cp(_16b& target, _16b& const value) // subtract value from target 
	{
		target -= value; // 1 cycle
	}

	void op_cpl(_8b& target) //  set target to complement of target
	{
		target = ~target; // 1 cycle
	}
	// increment/decrement instructions

	void op_inc(_8b& target) // increment target
	{
		target += 1; // 1 cycle
	}

	void op_inc(_16b& target) // increment target 
	{
		target += 1; // 1 cycle
	}


	void op_dec(_8b& target) // decrement target 
	{
		target -= 1; // 1 cycle
	}

	void op_dec(_16b& target) // decrement target 
	{
		target -= 1; // 1 cycle
	}

	// copy


	void op_ld(_8b& target, _8b& const source) // load source to target 
	{
		target = source; // 1 cycle
	}

	// bitwise instructions

	void op_ld(_16b& target, _16b& const source) // load source to target 
	{
		target = source; // 1 cycle
	}
	void op_ld(_8b& target, _8b& const source) // load source to target 
	{
		target = source; // 1 cycle
	}

	void op_and(_8b& target, _8b& const source) // bitwise AND
	{
		target = target | source;
	}


	void op_swap(_8b& target) // swap upper/lower 4bits in target
	{
		target = target << 4; // 1 cycle
	}
	void op_swap(_16b& target) // swap upper/lower 8bits in target
	{
		target = target << 8; // 1 cycle
	}

};
