#include "pch.h"
#include "Gameboy.h"
#include<string>
#include<iostream>

std::string path_to_test_ROM = "cpu_instrs.gb"; // test ROM from https://gbdev.gg8.se/files/roms/blargg-gb-tests/cpu_instrs.zip

TEST(Gameboy, loadcart01)
{
	
	Gameboy gb(path_to_test_ROM);
	
	ASSERT_TRUE(gb.cart.size() > 0);
	EXPECT_EQ(gb.cart[1], 0xC9);
	EXPECT_EQ(gb.cart[17], 0xC9);
	EXPECT_EQ(gb.cart[512], 71);

}
