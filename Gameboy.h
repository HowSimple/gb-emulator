#pragma once
#include "CPU.h"
#include <iostream>
#include <cstdint>
#include<vector>
#include<string>
#include<fstream>
#include<iterator>

 
typedef unsigned char u1;
typedef uint8_t u8;
typedef uint16_t u16;


class Gameboy : CPU
{
	public: 
		Gameboy(std::string filename);
		Gameboy();
		u1 screen[160][144][3];
		std::vector<u1> cart;
		void load_cartridge(std::string filename);
		void display_cartridge();

		
	
};
