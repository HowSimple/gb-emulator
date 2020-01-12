#include "pch.h"
#include "Gameboy.h"
#include "GPU.h"
#include <vector>

TEST(GPU, get_tile_color01)
{
	u8 high = 0b10101110;
	u8 low = 0b00110101;

	EXPECT_EQ(2, GPU::get_color(7, high, low));
	EXPECT_EQ(0, GPU::get_color(6, high, low));
	EXPECT_EQ(3, GPU::get_color(5, high, low));
	EXPECT_EQ(1, GPU::get_color(4, high, low));
	EXPECT_EQ(2, GPU::get_color(3, high, low));
	EXPECT_EQ(3, GPU::get_color(2, high, low));
	EXPECT_EQ(2, GPU::get_color(1, high, low));
	EXPECT_EQ(1, GPU::get_color(0, high, low));
	
	
}
TEST(GPU, get_tile_id01)
{
	std::vector<u8> ram(0xFFFF);
	GPU gpu(ram);
	const u16 LCDCONTROL = 0xFF40;
	// bit 3 selects tile map at [0x9C00, 0x9FFF]. 
	// bit 4 selects tile set at [0x8000, 0x8FFF]. 
	// tile ID is unsigned byte from 0 to 255 on this tile set
	ram.at(LCDCONTROL) = 0b10011000; 

	ram.at(0x9C00) = 240; // setting first tile ID in map
	u16 tile_id = gpu.get_tile_id(0, 0); // x: 0, y: 0, to get the tile ID set above
	EXPECT_EQ(240, tile_id);



}
TEST(GPU, get_tile_id02)
{
	std::vector<u8> ram(0xFFFF);
	GPU gpu(ram);
	const u16 LCDCONTROL = 0xFF40;
	// bit 3 selects tile map at [0x9C00, 0x9FFF]. 
	// bit 4 selects tile set at [0x8000, 0x8FFF]. 
	// tile ID is unsigned byte from 0 to 255 on this tile set
	ram.at(LCDCONTROL) = 0b10011000;

	ram.at(0x9C00) = 240; // setting first tile ID in map
	u16 tile_id = gpu.get_tile_id(5, 0); // x: 0, y: 0, to get the tile ID set above
	EXPECT_EQ(240, tile_id);



}
TEST(GPU, get_tile_id03)
{
	std::vector<u8> ram(0xFFFF);
	GPU gpu(ram);
	const u16 LCDCONTROL = 0xFF40;
	// bit 3 selects tile map at [0x9C00, 0x9FFF]. 
	// bit 4 selects tile set at [0x8800, 0x97FF]. 
	// tile ID is signed byte from -127 to 128 on this tile set
	ram.at(LCDCONTROL) = 0b10001000; 

	ram.at(0x9C00) = -100; // setting first tile ID in map
	u16 tile_id = gpu.get_tile_id(0, 0); // x: 0, y: 0, to get the tile ID set above
	EXPECT_EQ(156, tile_id);


}
TEST(GPU, get_tile_address01)
{
	std::vector<u8> ram(0xFFFF);
	GPU gpu(ram);
	const u16 LCDCONTROL = 0xFF40;

	// bit 3 selects tile map at [0x9C00, 0x9FFF]. 
	// bit 4 selects tile set at [0x8000, 0x8FFF]. 
	// tile ID is unsigned byte from 0 to 255 on this tile set
	ram.at(LCDCONTROL) = 0b10011000;

	ram.at(0x9C00) = 240; // setting first tile ID in map
	u16 tile_id = 100; // x: 0, y: 0, to get the tile ID set above
	u16 tile_address = gpu.get_tile_address(tile_id, 0x8000);

	EXPECT_EQ(0x8C80, tile_address);



}