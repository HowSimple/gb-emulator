#include "pch.h"
#include "CPU.h"

TEST(CPU, add01)
{
	CPU cpu;

	cpu.a = 0b00000110;
	cpu.b = 0b00000001;
	cpu.op_add(cpu.a, cpu.b);
	EXPECT_EQ(cpu.a, 7);
}
TEST(CPU, add02_carry)
{
	CPU reg;
	reg.a = 0xFF;
	reg.b = 0x1;

	reg.op_add(reg.a, reg.b);
	EXPECT_EQ(reg.a, 0x0);
	EXPECT_EQ(reg.get_carry(), 1);
}
TEST(CPU, sub01)
{
	CPU reg;
	reg.a = 0x8;
	reg.b = 0x4;

	reg.op_sub(reg.a, reg.b);
	EXPECT_EQ(reg.a, 0x4);
}
TEST(CPU, sub01f)
{
	CPU reg;
	reg.a = 0x8;
	reg.b = 0x4;

	reg.op_sub(reg.a, reg.b);
	EXPECT_EQ(reg.a, 0x4);

	EXPECT_EQ(reg.get_carry(), 0);
	EXPECT_EQ(reg.get_halfc(), 0);
}
TEST(CPU, inc01)
{
	CPU reg;
	reg.a = 6;

	reg.op_inc(reg.a);
	EXPECT_EQ(reg.a, 7);

}

TEST(CPU, inc02)
{
	CPU reg;
	reg.a = 8;
	reg.b = 4;

	reg.op_inc(reg.a);
	EXPECT_EQ(reg.a, 9);
	EXPECT_EQ(reg.get_carry(), 0);
	EXPECT_EQ(reg.get_zero(), 0);
	EXPECT_EQ(reg.get_halfc(), 0);


}
TEST(CPU, dec01)
{
	CPU reg;
	reg.a = 8;

	reg.op_dec(reg.a);
	EXPECT_EQ(reg.a, 7);
}
TEST(CPU, dec02)
{
	CPU reg;
	reg.a = 8;

	reg.op_dec(reg.a);
	EXPECT_EQ(reg.a, 7);
}
TEST(CPU, and01)
{
	CPU reg;
	reg.a = 0b00101110;
	reg.b = 0b11101010;

	reg.op_and(reg.b);
	EXPECT_EQ(reg.a, 0b00101010);

	EXPECT_EQ(reg.get_carry(), 0);
	EXPECT_EQ(reg.get_halfc(), 1);


}

TEST(CPU, or01)
{
	CPU reg;
	reg.a = 0b00001110;
	reg.b = 0b11100000;

	reg.op_or(reg.b);
	EXPECT_EQ(reg.a, 0b11101110);
}
TEST(CPU, or01F)
{
	CPU reg;
	reg.a = 0b00001110;
	reg.b = 0b11100000;

	reg.op_or(reg.b);
	EXPECT_EQ(reg.a, 0b11101110);
	EXPECT_EQ(reg.get_zero(), 0);

}

TEST(CPU, xor01)
{
	CPU reg;
	reg.a = 0b01101110;
	reg.b = 0b11101100;

	reg.op_xor(reg.b);
	EXPECT_EQ(reg.a, 0b10000010);
}

TEST(CPU, xor01f)
{
	CPU reg;
	reg.a = 0b01101110;
	reg.b = 0b11101100;

	reg.op_xor(reg.b);
	EXPECT_EQ(reg.a, 0b10000010);

	EXPECT_EQ(reg.get_carry(), 0);
	EXPECT_EQ(reg.get_halfc(), 1);
}

TEST(CPU, swap01)
{
	CPU reg;

	reg.a = 0b00000110;
	reg.op_swap(reg.a);
	EXPECT_EQ(reg.a, 0b01100000);
}

TEST(CPU, ld01)
{
	CPU reg;
	reg.b = 0x4;
	reg.op_ld(reg.a, reg.b);
	EXPECT_EQ(reg.a, 0x4);
}
TEST(CPU, ld02)
{
	CPU reg;
	u16 value1 = 0b11111111;
	u16 value2 = 0b11000111;
	reg.op_ld(reg.bc, value1);
	EXPECT_EQ(reg.bc, value1);
}


TEST(CPU, ld03)	// test AF behavior
{
	CPU cpu;
	u16 value1 = 0b11111111;
	cpu.op_ld(cpu.af, value1);
	EXPECT_EQ(cpu.af, 0b11110000);
}


/*
TEST(CPU, swap01)
{
	CPU cpu;
	cpu.a = 0b11000000;
	cpu.op_swap(cpu.a);
	EXPECT_EQ(cpu.a, 0b00001100);
}
*/

/*
TEST(CPU, swap02)
{
	CPU cpu;
	
	cpu.hl = 0b1111000000001101;
	cpu.op_swap(cpu.ram[cpu.hl]);
	EXPECT_EQ(cpu.bc, 0b00001100);
}
*/

TEST(CPU, run_opcode_0x03)
{
	CPU cpu;

	cpu.bc = 60000;
	cpu.execute_opcode(0x03);
	EXPECT_EQ(cpu.bc, 60001);
}



TEST(CPU, run_cb_opcode_0x10)
{
	CPU cpu;

	cpu.b = 0b00001111;

	cpu.execute_cb_opcode(0x10);
	EXPECT_EQ(cpu.b, 0b00011110);
}


TEST(CPU, run_cb_opcode_0x18)
{
	CPU cpu;

	cpu.b = 0b00001111;

	cpu.execute_cb_opcode(0x18);
	EXPECT_EQ(cpu.b, 0b10000111);
}
