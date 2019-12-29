#pragma once
#include "CPU.h"
#include <iostream>
#include <cstdint>
#include<vector>
#include<string>
#include<fstream>

 
typedef uint8_t u8;
typedef uint16_t u16;


class Gameboy : CPU
{
public:
	Gameboy(std::string filename);
	Gameboy();
	u8 screen[160][144][3];
	std::vector<u8> cart;
	int cart_size;
	void load_cartridge(std::string filename);
		

		
	
};
