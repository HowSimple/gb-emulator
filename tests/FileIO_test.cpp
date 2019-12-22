#include "pch.h"
#include "Gameboy.h"
#include<string>

std::string path_to_test_ROM = "test.gb";

TEST(Gameboy, loadcart01)
{

	Gameboy gb(path_to_test_ROM);
	gb.display_cartridge();

}
