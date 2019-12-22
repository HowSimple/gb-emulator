#pragma once
#include <cstdint>
#include <bitset>
#include <iostream>
#include <cstdlib>


typedef uint8_t u8;
typedef uint16_t u16;
typedef unsigned char u1;
enum flag { ZERO = 7, SUBT = 6, HALFC = 5, CARRY = 4};
enum op_type {ADD, ADC,SUB, LD, NOP, OR, AND, CP};


class Registers
{
	public:
		Registers();

		void op_dec(u16& target);

		void op_or(u8& target, u8 source);

		void op_dec(u8& target);

		void op_ld(u8& target, u8 const source);

		void op_ld(u16& target, u16 source);

		void op_and(u8& target, u8 source);

		void op_xor(u8& target, u8 source);

		void op_swap(u8& target);

		void op_swap(u16& target);

		u1 get_carry();

		u1 get_halfc();

		u1 get_zero();

		u1 get_sub();

		void set_carry(bool x);

		void set_halfc(bool x);

		void set_zero(bool x);

		void set_sub(bool x);

		void op_nop();

		void update_halfc(u8 target, u8 source);
		void update_halfc(u16 target, u16 source);
		void update_carry(u8 target, u8 source);
		void update_carry(u16 target, u16 source);

		void update_zero(u16 target);

		void update_zero(u8 target);

		void update_flags(bool zero, bool subt, bool carry, bool halfc);

		// arithmetic instructions
		void op_add(u8& target, u8 source);

		void op_sub(u8& target, u8 source);

		void op_adc(u8& target, u8 source);

	

		void op_cp(u16& target, u16 const value);
		void op_cpl(u8& target);
		  // increment/decrement instructions

		void op_inc(u8& target);
		struct flags {
			bool zero; 
			bool subt;
			bool halfc;
			bool carry;

		};
			   
	
	// registers can be accessed individually or as a pair
	// each pair of registers occupies the same 16bit location
	
		u8 a;
		flags f;
				
			
			
	
	
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

