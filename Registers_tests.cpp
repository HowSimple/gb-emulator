#pragma once
#include "Registers.h"
#include "CPU.h"
#include "RAM.h"
#include "Instruction.h"
#include <iostream>
#include <bitset>


typedef char _1b;
typedef uint8_t _8b;
typedef uint16_t _16b;



int main()
{


	Registers regs;
	_16b num = 12345;
	regs.set_af(num);
	std::cout << "a: " << " " << std::bitset<8>(regs.a) << "\n";
	std::cout << "f: " << std::bitset<8>(regs.f) << "\n";
	std::cout << "af: " << std::bitset<16>(regs.get_af()) << "\n";

	regs.a = 200;
	regs.f = 135;
	std::cout << "a: " << " " << std::bitset<8>(regs.a) << "\n";
	std::cout << "f: " << std::bitset<8>(regs.f) << "\n";
	std::cout << "af: " << std::bitset<16>(regs.get_af()) << "\n";

	return 0;
}

bool regTest(Registers regs)
{
	
	

	return true;

}