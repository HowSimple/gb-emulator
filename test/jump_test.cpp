#include "pch.h"
#include "Gameboy.h"
TEST(Gameboy, push01)
{
	Gameboy gb("Tetris.gb");
	
	gb.push_16b(0xF1FF);
	EXPECT_EQ(gb.read_mem(gb.reg.sp), 0xFF);
	EXPECT_EQ(gb.read_mem(gb.reg.sp+1), 0xF1);
}
TEST(Gameboy, pop01)
{
	Gameboy gb("Tetris.gb");
	gb.push_16b(0xF1FF);

	EXPECT_EQ(gb.pop_16b(), 0xF1FF);
}

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
	
}
TEST(Gameboy, call01)
{
	Gameboy gb("Tetris.gb");
	EXPECT_EQ(gb.reg.pc, 0x100);

	gb.op_call(0x120);
	EXPECT_EQ(gb.pop_16b(), 0x100);
	EXPECT_EQ(gb.reg.pc, 0x120);
}

TEST(Gameboy, ret01)
{
	Gameboy gb("Tetris.gb");
	EXPECT_EQ(gb.reg.pc, 0x100);
	gb.push_16b(0xF1F0);
	gb.op_ret();
	EXPECT_EQ(gb.reg.pc, 0xF1F0);
}
