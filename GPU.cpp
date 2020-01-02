#include "GPU.h"

GPU::tile& GPU::get_tile(u8 address)
{
	
	u16 offset;
	const u8 tile_size = 16;
	return tile_set2[address/tile_size];
}

void GPU::update_lcdc(u8 lcdreg)
{	//ram[0xFF40]
	LCD_ENABLE			  = (lcdreg << 7)& 1;
	SPRITE_ENABLE		  = (lcdreg << 6)& 1;
	SPRITE_SIZE			  = (lcdreg << 5)& 1;
	BG_TILE_MAP			  = (lcdreg << 4)& 1;
	BGWINDOW_TILE_MAP	  = (lcdreg << 3)& 1;
	WINDOW_DISPLAY_ENABLE = (lcdreg << 2)& 1;
	LCD_ENABLE			  = (lcdreg << 1)& 1;
}
void GPU::update_vram(u16 address, u8 value)
{

}
void GPU::update_background()
{
	for (auto x = 0; x < 256; x++)
		for (auto y = 0; y < 256; y++)
		{
			//screen[x][y] = 
			int16_t address = vram[0x9800 - VRAM_BEGIN];
			u8 offset;
			background[x][y] = 
			
			if (BG_TILE_MAP)
			{
				offset = 255;
			}
			else
			{
				offset = 0;
			}

			background[x][y] = 0;
			if (WINDOW_TILE_MAP)
			{
				offset = 255;
			}
			else
			{

			}
		};
}

void GPU::render_tiles()
{
	if (BG_DISPLAY_ENABLE)
		for (auto x = 0; x < 255; x++)
			for (auto y = 0; y < 255; y++)
			{

			}
	if (WINDOW_DISPLAY_ENABLE)
		for (auto x = window_x; x < 255; x++)
			for (auto y = window_y; y < 255; y++)
			{

			}
	

	if (SPRITE_ENABLE)
	{
	};
			
			
			
			
			
			
			
			
			

			
			
			
			
			
			
			
			
			
			
		}
			
}

void GPU::update_tiles()
{
	
	for (auto ti = 0; ti < 0x800; ti += 2)
	{
		u8 byte1 = vram[ti];
		u8 byte2 = vram[ti + 1];
		
		for (auto rw = 0; rw < 7; rw++)
			for (auto px = 0; px < 7; px++)
				tile_set1[ti].row[rw].pixel[px] = static_cast<color>((byte1 << 7) | (byte2 << 7) << 1);
	}
	for (auto ti = 0x800; ti < 0x17FF; ti += 2)
	{
		u8 byte1 = vram[ti];
		u8 byte2 = vram[ti + 1];

		for (auto rw = 0; rw < 7; rw++)
			for (auto px = 0; px < 7; px++)
				tile_set2[ti].row[rw].pixel[px] = static_cast<color>((byte1 << 7) | (byte2 << 7) << 1);
	}
}

void GPU::render_screen()
{

}
