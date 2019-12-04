#pragma once
#include "Registers.h"
#include "instructions.h"
#include <iostream>
#include <cstdint>


typedef char _1b;
typedef uint8_t _8b;
typedef uint16_t _16b;

class Gameboy
{
	 Registers regs;

	 _1b screen[160][144][3];
	 _1b ram[8192];

};

