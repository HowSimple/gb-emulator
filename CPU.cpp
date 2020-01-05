#include"CPU.h"
#include <iostream>

void CPU::push_16b(u16 value)
{
	reg.sp--;
	write_mem(reg.sp, value >> 8);
	reg.sp--;
	write_mem(reg.sp, (value & 0x00FF));

}
void CPU::check_lcd()
{

}
u16 CPU::pop_16b()
{
	
	u16 value = read_mem(reg.sp--) | read_mem(reg.sp--) << 8;
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
	else if (address == 0xFF42)
		gpu.bg_start.y = value;
	else if (address == 0xFF43)
		gpu.bg_start.x = value;
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
	if (address == 0xFF06 || address == 0xFF07)
	{	// TODO: implement timer 
		u8 timer = 0;
		std::cout << "TIMER CALL\n";
		return timer;
	}
	//
	else if (address == 0xFF04)
	{
		u8 random_num = rand();
		std::cout << "RAND CALL\n";
		return random_num;
	}
	else return ram[address];
}
u8 CPU::get_imm_8() // get 8-bit immediate value from RAM
{
	return read_mem(reg.pc++);
}
u16 CPU::get_imm_16()	// get 16-bit immediate value from RAM
{
	u16 value = read_mem(reg.pc++);
	value = value << 8;
	value |= (read_mem(reg.pc++));
	
	return value;
}
s8 CPU::get_imm_s8() // get signed 8-bit immediate value from RAM
{
	return read_mem(reg.pc++);
}

void CPU::write_imm_16(u16 value)
{
	u8 high = value << 8;
	u8 low = value >> 8;
	write_mem(reg.pc++, low);
	write_mem(reg.pc, low);
	

}
void CPU::write_imm_8(u8 value)
{
	write_mem(reg.pc, value);
	reg.pc++;
}
u8 CPU::fetch_opcode()
{
	
	u8 opcode = read_mem(reg.pc);
	std::cout << static_cast<int>(opcode) << " ";
	reg.pc++;
	return opcode;
}
void CPU::execute_cb_opcode(u8 opcode)
{
	
	switch (opcode)
	{
	case 0x00: {	op_rlc(reg.b);						cycles += 8; break; }
	case 0x01: {	op_rlc(reg.c);						cycles += 8; break; }
	case 0x02: {	op_rlc(reg.d);						cycles += 8; break; }
	case 0x03: {	op_rlc(reg.e);						cycles += 8; break; }
	case 0x04: {	op_rlc(reg.h);						cycles += 8; break; }
	case 0x05: {	op_rlc(reg.l);						cycles += 8; break; }
	case 0x06: {	op_rlc(read_mem(reg.hl));			cycles += 16; break; }
	case 0x07: {	op_rlc(reg.a);						cycles += 8; break; }
	case 0x08: {	op_rrc(reg.b);						cycles += 8; break; }
	case 0x09: {	op_rrc(reg.c);						cycles += 8; break; }
	case 0x0A: {	op_rrc(reg.d);						cycles += 8; break; }
	case 0x0B: {	op_rrc(reg.e);						cycles += 8; break; }
	case 0x0C: {	op_rrc(reg.h);						cycles += 8; break; }
	case 0x0D: {	op_rrc(reg.l);						cycles += 8; break; }
	case 0x0E: {	op_rrc(read_mem(reg.hl));			cycles += 16; break; }
	case 0x0F: {	op_rrc(reg.a);						cycles += 8; break; }

	case 0x10: {	op_rl(reg.b);						cycles += 8; break; }
	case 0x11: {	op_rl(reg.c);						cycles += 8; break; }
	case 0x12: {	op_rl(reg.d);						cycles += 8; break; }
	case 0x13: {	op_rl(reg.e);						cycles += 8; break; }
	case 0x14: {	op_rl(reg.h);						cycles += 8; break; }
	case 0x15: {	op_rl(reg.l);						cycles += 8; break; }
	case 0x16: {	op_rl(read_mem(reg.hl));			cycles += 16; break; }
	case 0x17: {	op_rl(reg.a);						cycles += 8; break; }
	case 0x18: {	op_rr(reg.b);						cycles += 8; break; }
	case 0x19: {	op_rr(reg.c);						cycles += 8; break; }
	case 0x1A: {	op_rr(reg.d);						cycles += 8; break; }
	case 0x1B: {	op_rr(reg.e);						cycles += 8; break; }
	case 0x1C: {	op_rr(reg.h);						cycles += 8; break; }
	case 0x1D: {	op_rr(reg.l);						cycles += 8; break; }
	case 0x1E: {	op_rr(read_mem(reg.hl));			cycles += 16; break; }
	case 0x1F: {	op_rr(reg.a);						cycles += 8; break; }

	case 0x20: {	op_sla(reg.b);						cycles += 8; break; }
	case 0x21: {	op_sla(reg.c);						cycles += 8; break; }
	case 0x22: {	op_sla(reg.d);						cycles += 8; break; }
	case 0x23: {	op_sla(reg.e);						cycles += 8; break; }
	case 0x24: {	op_sla(reg.h);						cycles += 8; break; }
	case 0x25: {	op_sla(reg.l);						cycles += 8; break; }
	case 0x26: {	op_sla(read_mem(reg.hl));			cycles += 16; break; }
	case 0x27: {	op_sla(reg.a);						cycles += 8; break; }
	case 0x28: {	op_sra(reg.b);						cycles += 8; break; }
	case 0x29: {	op_sra(reg.c);						cycles += 8; break; }
	case 0x2A: {	op_sra(reg.d);						cycles += 8; break; }
	case 0x2B: {	op_sra(reg.e);						cycles += 8; break; }
	case 0x2C: {	op_sra(reg.h);						cycles += 8; break; }
	case 0x2D: {	op_sra(reg.l);						cycles += 8; break; }
	case 0x2E: {	op_sra(read_mem(reg.hl));			cycles += 16; break; }
	case 0x2F: {	op_sra(reg.a);						cycles += 8; break; }

	case 0x30: {	op_swap(reg.b);						cycles += 8; break; }
	case 0x31: {	op_swap(reg.c);						cycles += 8; break; }
	case 0x32: {	op_swap(reg.d);						cycles += 8; break; }
	case 0x33: {	op_swap(reg.e);						cycles += 8; break; }
	case 0x34: {	op_swap(reg.h);						cycles += 8; break; }
	case 0x35: {	op_swap(reg.l);						cycles += 8; break; }
	case 0x36: {	op_swap(read_mem(reg.hl));			cycles += 16; break; }
	case 0x37: {	op_swap(reg.a);						cycles += 8; break; }
	case 0x38: {	op_srl(reg.b);						cycles += 8; break; }
	case 0x39: {	op_srl(reg.c);						cycles += 8; break; }
	case 0x3A: {	op_srl(reg.d);						cycles += 8; break; }
	case 0x3B: {	op_srl(reg.e);						cycles += 8; break; }
	case 0x3C: {	op_srl(reg.h);						cycles += 8; break; }
	case 0x3D: {	op_srl(reg.l);						cycles += 8; break; }
	case 0x3E: {	op_srl(read_mem(reg.hl));			cycles += 16; break; }
	case 0x3F: {	op_srl(reg.a);						cycles += 8; break; }

	case 0x40: {	op_bit(0, reg.b);					cycles += 8; break; }
	case 0x41: {	op_bit(0, reg.c);					cycles += 8; break; }
	case 0x42: {	op_bit(0, reg.d);					cycles += 8; break; }
	case 0x43: {	op_bit(0, reg.e);					cycles += 8; break; }
	case 0x44: {	op_bit(0, reg.h);					cycles += 8; break; }
	case 0x45: {	op_bit(0, reg.l);					cycles += 8; break; }
	case 0x46: {	op_bit(0, read_mem(reg.hl));		cycles += 16; break; }
	case 0x47: {	op_bit(0, reg.a);					cycles += 8; break; }
	case 0x48: {	op_bit(1, reg.b);					cycles += 8; break; }
	case 0x49: {	op_bit(1, reg.c);					cycles += 8; break; }
	case 0x4A: {	op_bit(1, reg.d);					cycles += 8; break; }
	case 0x4B: {	op_bit(1, reg.e);					cycles += 8; break; }
	case 0x4C: {	op_bit(1, reg.h);					cycles += 8; break; }
	case 0x4D: {	op_bit(1, reg.l);					cycles += 8; break; }
	case 0x4E: {	op_bit(1, read_mem(reg.hl));		cycles += 16; break; }
	case 0x4F: {	op_bit(1, reg.a);					cycles += 8; break; }

	case 0x50: {	op_bit(2, reg.b);					cycles += 8; break; }
	case 0x51: {	op_bit(2, reg.c);					cycles += 8; break; }
	case 0x52: {	op_bit(2, reg.d);					cycles += 8; break; }
	case 0x53: {	op_bit(2, reg.e);					cycles += 8; break; }
	case 0x54: {	op_bit(2, reg.h);					cycles += 8; break; }
	case 0x55: {	op_bit(2, reg.l);					cycles += 8; break; }
	case 0x56: {	op_bit(2, read_mem(reg.hl));		cycles += 16; break; }
	case 0x57: {	op_bit(2, reg.a);					cycles += 8; break; }
	case 0x58: {	op_bit(3, reg.b);					cycles += 8; break; }
	case 0x59: {	op_bit(3, reg.c);					cycles += 8; break; }
	case 0x5A: {	op_bit(3, reg.d);					cycles += 8; break; }
	case 0x5B: {	op_bit(3, reg.e);					cycles += 8; break; }
	case 0x5C: {	op_bit(3, reg.h);					cycles += 8; break; }
	case 0x5D: {	op_bit(3, reg.l);					cycles += 8; break; }
	case 0x5E: {	op_bit(3, read_mem(reg.hl));		cycles += 16; break; }
	case 0x5F: {	op_bit(3, reg.a);					cycles += 8; break; }

	case 0x60: {	op_bit(4, reg.b);					cycles += 8; break; }
	case 0x61: {	op_bit(4, reg.c);					cycles += 8; break; }
	case 0x62: {	op_bit(4, reg.d);					cycles += 8; break; }
	case 0x63: {	op_bit(4, reg.e);					cycles += 8; break; }
	case 0x64: {	op_bit(4, reg.h);					cycles += 8; break; }
	case 0x65: {	op_bit(4, reg.l);					cycles += 8; break; }
	case 0x66: {	op_bit(4, read_mem(reg.hl));		cycles += 16; break; }
	case 0x67: {	op_bit(4, reg.a);					cycles += 8; break; }
	case 0x68: {	op_bit(5, reg.b);					cycles += 8; break; }
	case 0x69: {	op_bit(5, reg.c);					cycles += 8; break; }
	case 0x6A: {	op_bit(5, reg.d);					cycles += 8; break; }
	case 0x6B: {	op_bit(5, reg.e);					cycles += 8; break; }
	case 0x6C: {	op_bit(5, reg.h);					cycles += 8; break; }
	case 0x6D: {	op_bit(5, reg.l);					cycles += 8; break; }
	case 0x6E: {	op_bit(5, read_mem(reg.hl));		cycles += 16; break; }
	case 0x6F: {	op_bit(5, reg.a);					cycles += 8; break; }

	case 0x70: {	op_bit(6, reg.b);					cycles += 8; break; }
	case 0x71: {	op_bit(6, reg.c);					cycles += 8; break; }
	case 0x72: {	op_bit(6, reg.d);					cycles += 8; break; }
	case 0x73: {	op_bit(6, reg.e);					cycles += 8; break; }
	case 0x74: {	op_bit(6, reg.h);					cycles += 8; break; }
	case 0x75: {	op_bit(6, reg.l);					cycles += 8; break; }
	case 0x76: {	op_bit(6, read_mem(reg.hl));		cycles += 16; break; }
	case 0x77: {	op_bit(6, reg.a);					cycles += 8; break; }
	case 0x78: {	op_bit(7, reg.b);					cycles += 8; break; }
	case 0x79: {	op_bit(7, reg.c);					cycles += 8; break; }
	case 0x7A: {	op_bit(7, reg.d);					cycles += 8; break; }
	case 0x7B: {	op_bit(7, reg.e);					cycles += 8; break; }
	case 0x7C: {	op_bit(7, reg.h);					cycles += 8; break; }
	case 0x7D: {	op_bit(7, reg.l);					cycles += 8; break; }
	case 0x7E: {	op_bit(7, read_mem(reg.hl));		cycles += 16; break; }
	case 0x7F: {	op_bit(7, reg.a);					cycles += 8; break; }

	case 0x80: {	op_res(0, reg.b);					cycles += 8; break; }
	case 0x81: {	op_res(0, reg.c);					cycles += 8; break; }
	case 0x82: {	op_res(0, reg.d);					cycles += 8; break; }
	case 0x83: {	op_res(0, reg.e);					cycles += 8; break; }
	case 0x84: {	op_res(0, reg.h);					cycles += 8; break; }
	case 0x85: {	op_res(0, reg.l);					cycles += 8; break; }
	case 0x86: {	op_res(0, read_mem(reg.hl));		cycles += 16; break; }
	case 0x87: {	op_res(0, reg.a);					cycles += 8; break; }
	case 0x88: {	op_res(1, reg.b);					cycles += 8; break; }
	case 0x89: {	op_res(1, reg.c);					cycles += 8; break; }
	case 0x8A: {	op_res(1, reg.d);					cycles += 8; break; }
	case 0x8B: {	op_res(1, reg.e);					cycles += 8; break; }
	case 0x8C: {	op_res(1, reg.h);					cycles += 8; break; }
	case 0x8D: {	op_res(1, reg.l);					cycles += 8; break; }
	case 0x8E: {	op_res(1, read_mem(reg.hl));		cycles += 16; break; }
	case 0x8F: {	op_res(1, reg.a);					cycles += 8; break; }
	case 0x90: {	op_res(2, reg.b);					cycles += 8; break; }
	case 0x91: {	op_res(2, reg.c);					cycles += 8; break; }
	case 0x92: {	op_res(2, reg.d);					cycles += 8; break; }
	case 0x93: {	op_res(2, reg.e);					cycles += 8; break; }
	case 0x94: {	op_res(2, reg.h);					cycles += 8; break; }
	case 0x95: {	op_res(2, reg.l);					cycles += 8; break; }
	case 0x96: {	op_res(2, read_mem(reg.hl));		cycles += 16; break; }
	case 0x97: {	op_res(2, reg.a);					cycles += 8; break; }
	case 0x98: {	op_res(3, reg.b);					cycles += 8; break; }
	case 0x99: {	op_res(3, reg.c);					cycles += 8; break; }
	case 0x9A: {	op_res(3, reg.d);					cycles += 8; break; }
	case 0x9B: {	op_res(3, reg.e);					cycles += 8; break; }
	case 0x9C: {	op_res(3, reg.h);					cycles += 8; break; }
	case 0x9D: {	op_res(3, reg.l);					cycles += 8; break; }
	case 0x9E: {	op_res(3, read_mem(reg.hl));		cycles += 16; break; }
	case 0x9F: {	op_res(3, reg.a);					cycles += 8; break; }
	case 0xA0: {	op_res(4, reg.b);					cycles += 8; break; }
	case 0xA1: {	op_res(4, reg.c);					cycles += 8; break; }
	case 0xA2: {	op_res(4, reg.d);					cycles += 8; break; }
	case 0xA3: {	op_res(4, reg.e);					cycles += 8; break; }
	case 0xA4: {	op_res(4, reg.h);					cycles += 8; break; }
	case 0xA5: {	op_res(4, reg.l);					cycles += 8; break; }
	case 0xA6: {	op_res(4, read_mem(reg.hl));		cycles += 16; break; }
	case 0xA7: {	op_res(4, reg.a);					cycles += 8; break; }
	case 0xA8: {	op_res(5, reg.b);					cycles += 8; break; }
	case 0xA9: {	op_res(5, reg.c);					cycles += 8; break; }
	case 0xAA: {	op_res(5, reg.d);					cycles += 8; break; }
	case 0xAB: {	op_res(5, reg.e);					cycles += 8; break; }
	case 0xAC: {	op_res(5, reg.h);					cycles += 8; break; }
	case 0xAD: {	op_res(5, reg.l);					cycles += 8; break; }
	case 0xAE: {	op_res(5, read_mem(reg.hl));		cycles += 16; break; }
	case 0xAF: {	op_res(5, reg.a);					cycles += 8; break; }
	case 0xB0: {	op_res(6, reg.b);					cycles += 8; break; }
	case 0xB1: {	op_res(6, reg.c);					cycles += 8; break; }
	case 0xB2: {	op_res(6, reg.d);					cycles += 8; break; }
	case 0xB3: {	op_res(6, reg.e);					cycles += 8; break; }
	case 0xB4: {	op_res(6, reg.h);					cycles += 8; break; }
	case 0xB5: {	op_res(6, reg.l);					cycles += 8; break; }
	case 0xB6: {	op_res(6, read_mem(reg.hl));		cycles += 16; break; }
	case 0xB7: {	op_res(6, reg.a);					cycles += 8; break; }
	case 0xB8: {	op_res(7, reg.b);					cycles += 8; break; }
	case 0xB9: {	op_res(7, reg.c);					cycles += 8; break; }
	case 0xBA: {	op_res(7, reg.d);					cycles += 8; break; }
	case 0xBB: {	op_res(7, reg.e);					cycles += 8; break; }
	case 0xBC: {	op_res(7, reg.h);					cycles += 8; break; }
	case 0xBD: {	op_res(7, reg.l);					cycles += 8; break; }
	case 0xBE: {	op_res(7, read_mem(reg.hl));		cycles += 16; break; }
	case 0xBF: {	op_res(7, reg.a);					cycles += 8; break; }

	case 0xC0: {	op_set(0, reg.b);					cycles += 8; break; }
	case 0xC1: {	op_set(0, reg.c);					cycles += 8; break; }
	case 0xC2: {	op_set(0, reg.d);					cycles += 8; break; }
	case 0xC3: {	op_set(0, reg.e);					cycles += 8; break; }
	case 0xC4: {	op_set(0, reg.h);					cycles += 8; break; }
	case 0xC5: {	op_set(0, reg.l);					cycles += 8; break; }
	case 0xC6: {	op_set(0, read_mem(reg.hl));		cycles += 16; break; }
	case 0xC7: {	op_set(0, reg.a);					cycles += 8; break; }
	case 0xC8: {	op_set(1, reg.b);					cycles += 8; break; }
	case 0xC9: {	op_set(1, reg.c);					cycles += 8; break; }
	case 0xCA: {	op_set(1, reg.d);					cycles += 8; break; }
	case 0xCB: {	op_set(1, reg.e);					cycles += 8; break; }
	case 0xCC: {	op_set(1, reg.h);					cycles += 8; break; }
	case 0xCD: {	op_set(1, reg.l);					cycles += 8; break; }
	case 0xCE: {	op_set(1, read_mem(reg.hl));		cycles += 16; break; }
	case 0xCF: {	op_set(1, reg.a);					cycles += 8; break; }

	case 0xD0: {	op_set(2, reg.b);					cycles += 8; break; }
	case 0xD1: {	op_set(2, reg.c);					cycles += 8; break; }
	case 0xD2: {	op_set(2, reg.d);					cycles += 8; break; }
	case 0xD3: {	op_set(2, reg.e);					cycles += 8; break; }
	case 0xD4: {	op_set(2, reg.h);					cycles += 8; break; }
	case 0xD5: {	op_set(2, reg.l);					cycles += 8; break; }
	case 0xD6: {	op_set(2, read_mem(reg.hl));		cycles += 16; break; }
	case 0xD7: {	op_set(2, reg.a);					cycles += 8; break; }
	case 0xD8: {	op_set(3, reg.b);					cycles += 8; break; }
	case 0xD9: {	op_set(3, reg.c);					cycles += 8; break; }
	case 0xDA: {	op_set(3, reg.d);					cycles += 8; break; }
	case 0xDB: {	op_set(3, reg.e);					cycles += 8; break; }
	case 0xDC: {	op_set(3, reg.h);					cycles += 8; break; }
	case 0xDD: {	op_set(3, reg.l);					cycles += 8; break; }
	case 0xDE: {	op_set(3, read_mem(reg.hl));		cycles += 16; break; }
	case 0xDF: {	op_set(3, reg.a);					cycles += 8; break; }

	case 0xE0: {	op_set(4, reg.b);					cycles += 8; break; }
	case 0xE1: {	op_set(4, reg.c);					cycles += 8; break; }
	case 0xE2: {	op_set(4, reg.d);					cycles += 8; break; }
	case 0xE3: {	op_set(4, reg.e);					cycles += 8; break; }
	case 0xE4: {	op_set(4, reg.h);					cycles += 8; break; }
	case 0xE5: {	op_set(4, reg.l);					cycles += 8; break; }
	case 0xE6: {	op_set(4, read_mem(reg.hl));		cycles += 16; break; }
	case 0xE7: {	op_set(4, reg.a);					cycles += 8; break; }
	case 0xE8: {	op_set(5, reg.b);					cycles += 8; break; }
	case 0xE9: {	op_set(5, reg.c);					cycles += 8; break; }
	case 0xEA: {	op_set(5, reg.d);					cycles += 8; break; }
	case 0xEB: {	op_set(5, reg.e);					cycles += 8; break; }
	case 0xEC: {	op_set(5, reg.h);					cycles += 8; break; }
	case 0xED: {	op_set(5, reg.l);					cycles += 8; break; }
	case 0xEE: {	op_set(5, read_mem(reg.hl));		cycles += 16; break; }
	case 0xEF: {	op_set(5, reg.a);					cycles += 8; break; }

	case 0xF0: {	op_set(6, reg.b);					cycles += 8; break; }
	case 0xF1: {	op_set(6, reg.c);					cycles += 8; break; }
	case 0xF2: {	op_set(6, reg.d);					cycles += 8; break; }
	case 0xF3: {	op_set(6, reg.e);					cycles += 8; break; }
	case 0xF4: {	op_set(6, reg.h);					cycles += 8; break; }
	case 0xF5: {	op_set(6, reg.l);					cycles += 8; break; }
	case 0xF6: {	op_set(6, read_mem(reg.hl));		cycles += 16; break; }
	case 0xF7: {	op_set(6, reg.a);					cycles += 8; break; }
	case 0xF8: {	op_set(7, reg.b);					cycles += 8; break; }
	case 0xF9: {	op_set(7, reg.c);					cycles += 8; break; }
	case 0xFA: {	op_set(7, reg.d);					cycles += 8; break; }
	case 0xFB: {	op_set(7, reg.e);					cycles += 8; break; }
	case 0xFC: {	op_set(7, reg.h);					cycles += 8; break; }
	case 0xFD: {	op_set(7, reg.l);					cycles += 8; break; }
	case 0xFE: {	op_set(7, read_mem(reg.hl));		cycles += 16; break; }
	case 0xFF: {	op_set(7, reg.a);					cycles += 8; break; }

	}
}

void CPU::execute_opcode(u8 opcode)
{
	switch (opcode)
	{
	case 0xCB: { execute_cb_opcode(fetch_opcode()); break; }

	case 0x00: { op_nop(); 										cycles += 4;	break; }
	case 0x01: { op_ld(reg.bc, reg.hl);							cycles += 12;	break; }
	case 0x02: { write_mem(reg.bc, reg.a);						cycles += 8;	break; }
	case 0x03: { op_inc(reg.bc);								cycles += 8;	break; }
	case 0x04: { op_inc(reg.b);									cycles += 4;	break; }
	case 0x05: { op_dec(reg.b);									cycles += 4;	break; }
	case 0x06: { op_ld(reg.b, get_imm_8());					cycles += 8;	break; }
	case 0x07: { op_rlca();										cycles += 4;	break; }
	case 0x08: { write_mem_16(get_imm_16(), reg.sp);								cycles += 20;	break; }
	case 0x09: { op_add(reg.hl, reg.bc);						cycles += 8;	break; }
	case 0x0A: { op_ld(reg.a, read_mem(reg.bc));				cycles += 8;	break; }
	case 0x0B: { op_dec(reg.bc);								cycles += 8;	break; }
	case 0x0C: { op_inc(reg.c);									cycles += 4;	break; }
	case 0x0D: { op_dec(reg.c);									cycles += 4;	break; }
	case 0x0E: { op_ld(reg.c, get_imm_8());						cycles += 8;	break; }
	case 0x0F: { op_rrca();										cycles += 4;	break; }
	case 0x10: { op_stop();										cycles += 4;	break; }
	case 0x11: { op_ld(reg.de, get_imm_16());					cycles += 12;	break; }
	case 0x12: { write_mem(reg.de, reg.a);						cycles += 8;	break; }
	case 0x13: { op_inc(reg.de);								cycles += 4;	break; }
	case 0x14: { op_inc(reg.d);									cycles += 4;	break; }
	case 0x15: { op_dec(reg.d);									cycles += 4;	break; }
	case 0x16: { op_ld(reg.d, read_mem(reg.pc));				cycles += 8;	break; }
	case 0x17: { op_rlca();										cycles += 4;	break; }
	case 0x18: { op_jr();										cycles += 12;	break; }
	case 0x19: { op_add(reg.hl, reg.de);						cycles += 8;	break; }
	case 0x1A: { op_ld(reg.a, read_mem(reg.de));				cycles += 8;	break; }
	case 0x1B: { op_dec(reg.bc);								cycles += 8;	break; }
	case 0x1C: { op_inc(reg.c);									cycles += 4;	break; }
	case 0x1D: { op_dec(reg.c);									cycles += 4;	break; }
	case 0x1E: { op_ld(reg.c, get_imm_8());						cycles += 8;	break; }
	case 0x1F: { op_rra();										cycles += 4;	break; }
	case 0x20: { op_jrc(!reg.get_zero());						cycles += 12;	break; }
	case 0x21: { op_ld(reg.hl, get_imm_16());					cycles += 12;	break; }
	case 0x22: { write_mem(reg.hl++, reg.a);					cycles += 8;	break; }
	case 0x23: { op_inc(reg.hl);								cycles += 8;	break; }
	case 0x24: { op_inc(reg.h);									cycles += 4;	break; }
	case 0x25: { op_dec(reg.h);									cycles += 4;	break; }
	case 0x26: { op_ld(reg.h, get_imm_8());						cycles += 8;	break; }
	case 0x27: { op_daa();										cycles += 4;	break; }
	case 0x28: { op_jrc(reg.get_zero());							cycles += 12;	break; }
	case 0x29: { op_add(reg.hl, reg.bc);						cycles += 8;	break; }
	case 0x2A: { op_ld(reg.a, read_mem(reg.hl++)); 				cycles += 8;	break; }
	case 0x2B: { op_dec(reg.bc);								cycles += 8;	break; }
	case 0x2C: { op_inc(reg.c);									cycles += 4;	break; }
	case 0x2D: { op_dec(reg.c);									cycles += 4;	break; }
	case 0x2E: { op_ld(reg.c, get_imm_8());						cycles += 8;	break; }
	case 0x2F: { op_rrca();										cycles += 4;	break; }
	case 0x30: { op_jrc(!reg.get_carry());						cycles += 12;	break; }
	case 0x31: { op_ld(reg.sp, get_imm_16());					cycles += 12;	break; }
	case 0x32: { write_mem(reg.hl--, reg.a);					cycles += 8;	break; }
	case 0x33: { op_inc(reg.sp);								cycles += 8;	break; }
	case 0x34: { op_inc(read_mem(reg.hl));						cycles += 12;	break; }
	case 0x35: { op_dec(read_mem(reg.hl));						cycles += 12;	break; }
	case 0x36: { write_mem(reg.hl, get_imm_8());				cycles += 12;	break; }
	case 0x37: { op_scf();										cycles += 4;	break; }
	case 0x38: { op_jrc(reg.get_carry());						cycles += 12;	break; }
	case 0x39: { op_add(reg.hl, reg.sp);						cycles += 8;	break; }
	case 0x3A: { op_ld(reg.a, read_mem(reg.hl--));				cycles += 8;	break; }
	case 0x3B: { op_dec(reg.sp);								cycles += 4;	break; }
	case 0x3C: { op_inc(reg.a);									cycles += 4;	break; }
	case 0x3D: { op_dec(reg.a);									cycles += 4;	break; }
	case 0x3E: { op_ld(reg.a, get_imm_8());						cycles += 8;	break; }
	case 0x3F: { op_ccf();										cycles += 4;	break; }
	case 0x40: { op_ld(reg.b, reg.b);							cycles += 4;	break; }
	case 0x41: { op_ld(reg.b, reg.c);							cycles += 4;	break; }
	case 0x42: { op_ld(reg.b, reg.d);							cycles += 4;	break; }
	case 0x43: { op_ld(reg.b, reg.e);							cycles += 4;	break; }
	case 0x44: { op_ld(reg.b, reg.b);							cycles += 4;	break; }
	case 0x45: { op_ld(reg.b, reg.l);							cycles += 4;	break; }
	case 0x46: { op_ld(reg.b, read_mem(reg.hl));				cycles += 8;	break; }
	case 0x47: { op_ld(reg.b, reg.a);							cycles += 4;	break; }
	case 0x48: { op_ld(reg.c, reg.b);							cycles += 4;	break; }
	case 0x49: { op_ld(reg.c, reg.c);							cycles += 4;	break; }
	case 0x4A: { op_ld(reg.c, reg.d);							cycles += 4;	break; }
	case 0x4B: { op_ld(reg.c, reg.e);							cycles += 4;	break; }
	case 0x4C: { op_ld(reg.c, reg.h);							cycles += 4;	break; }
	case 0x4D: { op_ld(reg.c, reg.l);							cycles += 4;	break; }
	case 0x4E: { op_ld(reg.c, read_mem(reg.hl));				cycles += 8;	break; }
	case 0x4F: { op_ld(reg.c, reg.a);							cycles += 4;	break; }
	case 0x50: { op_ld(reg.d, reg.b);							cycles += 4;	break; }
	case 0x51: { op_ld(reg.d, reg.c);							cycles += 4;	break; }
	case 0x52: { op_ld(reg.d, reg.d);							cycles += 4;	break; }
	case 0x53: { op_ld(reg.d, reg.e);							cycles += 4;	break; }
	case 0x54: { op_ld(reg.d, reg.b);							cycles += 4;	break; }
	case 0x55: { op_ld(reg.d, reg.l);							cycles += 4;	break; }
	case 0x56: { op_ld(reg.d, read_mem(reg.hl));				cycles += 8;	break; }
	case 0x57: { op_ld(reg.d, reg.a);							cycles += 4;	break; }
	case 0x58: { op_ld(reg.e, reg.b);							cycles += 4;	break; }
	case 0x59: { op_ld(reg.e, reg.c);							cycles += 4;	break; }
	case 0x5A: { op_ld(reg.e, reg.d);							cycles += 4;	break; }
	case 0x5B: { op_ld(reg.e, reg.e);							cycles += 4;	break; }
	case 0x5C: { op_ld(reg.e, reg.h);							cycles += 4;	break; }
	case 0x5D: { op_ld(reg.e, reg.l);							cycles += 4;	break; }
	case 0x5E: { op_ld(reg.e, read_mem(reg.hl));				cycles += 8;	break; }
	case 0x5F: { op_ld(reg.e, reg.a);							cycles += 4;	break; }
	case 0x60: { op_ld(reg.h, reg.b);							cycles += 4;	break; }
	case 0x61: { op_ld(reg.h, reg.c);							cycles += 4;	break; }
	case 0x62: { op_ld(reg.h, reg.d);							cycles += 4;	break; }
	case 0x63: { op_ld(reg.h, reg.e);							cycles += 4;	break; }
	case 0x64: { op_ld(reg.h, reg.b);							cycles += 4;	break; }
	case 0x65: { op_ld(reg.h, reg.l);							cycles += 4;	break; }
	case 0x66: { op_ld(reg.h, read_mem(reg.hl));				cycles += 8;	break; }
	case 0x67: { op_ld(reg.h, reg.a);							cycles += 4;	break; }
	case 0x68: { op_ld(reg.l, reg.b);							cycles += 4;	break; }
	case 0x69: { op_ld(reg.l, reg.c);							cycles += 4;	break; }
	case 0x6A: { op_ld(reg.l, reg.d);							cycles += 4;	break; }
	case 0x6B: { op_ld(reg.l, reg.e);							cycles += 4;	break; }
	case 0x6C: { op_ld(reg.l, reg.h);							cycles += 4;	break; }
	case 0x6D: { op_ld(reg.l, reg.l);							cycles += 4;	break; }
	case 0x6E: { op_ld(reg.l, read_mem(reg.hl));				cycles += 8;	break; }
	case 0x6F: { op_ld(reg.l, reg.a);							cycles += 4;	break; }
	case 0x70: { write_mem(reg.hl, reg.b);						cycles += 8;	break; }
	case 0x71: { write_mem(reg.hl, reg.c);						cycles += 8;	break; }
	case 0x72: { write_mem(reg.hl, reg.d);						cycles += 8;	break; }
	case 0x73: { write_mem(reg.hl, reg.e);						cycles += 8;	break; }
	case 0x74: { write_mem(reg.hl, reg.h);						cycles += 8;	break; }
	case 0x75: { write_mem(reg.hl, reg.l);						cycles += 8;	break; }
	case 0x76: { op_halt();										cycles += 4;	break; }
	case 0x77: { write_mem(reg.hl, reg.a);						cycles += 8;	break; }
	case 0x78: { op_ld(reg.a, reg.b);							cycles += 4;	break; }
	case 0x79: { op_ld(reg.a, reg.c);							cycles += 4;	break; }
	case 0x7A: { op_ld(reg.a, reg.d);							cycles += 4;	break; }
	case 0x7B: { op_ld(reg.a, reg.e);							cycles += 4;	break; }
	case 0x7C: { op_ld(reg.a, reg.h);							cycles += 4;	break; }
	case 0x7D: { op_ld(reg.a, reg.l);							cycles += 4;	break; }
	case 0x7E: { op_ld(reg.a, read_mem(reg.hl));				cycles += 8;	break; }
	case 0x7F: { op_ld(reg.a, reg.a);							cycles += 4;	break; }
	case 0x80: { op_add(reg.a, reg.b);							cycles += 4;	break; }
	case 0x81: { op_add(reg.a, reg.c);							cycles += 4;	break; }
	case 0x82: { op_add(reg.a, reg.d);							cycles += 4;	break; }
	case 0x83: { op_add(reg.a, reg.e);							cycles += 4;	break; }
	case 0x84: { op_add(reg.a, reg.h);							cycles += 4;	break; }
	case 0x85: { op_add(reg.a, reg.l);							cycles += 4;	break; }
	case 0x86: { op_add(reg.a, read_mem(reg.hl));				cycles += 8;	break; }
	case 0x87: { op_add(reg.a, reg.a);							cycles += 4;	break; }
	case 0x88: { op_adc(reg.a, reg.b);							cycles += 4;	break; }
	case 0x89: { op_adc(reg.a, reg.c);							cycles += 4;	break; }
	case 0x8A: { op_adc(reg.a, reg.d);							cycles += 4;	break; }
	case 0x8B: { op_adc(reg.a, reg.e);							cycles += 4;	break; }
	case 0x8C: { op_adc(reg.a, reg.h);							cycles += 4;	break; }
	case 0x8D: { op_adc(reg.a, reg.l);							cycles += 4;	break; }
	case 0x8E: { op_adc(reg.a, read_mem(reg.hl));				cycles += 8;	break; }
	case 0x8F: { op_adc(reg.a, reg.a);							cycles += 4;	break; }
	case 0x90: { op_sub(reg.a, reg.b);							cycles += 4;	break; }
	case 0x91: { op_sub(reg.a, reg.c);							cycles += 4;	break; }
	case 0x92: { op_sub(reg.a, reg.d);							cycles += 4;	break; }
	case 0x93: { op_sub(reg.a, reg.e);							cycles += 4;	break; }
	case 0x94: { op_sub(reg.a, reg.h);							cycles += 4;	break; }
	case 0x95: { op_sub(reg.a, reg.l);							cycles += 4;	break; }
	case 0x96: { op_sub(reg.a, read_mem(reg.hl));				cycles += 8;	break; }
	case 0x97: { op_sub(reg.a, reg.a);							cycles += 4;	break; }
	case 0x98: { op_sbc(reg.a, reg.b);							cycles += 4;	break; }
	case 0x99: { op_sbc(reg.a, reg.c);							cycles += 4;	break; }
	case 0x9A: { op_sbc(reg.a, reg.d);							cycles += 4;	break; }
	case 0x9B: { op_sbc(reg.a, reg.e);							cycles += 4;	break; }
	case 0x9C: { op_sbc(reg.a, reg.h);							cycles += 4;	break; }
	case 0x9D: { op_sbc(reg.a, reg.l);							cycles += 4;	break; }
	case 0x9E: { op_sbc(reg.a, read_mem(reg.hl));				cycles += 8;	break; }
	case 0x9F: { op_sbc(reg.a, reg.a);							cycles += 4;	break; }
	case 0xA0: { op_and(reg.b);									cycles += 4;	break; }
	case 0xA1: { op_and(reg.c);									cycles += 4;	break; }
	case 0xA2: { op_and(reg.d);									cycles += 4;	break; }
	case 0xA3: { op_and(reg.e);									cycles += 4;	break; }
	case 0xA4: { op_and(reg.h);									cycles += 4;	break; }
	case 0xA5: { op_and(reg.l);									cycles += 4;	break; }
	case 0xA6: { op_and(read_mem(reg.hl));						cycles += 4;	break; }
	case 0xA7: { op_and(reg.a);									cycles += 4;	break; }
	case 0xA8: { op_xor(reg.b);									cycles += 4;	break; }
	case 0xA9: { op_xor(reg.c);									cycles += 4;	break; }
	case 0xAA: { op_xor(reg.d);									cycles += 4;	break; }
	case 0xAB: { op_xor(reg.e);									cycles += 4;	break; }
	case 0xAC: { op_xor(reg.h);									cycles += 4;	break; }
	case 0xAD: { op_xor(reg.l);									cycles += 4;	break; }
	case 0xAE: { op_xor(read_mem(reg.hl));						cycles += 8;	break; }
	case 0xAF: { op_xor(reg.a);									cycles += 4;	break; }
	case 0xB0: { op_or(reg.b);									cycles += 4;	break; }
	case 0xB1: { op_or(reg.c);									cycles += 4;	break; }
	case 0xB2: { op_or(reg.d);									cycles += 4;	break; }
	case 0xB3: { op_or(reg.e);									cycles += 4;	break; }
	case 0xB4: { op_or(reg.h);									cycles += 4;	break; }
	case 0xB5: { op_or(reg.l);									cycles += 4;	break; }
	case 0xB6: { op_or(read_mem(reg.hl));						cycles += 8;	break; }
	case 0xB7: { op_or(reg.a);									cycles += 4;	break; }
	case 0xB8: { op_cp(reg.b);									cycles += 4;	break; }
	case 0xB9: { op_cp(reg.c);									cycles += 4;	break; }
	case 0xBA: { op_cp(reg.d);									cycles += 4;	break; }
	case 0xBB: { op_cp(reg.e);									cycles += 4;	break; }
	case 0xBC: { op_cp(reg.h);									cycles += 4;	break; }
	case 0xBD: { op_cp(reg.l);									cycles += 4;	break; }
	case 0xBE: { op_cp(read_mem(reg.hl));						cycles += 8;	break; }
	case 0xBF: { op_cp(reg.a);									cycles += 4;	break; }
	case 0xC0: { op_ret(!reg.get_zero());						cycles += 20;	break; }
	case 0xC1: { op_ld(reg.bc, pop_16b());								cycles += 12;	break; }
	case 0xC2: { op_jpc(!reg.get_zero());						cycles += 16;	break; }
	case 0xC3: { op_jp(get_imm_16());							cycles += 16;	break; }
	case 0xC4: { op_call(!reg.get_zero());						cycles += 24;	break; }
	case 0xC5: { push_16b(reg.bc);								cycles += 16;	break; }
	case 0xC6: { op_add(reg.a, get_imm_8());					cycles += 8;	break; }
	case 0xC7: { op_rst(0x00);							cycles += 32;	break; }
	case 0xC8: { op_ret(reg.get_zero());						cycles += 20;	break; }
	case 0xC9: { op_ret();										cycles += 20;	break; }
	case 0xCA: { op_jpc(reg.get_zero());						cycles += 16;	break; }
	case 0xCC: { op_call(reg.get_zero());						cycles += 24;	break; }
	case 0xCD: { op_call();										cycles += 24;	break; }
	case 0xCE: { op_adc(reg.a, get_imm_8());					cycles += 8;	break; }
	case 0xCF: { op_rst(0x08);							cycles += 32;	break; }
	case 0xD0: { op_ret(!reg.get_carry());						cycles += 20;	break; }
	case 0xD1: { op_ld(reg.de, pop_16b());						cycles += 12;	break; }
	case 0xD2: { op_jpc(!reg.get_carry());						cycles += 16;	break; }
	//	 0xD3 is an undefined opcode
	case 0xD4: { op_call(!reg.get_carry());						cycles += 24;	break; }
	case 0xD5: { push_16b(reg.de);								cycles += 16;	break; }
	case 0xD6: { op_sub(reg.a, get_imm_8());					cycles += 8;	break; }
	case 0xD7: { op_rst(0x10);							cycles += 32;	break; }
	case 0xD8: { op_ret(reg.get_carry());						cycles += 20;	break; }
	case 0xD9: { op_ret(); op_ei();								cycles += 4;	break; }
	case 0xDA: { op_jpc(reg.get_carry());						cycles += 16;	break; }
	//   0xDB is an undefined opcode 
	case 0xDC: { op_call(reg.get_carry());						cycles += 24;	break; }
	//   0xDD is an undefined opcode
	case 0xDE: { op_sbc(reg.a, get_imm_8());					cycles += 8;	break; }
	case 0xDF: { op_rst(0x18);							cycles += 32;	break; }
	case 0xE0: { write_mem(0xFF00 + get_imm_8(), reg.a);		cycles += 12;	break; }
	case 0xE1: { op_ld(reg.hl, pop_16b());						cycles += 12;	break; }
	case 0xE2: { write_mem(0xFF00 + reg.c, reg.a);				cycles += 16;	break; }
	//   0xE3 is an undefined opcode
	case 0xE4: { op_undefined();												break; }
	case 0xE5: { push_16b(reg.hl);								cycles += 16;	break; }
	case 0xE6: { op_and(get_imm_8());							cycles += 8;	break; }
	case 0xE7: { op_rst(0x20);							cycles += 32;	break; }
	case 0xE8: { op_add(reg.sp, get_imm_s8());					cycles += 16;	break; }
	case 0xE9: { op_jp(read_mem(reg.hl));						cycles += 4;	break; }
	case 0xEA: { write_imm_8(reg.a);							cycles += 16;	break; }
	//   0xEB is an undefined opcode
	case 0xEC: { op_call(reg.get_zero());						cycles += 24;	break; }
	case 0xED: { op_call();										cycles += 24;	break; }
	case 0xEE: { op_xor(get_imm_8());							cycles += 8;	break; }
	case 0xEF: { op_rst(0x28);							cycles += 32;	break; }
	case 0xF0: { op_ld(reg.a,read_mem(0xFF00+get_imm_8()));		cycles += 12;	break; }
	case 0xF1: {op_ld(reg.de, pop_16b());						cycles += 12;	break; }
	case 0xF2: { op_ld(reg.a, read_mem(0xFF00 + reg.c));		cycles += 8;	break; }
	case 0xF3: { op_di();										cycles += 4;	break; }
	//   0xF4  is an undefined opcode
	case 0xF5: { push_16b(reg.af);								cycles += 16;	break; }
	case 0xF6: { op_or(get_imm_8());							cycles += 8;	break; }
	case 0xF7: { op_rst(0x30);							cycles += 32;	break; }
	case 0xF8: { op_ld(reg.hl, get_imm_s8() + reg.sp);			cycles += 12;	break; }
	case 0xF9: { op_ld(reg.sp, reg.hl);							cycles += 8;	break; }
	case 0xFA: { op_ld(reg.a, read_mem(get_imm_16()));					cycles += 16;	break; }
	case 0xFB: { op_ei();										cycles += 4;	break; }
	//	 0xFC is an undefined opcode
	//	 0xFD is an undefined opcode
	case 0xFE: { op_cp(get_imm_8());							cycles += 16;	break; }
	case 0xFF: { op_rst(0x38);							cycles += 32;	break; }

	default:	 op_undefined();
	}
}


