#include "Gameboy.h"

void Gameboy::load_cartridge(std::string filename)
{
	/*std::ifstream cart(filename);
	std::vector<u8> bytes;
	u8 byte;
	while (cart >> byte)
	{
		bytes.push_back(byte);
	}*/
	std::ifstream file(filename, std::ios::binary);
	std::vector<char> bytes((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
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

	for (int i = 0; i < 0x3FFF && i < cart.size(); i++)
		ram[i] = cart[i];

}

Gameboy::Gameboy(std::string filename)
{
	load_cartridge(filename);
	//initialize_ram();
}

Gameboy::Gameboy()
{
}
