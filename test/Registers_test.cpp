#include "pch.h"
#include "Registers.h"



	TEST(Registers, flags01)
	{
		Registers reg;
		EXPECT_EQ(reg.get_carry(), false);
		EXPECT_EQ(reg.get_sub(), false);
		EXPECT_EQ(reg.get_halfc(), false);
		EXPECT_EQ(reg.get_zero(), false);
	}
	TEST(Registers, flags02)
	{
		Registers reg;
		reg.set_carry(true);
		reg.set_zero(true);
		reg.set_halfc(true);
		reg.set_sub(true);
		EXPECT_EQ(reg.get_carry(), true);
		EXPECT_EQ(reg.get_sub(), true);
		EXPECT_EQ(reg.get_halfc(), true);
		EXPECT_EQ(reg.get_zero(), true);
	}
	TEST(Registers, add01)
	{
		Registers reg;

		reg.a = 0b00000110;
		reg.b = 0b00000001;
		reg.op_add(reg.a, reg.b);
		EXPECT_EQ(reg.a, 7);
	}
	TEST(Registers, add02_carry)
	{
		Registers reg;
		reg.a = 0xFF;
		reg.b = 0x1;

		reg.op_add(reg.a, reg.b);
		EXPECT_EQ(reg.a, 0x0);
		EXPECT_EQ(reg.get_carry(), 1);
	}
	TEST(Registers, sub01)
	{
		Registers reg;
		reg.a = 0x8;
		reg.b = 0x4;

		reg.op_sub(reg.a, reg.b);
		EXPECT_EQ(reg.a, 0x4);
	}
	TEST(Registers, sub01f)
	{
		Registers reg;
		reg.a = 0x8;
		reg.b = 0x4;

		reg.op_sub(reg.a, reg.b);
		EXPECT_EQ(reg.a, 0x4);

		EXPECT_EQ(reg.get_carry(), 0);
		EXPECT_EQ(reg.get_halfc(), 0);
	}
	TEST(Registers, inc01)
	{
		Registers reg;
		reg.a = 6;

		reg.op_inc(reg.a);
		EXPECT_EQ(reg.a, 7);

	}

	TEST(Registers, inc02)
	{
		Registers reg;
		reg.a = 8;
		reg.b = 4;

		reg.op_inc(reg.a);
		EXPECT_EQ(reg.a, 9);
		EXPECT_EQ(reg.get_carry(), 0);
		EXPECT_EQ(reg.get_zero(), 0);
		EXPECT_EQ(reg.get_halfc(), 0);


	}
	TEST(Registers, dec01)
	{
		Registers reg;
		reg.a = 8;

		reg.op_dec(reg.a);
		EXPECT_EQ(reg.a, 7);
	}
	TEST(Registers, dec02)
	{
		Registers reg;
		reg.a = 8;

		reg.op_dec(reg.a);
		EXPECT_EQ(reg.a, 7);
	}
	TEST(Registers, and01)
	{
		Registers reg;
		reg.a = 0b00101110;
		reg.b = 0b11101010;

		reg.op_and(reg.a, reg.b);
		EXPECT_EQ(reg.a, 0b00101010);

		EXPECT_EQ(reg.get_carry(), 0);
		EXPECT_EQ(reg.get_halfc(), 1);


	}

	TEST(Registers, or01)
	{
		Registers reg;
		reg.a = 0b00001110;
		reg.b = 0b11100000;

		reg.op_or(reg.a, reg.b);
		EXPECT_EQ(reg.a, 0b11101110);
	}
	TEST(Registers, or01F)
	{
		Registers reg;
		reg.a = 0b00001110;
		reg.b = 0b11100000;

		reg.op_or(reg.a, reg.b);
		EXPECT_EQ(reg.a, 0b11101110);
		EXPECT_EQ(reg.get_zero(), 0);
	
	}
	
	TEST(Registers, xor01)
	{
		Registers reg;
		reg.a = 0b01101110;
		reg.b = 0b11101100;

		reg.op_xor(reg.a, reg.b);
		EXPECT_EQ(reg.a, 0b10000010);
	}

	TEST(Registers, xor01f)
	{
		Registers reg;
		reg.a = 0b01101110;
		reg.b = 0b11101100;

		reg.op_xor(reg.a, reg.b);
		EXPECT_EQ(reg.a, 0b10000010);

		EXPECT_EQ(reg.get_carry(), 0);
		EXPECT_EQ(reg.get_halfc(), 1);
	}

	TEST(Registers, swap01)
	{
		Registers reg;

		reg.a = 0b00000110;
		reg.op_swap(reg.a);
		EXPECT_EQ(reg.a, 0b01100000);
	}
	
	TEST(Registers, ld01)
	{
			Registers reg;
			reg.b = 0x4;
			reg.op_ld(reg.a, reg.b);
			EXPECT_EQ(reg.a, 0x4);
	}
	TEST(Registers, ld02)
	{
		Registers reg;
		reg.op_ld(reg.bc, 0b11111111);
		EXPECT_EQ(reg.bc, 0b11111111);
		reg.op_ld(reg.de, 0b11000111);
		EXPECT_EQ(reg.de, 0b11000111);
	}
	/*TEST(Registers, ld03)
	{
		Registers reg;
		reg.op_ld(reg.af, 0b11111111);
		EXPECT_EQ(reg.af, 0b11111111);
		reg.op_ld(reg.af, 0b11000111);
		EXPECT_EQ(reg.af, 0b11000111);
	}
	*/