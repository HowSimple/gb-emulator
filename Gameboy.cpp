#include "Gameboy.h"
#include<cstring>
#include <iterator>
#include <stdexcept>
void Gameboy::load_cartridge(std::string filename)
{
	std::ifstream file(filename, std::ios::binary);
	file.unsetf(std::ios::skipws);
	file.seekg(0, std::ios::end); 
	std::streampos size = file.tellg();
	file.seekg(0, std::ios::beg);
	
	std::vector<u8> bytes;
	bytes.reserve(size);
	bytes.insert(bytes.begin(), std::istream_iterator<u8>(file), std::istream_iterator<u8>());
	cart_size = bytes.size();
	cart = bytes;
	file.close();
}


void Gameboy::load_ram()
{
	for (auto it = ram.rbegin(); it != ram.rbegin(); ++it)
	ram[*it] = 0;		// initialize RAM to zero

	for (auto it = cart.begin(); it != cart.begin()+0x3FFF; ++it)
		ram[*it] = cart[*it];	
	set_cart_type();
	//
	//if (mode == OFF)
	//for (auto i = 0x3FFF; i < 0x7FFF && i < cart.size(); i++)
	//	ram[i] = cart[i];
	

}
void Gameboy::load_boot_rom()
{		
	reg.pc = 0x100;
	reg.af = 0x01B0;
	reg.bc = 0x0013;
	reg.de = 0x00D8;
	reg.hl = 0x014D;
	
	// // load boot ROM to RAM http://bgb.bircd.org/pandocs.htm#powerupsequence
	ram[0xFF05] = 0x00;		
	ram[0xFF06] = 0x00;
	ram[0xFF07] = 0x00;
	ram[0xFF10] = 0x80;
	ram[0xFF11] = 0xBF;
	ram[0xFF12] = 0xF3;
	ram[0xFF14] = 0xBF;
	ram[0xFF16] = 0x3F;
	ram[0xFF17] = 0x00;
	ram[0xFF19] = 0xBF;
	ram[0xFF1A] = 0x7F;
	ram[0xFF1B] = 0xFF;
	ram[0xFF1C] = 0x9F;
	ram[0xFF1E] = 0xBF;
	ram[0xFF20] = 0xFF;
	ram[0xFF21] = 0x00;
	ram[0xFF22] = 0x00;
	ram[0xFF23] = 0xBF;
	ram[0xFF24] = 0x77;
	ram[0xFF25] = 0xF3;
	ram[0xFF26] = 0xF1;
	ram[0xFF40] = 0x91;
	ram[0xFF42] = 0x00;
	ram[0xFF43] = 0x00;
	ram[0xFF45] = 0x00;
	ram[0xFF47] = 0xFC;
	ram[0xFF48] = 0xFF;
	ram[0xFF49] = 0xFF;
	ram[0xFF4A] = 0x00;
	ram[0xFF4B] = 0x00;
	ram[0xFFFF] = 0x00;
}
void Gameboy::set_cart_type()
{
	switch (ram[0x147])
	{
	case 1: mode = rom_bank::MBC1;
	case 2: mode = rom_bank::MBC1;
	case 3: mode = rom_bank::MBC1;
	case 5: mode = rom_bank::MBC2;
	case 6: mode = rom_bank::MBC2;
	default: mode = rom_bank::OFF;
	}
	if (mode != rom_bank::OFF)
	{
		throw std::logic_error("Requested ROM bank mode not yet implemented");
	}
	if (has_cart_ram || has_cart_battery)
	{
		throw std::logic_error("Requested ROM hardware not yet implemented");
	}
}

Gameboy::Gameboy(std::string filename)
{
	ram.resize(0xFFFF);
	//load_boot_rom();
	load_cartridge(filename);
	load_ram();
	
	
}

Gameboy::Gameboy()
{
	ram.resize(0xFFFF);
	//ram.reserve(0xFFFF);
	//cart.reserve(0x200000);
}

