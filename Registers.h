#pragma once
#include "Gameboy.h"

union Registers
{
	// CPU registers, each stores 8-bits
	_8b a;
	_8b b;
	_8b c;
	_8b d;
	_8b e;
	_8b f;
	_8b h; 
	_8b l;

	_16b af;


	// 16-bit getters/setters 
	_16b get_af();
	void set_af(_16b);

};

