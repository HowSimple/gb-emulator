#pragma once
#include "Registers.h"
#include "CPU.h"
#include "RAM.h"
#include "Instruction.h"
#include <iostream>
#include <bitset>

typedef unsigned char byte;
typedef char signed_byte;
typedef unsigned short _8b;
typedef signed short _16b;



int main()
{


	Registers regs;
	regs.a = 200;
	regs.f = 135;
	std::cout << "a: " << regs.a << " " << std::bitset<8>(regs.a) << "\n";
	std::cout << "f: " << regs.f << std::bitset<8>(regs.f) << "\n";
	std::cout << "af: " << regs.get_af() << std::bitset<16>(regs.get_af()) << "\n";
	_16b num = 12345;
	regs.set_af(num);
	std::cout << "b: " << regs.f << "\n";

	return 0;
}

