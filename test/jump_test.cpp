#include "pch.h"
#include "Gameboy.h"


TEST(Gameboy, jp01)
{
	Gameboy gb("Tetris.gb");
	EXPECT_EQ(gb.reg.pc, 0x100);
	gb.op_jp(0x0200);
	EXPECT_EQ(gb.reg.pc, 0x200);
}

TEST(Gameboy, jr01)
{
	Gameboy gb("Tetris.gb");
	EXPECT_EQ(gb.reg.pc, 0x100);
	
	gb.op_jr(0x64);
	EXPECT_EQ(gb.reg.pc, 0x164);
}


TEST(Gameboy, rst01)
{
	Gameboy gb("Tetris.gb");
	gb.op_jp(0x667F);
	EXPECT_EQ(gb.reg.pc, 0x667F);
	gb.op_rst(0x38);
	EXPECT_EQ(gb.reg.pc, 0x38);
	EXPECT_EQ(gb.pop_16b(), 0x677F);
	//EXPECT_EQ(gb.read_mem(gb.reg.sp-1), 0b01100110);
	//EXPECT_EQ(gb.read_mem(gb.reg.sp-2), 0b01110000);
	
}