#pragma once
#include "CPU.h"
#include <cstdint>
#include<vector>
#include<string>
#include<fstream>

 
typedef uint8_t u8;
typedef uint16_t u16;
enum interrupt { vblank = 0, lcdstat = 1, timer = 2, serial = 3, joypad = 4 };


class Gameboy : public CPU
{
public:
	Gameboy(std::string filename);
	Gameboy();
	 std::vector<u8> cart;
	
	int cart_size;
	enum class rom_bank { MBC1, MBC2, MBC3, MBC4, MBC5, OFF } mode;
	bool has_cart_battery;
	bool has_cart_ram;
	
	void load_cartridge(std::string filename);

	void load_ram();
	void load_boot_rom();
	void set_cart_type();

	
	void request_interrupt(interrupt x);

};
