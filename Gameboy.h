#pragma once
#include "Registers.h"
#include <iostream>
#include <cstdint>
#include<vector>
#include<string>
#include<fstream>
#include<iterator>

 
typedef unsigned char u1;
typedef uint8_t u8;
typedef uint16_t u16;
enum rom_bank { MBC1, MBC2, OFF };

class Gameboy
{
	public: 
		Gameboy(std::string filename);
		Gameboy();
		u1 screen[160][144][3];
		std::vector<u1> cart;
		u1 ram[8192];
		Registers regs;
		void load_cartridge(std::string filename);
		void display_cartridge();
	private:
		
		
		rom_bank mode;

		
		void initialize_ram();
		void fetch_instruction();
	

};
