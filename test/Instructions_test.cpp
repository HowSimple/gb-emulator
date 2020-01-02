#include "pch.h"
#include "CPU.h"
#define A cpu.reg.a
#define B cpu.reg.b
#define C cpu.reg.c
#define D cpu.reg.d
#define E cpu.reg.e
#define H cpu.reg.h
#define L cpu.reg.l
#define AF cpu.reg.af
#define BC cpu.reg.bc
#define DE cpu.reg.de
#define HL cpu.reg.hl
#define PC cpu.reg.pc
#define SP cpu.reg.sp
#define F cpu.reg


TEST(CPU, add01)
{
	CPU cpu;

	A = 0b00000110;
	B = 0b00000001;
	cpu.op_add(A, B);
	EXPECT_EQ(A, 7);
}
TEST(CPU, add02_carry)
{
	CPU cpu;
	A = 0xFF;
	B = 0x1;

	cpu.op_add(A, B);
	EXPECT_EQ(A, 0x0);
	EXPECT_EQ(F.get_carry(), 1);
}
TEST(CPU, sub01)
{
	CPU cpu;
	A = 0x8;
	B = 0x4;

	cpu.op_sub(A, B);
	EXPECT_EQ(A, 0x4);
}
TEST(CPU, sub01f)
{
	CPU cpu;
	A = 0x8;
	B = 0x4;

	cpu.op_sub(A, B);
	EXPECT_EQ(A, 0x4);

	EXPECT_EQ(F.get_carry(), 0);
	EXPECT_EQ(F.get_halfc(), 0);
}
TEST(CPU, inc01)
{
	CPU cpu;
	A = 6;

	cpu.op_inc(A);
	EXPECT_EQ(A, 7);

}

TEST(CPU, inc02)
{
	CPU cpu;
	A = 0xFF;

	cpu.op_inc(A);
	EXPECT_EQ(A, 0);
	EXPECT_EQ(F.get_carry(), 0);
	EXPECT_EQ(F.get_zero(), 1);
	EXPECT_EQ(F.get_halfc(), 0);


}
TEST(CPU, dec01)
{
	CPU cpu;
	A = 8;

	cpu.op_dec(A);
	EXPECT_EQ(A, 7);
}
TEST(CPU, dec02)
{
	CPU cpu;
	A = 8;

	cpu.op_dec(A);
	EXPECT_EQ(A, 7);
}
TEST(CPU, and01)
{
	CPU cpu;
	A = 0b00101110;
	B = 0b11101010;

	cpu.op_and(B);
	EXPECT_EQ(A, 0b00101010);

	EXPECT_EQ(F.get_carry(), 0);
	EXPECT_EQ(F.get_halfc(), 1);


}

TEST(CPU, or01)
{
	CPU cpu;
	A = 0b00001110;
	B = 0b11100000;

	cpu.op_or(B);
	EXPECT_EQ(A, 0b11101110);
}
TEST(CPU, or01F)
{
	CPU cpu;
	A = 0b00001110;
	B = 0b11100000;

	cpu.op_or(B);
	EXPECT_EQ(A, 0b11101110);
	EXPECT_EQ(F.get_zero(), 0);

}

TEST(CPU, xor01)
{
	CPU cpu;
	A = 0b01101110;
	B = 0b11101100;

	cpu.op_xor(B);
	EXPECT_EQ(A, 0b10000010);
}

TEST(CPU, xor01f)
{
	CPU cpu;
	A = 0b01101110;
	B = 0b11101100;

	cpu.op_xor(B);
	EXPECT_EQ(A, 0b10000010);

	EXPECT_EQ(F.get_carry(), 0);
	EXPECT_EQ(F.get_halfc(), 0);
	EXPECT_EQ(F.get_zero(), 0);
	EXPECT_EQ(F.get_sub(), 0);
}

TEST(CPU, swap01)
{
	CPU cpu;

	A = 0b00001111;
	cpu.op_swap(A);
	EXPECT_EQ(A, 0b11110000);
}

TEST(CPU, ld01)
{
	CPU cpu;
	B = 0x4;
	cpu.op_ld(A, B);
	EXPECT_EQ(A, 0x4);
}

TEST(CPU, op_swap01)
{
	CPU cpu;
	
	A = 0b01001111;
	cpu.op_swap(A);
	EXPECT_EQ(A, 0b11110100);
}

TEST(CPU, op_rr01)
{
	CPU cpu;
	F.set_carry(0);
	A = 0b00111111;
	cpu.op_rr(A);
	EXPECT_EQ(A, 0b00011111);
}

TEST(CPU, op_rl01)
{
	CPU cpu;

	A = 0b00111111;
	cpu.op_rl(A);
	EXPECT_EQ(A, 0b01111110);
}
TEST(CPU, op_sla01)
{
	CPU cpu;

	A = 0b10011111;
	cpu.op_sla(A);
	EXPECT_EQ(A, 0b00111110);
}
TEST(CPU, op_sla02)
{
	CPU cpu;

	A = 0b10011111;
	cpu.op_sla(A);
	EXPECT_EQ(A, 0b00111110);
	EXPECT_EQ(F.get_carry(), 1);

}
TEST(CPU, op_sra01)
{
	CPU cpu;

	A = 0b00111111;
	cpu.op_sra(A);
	EXPECT_EQ(A, 0b00011111);
}
TEST(CPU, op_sra02)
{
	CPU cpu;

	A = 0b00111111;
	cpu.op_sra(A);
	EXPECT_EQ(A, 0b00011111);
	EXPECT_EQ(F.get_carry(), 1);
}
TEST(CPU, op_set01)
{
	CPU cpu;

	A = 0b11000011;
	cpu.op_set(4, A);
	EXPECT_EQ(A, 0b11010011);
}
TEST(CPU, op_res01)
{
	CPU cpu;

	A = 0b11111111;
	cpu.op_res(4, A);
	EXPECT_EQ(A, 0b11101111);
}

TEST(CPU, op_sbc01)	
{
	CPU cpu;

	A = 0b00111111;
	B = 0b0;
	F.set_carry(0);
	cpu.op_sbc(A, B);
	EXPECT_EQ(A, 0b00111111);
	F.set_carry(0);
	A = 0b00111111;
	B = 0b111;
	cpu.op_sbc(A, B);
	EXPECT_EQ(A, 0b00111000);

	
}
TEST(CPU, op_adc01)
{
	CPU cpu;

	A = 0b00111100;
	B = 0b10;
	F.set_carry(0);
	cpu.op_adc(A, B);
	EXPECT_EQ(A, 0b00111110);
}
TEST(CPU, run_opcode_0x03)
{
	CPU cpu;

	BC = 60000;
	cpu.execute_opcode(0x03);
	EXPECT_EQ(BC, 60001);
}



TEST(CPU, run_cb_opcode_0x10)
{
	CPU cpu;

	B = 0b00001111;

	cpu.execute_cb_opcode(0x10);
	EXPECT_EQ(B, 0b00011110);
}


TEST(CPU, run_cb_opcode_0x18)
{
	CPU cpu;

	B = 0b00001111;

	cpu.execute_cb_opcode(0x18);
	EXPECT_EQ(B, 0b10000111);
}
