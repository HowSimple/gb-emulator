#pragma once
#include <cstdint>
#include <bitset>
#include <iostream>
#include <cstdlib>


typedef uint8_t u8;
typedef uint16_t u16;
typedef unsigned char u1;
enum flag { ZERO = 7, SUBT = 6, HALFC = 5, CARRY = 4};

class Registers
{
	public:
		Registers();
		u1 get_carry();

		u1 get_halfc();

		u1 get_zero();

		u1 get_sub();

		void set_carry(bool x);

		void set_halfc(bool x);

		void set_zero(bool x);

		void set_sub(bool x);


	
			   
	
	// registers can be accessed individually or as a pair
	// each pair of registers occupies the same 16bit location
	
		struct flags {
			bool zero;
			bool subt;
			bool halfc;
			bool carry;

		};
		
				
			
			
		struct {
			union {
				struct {
					u8 a;
					flags f;
				};
				u16 af;
			};
		};
	
	struct {
		union {
			struct {
				u8 c;
				u8 b;
			};
			u16 bc;
		};
	};
	struct {
		union {
			struct {
				u8 e;
				u8 d;
			};
			u16 de;
		};
	};
	struct {
		union {
			struct {
				u8 l;
				u8 h;
			};
			u16 hl;
		};
	};
	u16 sp;
	u16 pc;


};

