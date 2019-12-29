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
	reg.a = 0xFF;

	reg.op_inc(reg.a);
	EXPECT_EQ(reg.a, 0);
	EXPECT_EQ(reg.get_carry(), 0);
	EXPECT_EQ(reg.get_zero(), 1);
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
	EXPECT_EQ(reg.get_halfc(), 0);
	EXPECT_EQ(reg.get_zero(), 0);
	EXPECT_EQ(reg.get_sub(), 0);
}

TEST(CPU, swap01)
{
	CPU reg;

	reg.a = 0b00001111;
	reg.op_swap(reg.a);
	EXPECT_EQ(reg.a, 0b11110000);
}

TEST(CPU, ld01)
{
	CPU reg;
	reg.b = 0x4;
	reg.op_ld(reg.a, reg.b);
	EXPECT_EQ(reg.a, 0x4);
}

TEST(CPU, op_swap01)
{
	CPU cpu;
	
	cpu.a = 0b01001111;
	cpu.op_swap(cpu.a);
	EXPECT_EQ(cpu.a, 0b11110100);
}

TEST(CPU, op_rr01)
{
	CPU cpu;
	cpu.f.carry = 0;
	cpu.a = 0b00111111;
	cpu.op_rr(cpu.a);
	EXPECT_EQ(cpu.a, 0b00011111);
}

TEST(CPU, op_rl01)
{
	CPU cpu;

	cpu.a = 0b00111111;
	cpu.op_rl(cpu.a);
	EXPECT_EQ(cpu.a, 0b01111110);
}
TEST(CPU, op_sla01)
{
	CPU cpu;

	cpu.a = 0b10011111;
	cpu.op_sla(cpu.a);
	EXPECT_EQ(cpu.a, 0b00111110);
}
TEST(CPU, op_sla02)
{
	CPU cpu;

	cpu.a = 0b10011111;
	cpu.op_sla(cpu.a);
	EXPECT_EQ(cpu.a, 0b00111110);
	EXPECT_EQ(cpu.f.carry, 1);

}
TEST(CPU, op_sra01)
{
	CPU cpu;

	cpu.a = 0b00111111;
	cpu.op_sra(cpu.a);
	EXPECT_EQ(cpu.a, 0b00011111);
}
TEST(CPU, op_sra02)
{
	CPU cpu;

	cpu.a = 0b00111111;
	cpu.op_sra(cpu.a);
	EXPECT_EQ(cpu.a, 0b00011111);
	EXPECT_EQ(cpu.f.carry, 1);
}
TEST(CPU, op_set01)
{
	CPU cpu;

	cpu.a = 0b11000011;
	cpu.op_set(4, cpu.a);
	EXPECT_EQ(cpu.a, 0b11010011);
}
TEST(CPU, op_res01)
{
	CPU cpu;

	cpu.a = 0b11111111;
	cpu.op_res(4, cpu.a);
	EXPECT_EQ(cpu.a, 0b11101111);
}

TEST(CPU, op_sbc01)	
{
	CPU cpu;

	cpu.a = 0b00111111;
	cpu.b = 0b0;
	cpu.f.carry = 0;
	cpu.op_sbc(cpu.a, cpu.b);
	EXPECT_EQ(cpu.a, 0b00111111);
	cpu.f.carry = 0;
	cpu.a = 0b00111111;
	cpu.b = 0b111;
	cpu.op_sbc(cpu.a, cpu.b);
	EXPECT_EQ(cpu.a, 0b00111000);

	
}
TEST(CPU, op_adc01)
{
	CPU cpu;

	cpu.a = 0b00111100;
	cpu.b = 0b10;
	cpu.f.carry = 0;
	cpu.op_adc(cpu.a, cpu.b);
	EXPECT_EQ(cpu.a, 0b00111110);
}
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
