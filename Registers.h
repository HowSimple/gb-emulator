#pragma once


typedef unsigned char byte;
typedef char signed_byte;
typedef unsigned short _8b;
typedef signed short _16b;

struct Registers
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

	


	// 16-bit getters/setters 
	_16b get_af();
	void set_af(_16b);


};

