#pragma once
#include <cstdint>
#include <cstdlib>


typedef uint8_t u8;
typedef uint16_t u16;

class Registers
{
	public:
		Registers();
		bool get_carry();

		bool get_halfc();

		bool get_zero();

		bool get_sub();
		void set_carry(bool x);

		void set_halfc(bool x);

		void set_zero(bool x);

		void set_sub(bool x);
				
		// all registers can be accessed individually or as a pair
		// each pair of registers occupies the same 16bit location		
	struct {
		union {
			struct {
				u8 a;
				struct { bool zero, subt, halfc, carry; } f;
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

