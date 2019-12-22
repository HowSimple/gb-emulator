#include "Gameboy.h"

void Gameboy::load_cartridge(std::string filename)
{

	

}
void Gameboy::display_cartridge()
{
	for (auto i = cart.begin(); i != cart.end(); i++)
		std::cout << *i << ' ';
}
void Gameboy::initialize_ram()
{
	if (cart[0x147] >= 1 && cart[0x147] <= 3)
		mode = MBC1;
	else if (cart[0x147] == 5 || cart[0x147] == 6)
		mode = MBC2;
	else mode = OFF;
	for (auto i : cart)
	{
		if (i >= 0 ) 
	}
	for (auto i = 0; i < 0x3FFF && i < cart.size(); i++)
		ram[i] = cart[i];

}

Gameboy::Gameboy(std::string filename)
{
	//load_cartridge(filename);
	std::ifstream file(filename, std::ios::binary);
	file.skipws;
	u1 byte;
	file >> byte;
	while (!file.eof())
	{
		cart.push_back(byte);
		file >> byte;
	}
	
	initialize_ram();
}

Gameboy::Gameboy()
{
}
