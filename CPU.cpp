#include"CPU.h"
#include <iostream>
#include <iomanip>
#include <cstdint>

void CPU::push_16b(u16 value)
{
	reg.sp--;
	write_mem(reg.sp, (value & 0x00FF));
	reg.sp--;
	write_mem(reg.sp, value >> 8);


}
u16 CPU::pop_16b()
{
	
	u16 value = read_mem(reg.sp--) << 8;
	value |= read_mem(reg.sp--);
	reg.sp += 2;
	return value;
	
}
void CPU::write_mem_16(u16 address, u16 value)
{
	u8 low = (value & 0xFF);
	write_mem(address, (low));
	u8 high = ((value & 0xFF00) >> 8);
	write_mem(address + 1, high);
}
void CPU::write_mem(u16 address, u8 value)
{
	// read only address range
	if ((address < 0x8000))
	{
		ram[address] = value;
	}
	// 'Echo RAM' address range
	else if ((address >= 0xE000) && (address < 0xFE00))
	{
		ram[address] = value;
		write_mem(address - 0x2000, value);
	}
	// scanline
	else if (address == 0xFF44)
	{
		ram[address] = 0;
	}
	// LCD control register address, forward to GPU
	else if (address == 0xFF40)
		gpu.update_lcdc(value);
	else if (address == 0xFF41)
		gpu.update_lcdstat(value);
	else if (address == 0xFF42)
		gpu.bg_start.x = value;
	else if (address == 0xFF43)
		gpu.bg_start.y = value;
	else if (address == 0xFF44)
		gpu.current_scanline_y = 0;
	else if (address == 0xFF45)
		gpu.lyc = value;
	else if (address == 0xFF47)
		gpu.set_bg_palette(value);
	else if (address == 0xFF48)
		gpu.sprite0_palette_reg = value;
	else if (address == 0xFF49)
		gpu.sprite1_palette_reg = value;
	else if (address == 0xFF4A)
		gpu.win_start.y = value + 7;
	else if (address == 0xFF4B)
		gpu.win_start.x = value;
	//	Video RAM address range
	else if ((address >= 0x8000) && (address <= 0x9FFF))
		gpu.update_vram(address, value);
	// restricted address range
	//else if ((address >= 0xFEA0) && (address < 0xFEFF))
	//{
	//	return;
	//}	
	// standard address range
	else ram[address] = value;
}

u8& CPU::read_mem(u16 address)
{	// Timer address
	 if (address == 0xFF06)
	{	// TODO: implement timer 
		
		std::cout << "TIMER CALL\n";
		return ram[address];
	}
	
	 if (address == 0xFF04)
	 {
		 ram[address] = rand();
		 std::cout << "RAND CALL\n";
		 return ram[address];
	 }
	 else if (address == 0xFF41)
	 {
		 ram[address] = gpu.read_lcdstat();
		 return ram[address];
	 }
	 else if (address == 0xFF42)
		 return gpu.bg_start.x;
	 else if (address == 0xFF43)
		 return gpu.bg_start.y;
	 else if (address == 0xFF44)
		 return gpu.current_scanline_y;
	 else if (address == 0xFF47)
		 return gpu.bg_palette_reg;
	 else if (address == 0xFF48)
		 return gpu.sprite0_palette_reg;
	 else if (address == 0xFF49)
		 return gpu.sprite1_palette_reg;

	else return ram[address];
}

u16 CPU::get_word()	// get 16-bit immediate value from RAM
{
	u8 low = get_byte();
	u8 high = get_byte();
	u16 value = high << 8;
	value |= low;
	return value;
}
s8 CPU::get_signed_byte() // get signed 8-bit immediate value from RAM
{
	s8 byte = read_mem(reg.pc++);
	std::cout << std::hex << (byte & 0xFF) << " ";
	return byte;
}

void CPU::write_imm_16(u16 value)
{
	u8 high = value >> 8;
	u8 low = value & 0xFF;
	write_mem(reg.pc++, high);
	write_mem(reg.pc++, low);
}
void CPU::write_imm_8(u8 value)
{
	write_mem(reg.pc++, value);
}
u8 CPU::get_byte()// get 8-bit immediate value from RAM
{
	
	u8 byte = read_mem(reg.pc++);
	std::cout << std::hex<< static_cast<int>(byte) << " ";
	return byte;
}
