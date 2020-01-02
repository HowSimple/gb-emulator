#include "pch.h"
#include "Gameboy.h"


std::string path_to_test_ROM = "cpu_instrs.gb"; // test ROM from https://gbdev.gg8.se/files/roms/blargg-gb-tests/cpu_instrs.zip
std::string path_to_Tetris_ROM = "Tetris.gb";
TEST(Gameboy, loadcart01)
{
	
	Gameboy gb(path_to_test_ROM);
	
	//ASSERT_TRUE(gb.cart.size() > 0);
	EXPECT_EQ(gb.cart[0], 0x3C);
	EXPECT_EQ(gb.cart[1], 0xC9);
	EXPECT_EQ(gb.cart[290], 0xD9);
	EXPECT_EQ(gb.cart[285], 0xCC);
	EXPECT_EQ(gb.cart[17], 0xC9);
	EXPECT_EQ(gb.cart[59377], 0xC9);
	EXPECT_EQ(gb.cart[65535], 0x00);

	//EXPECT_EQ(gb.cart[512], 71);

}

TEST(Gameboy, loadram01)
{

	Gameboy gb(path_to_Tetris_ROM);

	//ASSERT_TRUE(gb.cart.size() > 0);
	EXPECT_EQ(gb.cart[0], 0xC3);
	EXPECT_EQ(gb.cart[1], 0x8B);
	EXPECT_EQ(gb.cart[29493], 0x06);
	EXPECT_EQ(gb.cart[32757], 0x69);
	EXPECT_EQ(gb.cart[32767], 0x00);

	//EXPECT_EQ(gb.cart[512], 71);

}

