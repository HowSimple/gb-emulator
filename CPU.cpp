#include "Registers.h"
#include"CPU.h"
#define NZ !f.zero
#define NC !f.carry
#define Z f.zero
#define C f.carry




u8 CPU::get_d8() // gets 8-bit immediate value from RAM
{
	cycles += 4;

	return (ram[sp + 1]);
}
u16 CPU::get_d16()	// gets 16-bit immediate value from RAM
{
	cycles += 4;
	u16 immediate_16_bit_value = ram[sp + 1] | (ram[sp + 2] << 8);

	return immediate_16_bit_value;
}
u8 CPU::get_s8() // gets 8-bit immediate value from RAM
{
	cycles += 4;

	return (ram[sp + 1]);
}
u16 CPU::get_s16()	// gets 16-bit immediate value from RAM
{
	cycles += 4;
	u16 immediate_16_bit_value = ram[sp + 1] | (ram[sp + 2] << 8);

	return immediate_16_bit_value;
}
void CPU::set_d16(u16 value)
{
	cycles += 20;
	ram[sp + 1] = value;
}
void CPU::set_d8(u8 value)
{
	cycles += 16;
	ram[sp + 1] = value;
}
void CPU::execute_cb_opcode()
{
	u1 opcode = fetch_opcode();
	switch (opcode)
	{
	case 0x00:	{	op_rlc(b);						cycles += 8; break;}
	case 0x01:	{	op_rlc(c);						cycles += 8; break;}
	case 0x02:	{	op_rlc(d);						cycles += 8; break;}
	case 0x03:	{	op_rlc(e);						cycles += 8; break;}
	case 0x04:	{	op_rlc(h);						cycles += 8; break;}
	case 0x05:	{	op_rlc(l);						cycles += 8; break;}
	case 0x06:	{	op_rlc(ram[hl]);				cycles += 16; break;}
	case 0x07:	{	op_rlc(a);						cycles += 8; break;}
	case 0x08:	{	op_rrc(b);						cycles += 8; break;}
	case 0x09:	{	op_rrc(c);						cycles += 8; break;}
	case 0x0A:	{	op_rrc(d);						cycles += 8; break;}
	case 0x0B:	{	op_rrc(e);						cycles += 8; break;}
	case 0x0C:	{	op_rrc(h);						cycles += 8; break;}
	case 0x0D:	{	op_rrc(l);						cycles += 8; break;}
	case 0x0E:	{	op_rrc(ram[hl]);				cycles += 16; break;}
	case 0x0F:	{	op_rrc(a);						cycles += 8; break;}
				
	case 0x10:	{	op_rl(b);						cycles += 8; break;}
	case 0x11:	{	op_rl(c);						cycles += 8; break;}
	case 0x12:	{	op_rl(d);						cycles += 8; break;}
	case 0x13:	{	op_rl(e);						cycles += 8; break;}
	case 0x14:	{	op_rl(h);						cycles += 8; break;}
	case 0x15:	{	op_rl(l);						cycles += 8; break;}
	case 0x16:	{	op_rl(ram[hl]);					cycles += 16; break;}
	case 0x17:	{	op_rl(a);						cycles += 8; break;}
	case 0x18:	{	op_rr(b);						cycles += 8; break;}
	case 0x19:	{	op_rr(c);						cycles += 8; break;}
	case 0x1A:	{	op_rr(d);						cycles += 8; break;}
	case 0x1B:	{	op_rr(e);						cycles += 8; break;}
	case 0x1C:	{	op_rr(h);						cycles += 8; break;}
	case 0x1D:	{	op_rr(l);						cycles += 8; break;}
	case 0x1E:	{	op_rr(ram[hl]);					cycles += 16; break;}
	case 0x1F:	{	op_rr(a);						cycles += 8; break;}
				
	case 0x20:	{	op_sla(b);						cycles += 8; break;}
	case 0x21:	{	op_sla(c);						cycles += 8; break;}
	case 0x22:	{	op_sla(d);						cycles += 8; break;}
	case 0x23:	{	op_sla(e);						cycles += 8; break;}
	case 0x24:	{	op_sla(h);						cycles += 8; break;}
	case 0x25:	{	op_sla(l);						cycles += 8; break;}
	case 0x26:	{	op_sla(ram[hl]);				cycles += 16; break;}
	case 0x27:	{	op_sla(a);						cycles += 8; break;}
	case 0x28:	{	op_sra(b);						cycles += 8; break;}
	case 0x29:	{	op_sra(c);						cycles += 8; break;}
	case 0x2A:	{	op_sra(d);						cycles += 8; break;}
	case 0x2B:	{	op_sra(e);						cycles += 8; break;}
	case 0x2C:	{	op_sra(h);						cycles += 8; break;}
	case 0x2D:	{	op_sra(l);						cycles += 8; break;}
	case 0x2E:	{	op_sra(ram[hl]);				cycles += 16; break;}
	case 0x2F:	{	op_sra(a);						cycles += 8; break;}
				
	case 0x30:	{	op_swap(b);						cycles += 8; break;}
	case 0x31:	{	op_swap(c);						cycles += 8; break;}
	case 0x32:	{	op_swap(d);						cycles += 8; break;}
	case 0x33:	{	op_swap(e);						cycles += 8; break;}
	case 0x34:	{	op_swap(h);						cycles += 8; break;}
	case 0x35:	{	op_swap(l);						cycles += 8; break;}
	case 0x36:	{	op_swap(ram[hl]);				cycles += 16; break;}
	case 0x37:	{	op_swap(a);						cycles += 8; break;}
	case 0x38:	{	op_srl(b);						cycles += 8; break;}
	case 0x39:	{	op_srl(c);						cycles += 8; break;}
	case 0x3A:	{	op_srl(d);						cycles += 8; break;}
	case 0x3B:	{	op_srl(e);						cycles += 8; break;}
	case 0x3C:	{	op_srl(h);						cycles += 8; break;}
	case 0x3D:	{	op_srl(l);						cycles += 8; break;}
	case 0x3E:	{	op_srl(ram[hl]);				cycles += 16; break;}
	case 0x3F:	{	op_srl(a);						cycles += 8; break;}
				
	case 0x40:	{	op_bit(0, b);					cycles += 8; break;}
	case 0x41:	{	op_bit(0, c);					cycles += 8; break;}
	case 0x42:	{	op_bit(0, d);					cycles += 8; break;}
	case 0x43:	{	op_bit(0, e);					cycles += 8; break;}
	case 0x44:	{	op_bit(0, h);					cycles += 8; break;}
	case 0x45:	{	op_bit(0, l);					cycles += 8; break;}
	case 0x46:	{	op_bit(0, ram[hl]);				cycles += 16; break;}
	case 0x47:	{	op_bit(0, a);					cycles += 8; break;}
	case 0x48:	{	op_bit(1, b);					cycles += 8; break;}
	case 0x49:	{	op_bit(1, c);					cycles += 8; break;}
	case 0x4A:	{	op_bit(1, d);					cycles += 8; break;}
	case 0x4B:	{	op_bit(1, e);					cycles += 8; break;}
	case 0x4C:	{	op_bit(1, h);					cycles += 8; break;}
	case 0x4D:	{	op_bit(1, l);					cycles += 8; break;}
	case 0x4E:	{	op_bit(1, ram[hl]);				cycles += 16; break;}
	case 0x4F:	{	op_bit(1, a);					cycles += 8; break;}
				
	case 0x50:	{	op_bit(2, b);					cycles += 8; break; }
	case 0x51:	{	op_bit(2, c);					cycles += 8; break; }
	case 0x52:	{	op_bit(2, d);					cycles += 8; break; }
	case 0x53:	{	op_bit(2, e);					cycles += 8; break; }
	case 0x54:	{	op_bit(2, h);					cycles += 8; break; }
	case 0x55:	{	op_bit(2, l);					cycles += 8; break; }
	case 0x56:	{	op_bit(2, ram[hl]);				cycles += 16; break; }
	case 0x57:	{	op_bit(2, a);					cycles += 8; break; }
	case 0x58:	{	op_bit(3, b);					cycles += 8; break; }
	case 0x59:	{	op_bit(3, c);					cycles += 8; break; }
	case 0x5A:	{	op_bit(3, d);					cycles += 8; break; }
	case 0x5B:	{	op_bit(3, e);					cycles += 8; break; }
	case 0x5C:	{	op_bit(3, h);					cycles += 8; break; }
	case 0x5D:	{	op_bit(3, l);					cycles += 8; break; }
	case 0x5E:	{	op_bit(3, ram[hl]);				cycles += 16; break; }
	case 0x5F:	{	op_bit(3, a);					cycles += 8; break;}
					
	case 0x60:	{	op_bit(4, b);					cycles += 8; break; }
	case 0x61:	{	op_bit(4, c);					cycles += 8; break; }
	case 0x62:	{	op_bit(4, d);					cycles += 8; break; }
	case 0x63:	{	op_bit(4, e);					cycles += 8; break; }
	case 0x64:	{	op_bit(4, h);					cycles += 8; break; }
	case 0x65:	{	op_bit(4, l);					cycles += 8; break; }
	case 0x66:	{	op_bit(4, ram[hl]);				cycles += 16; break; }
	case 0x67:	{	op_bit(4, a);					cycles += 8; break; }
	case 0x68:	{	op_bit(5, b);					cycles += 8; break; }
	case 0x69:	{	op_bit(5, c);					cycles += 8; break; }
	case 0x6A:	{	op_bit(5, d);					cycles += 8; break; }
	case 0x6B:	{	op_bit(5, e);					cycles += 8; break; }
	case 0x6C:	{	op_bit(5, h);					cycles += 8; break; }
	case 0x6D:	{	op_bit(5, l);					cycles += 8; break; }
	case 0x6E:	{	op_bit(5, ram[hl]);				cycles += 16; break; }
	case 0x6F:	{	op_bit(5, a);					cycles += 8; break; }
					
	case 0x70:	{	op_bit(6, b);					cycles += 8; break; }
	case 0x71:	{	op_bit(6, c);					cycles += 8; break; }
	case 0x72:	{	op_bit(6, d);					cycles += 8; break; }
	case 0x73:	{	op_bit(6, e);					cycles += 8; break; }
	case 0x74:	{	op_bit(6, h);					cycles += 8; break; }
	case 0x75:	{	op_bit(6, l);					cycles += 8; break; }
	case 0x76:	{	op_bit(6, ram[hl]);				cycles += 16; break; }
	case 0x77:	{	op_bit(6, a);					cycles += 8; break; }
	case 0x78:	{	op_bit(7, b);					cycles += 8; break; }
	case 0x79:	{	op_bit(7, c);					cycles += 8; break; }
	case 0x7A:	{	op_bit(7, d);					cycles += 8; break; }
	case 0x7B:	{	op_bit(7, e);					cycles += 8; break; }
	case 0x7C:	{	op_bit(7, h);					cycles += 8; break; }
	case 0x7D:	{	op_bit(7, l);					cycles += 8; break; }
	case 0x7E:	{	op_bit(7, ram[hl]);				cycles += 16; break; }
	case 0x7F:	{	op_bit(7, a);					cycles += 8; break; }
			
	case 0x80: {	op_res(0, b);					cycles += 8; break; }
	case 0x81: {	op_res(0, c);					cycles += 8; break; }
	case 0x82: {	op_res(0, d);					cycles += 8; break; }
	case 0x83: {	op_res(0, e);					cycles += 8; break; }
	case 0x84: {	op_res(0, h);					cycles += 8; break; }
	case 0x85: {	op_res(0, l);					cycles += 8; break; }
	case 0x86: {	op_res(0, ram[hl]);				cycles += 16; break; }
	case 0x87: {	op_res(0, a);					cycles += 8; break; }
	case 0x88: {	op_res(1, b);					cycles += 8; break; }
	case 0x89: {	op_res(1, c);					cycles += 8; break; }
	case 0x8A: {	op_res(1, d);					cycles += 8; break; }
	case 0x8B: {	op_res(1, e);					cycles += 8; break; }
	case 0x8C: {	op_res(1, h);					cycles += 8; break; }
	case 0x8D: {	op_res(1, l);					cycles += 8; break; }
	case 0x8E: {	op_res(1, ram[hl]);				cycles += 16; break; }
	case 0x8F: {	op_res(1, a);					cycles += 8; break; }
	case 0x90: {	op_res(2, b);					cycles += 8; break; }
	case 0x91: {	op_res(2, c);					cycles += 8; break; }
	case 0x92: {	op_res(2, d);					cycles += 8; break; }
	case 0x93: {	op_res(2, e);					cycles += 8; break; }
	case 0x94: {	op_res(2, h);					cycles += 8; break; }
	case 0x95: {	op_res(2, l);					cycles += 8; break; }
	case 0x96: {	op_res(2, ram[hl]);				cycles += 16; break; }
	case 0x97: {	op_res(2, a);					cycles += 8; break; }
	case 0x98: {	op_res(3, b);					cycles += 8; break; }
	case 0x99: {	op_res(3, c);					cycles += 8; break; }
	case 0x9A: {	op_res(3, d);					cycles += 8; break; }
	case 0x9B: {	op_res(3, e);					cycles += 8; break; }
	case 0x9C: {	op_res(3, h);					cycles += 8; break; }
	case 0x9D: {	op_res(3, l);					cycles += 8; break; }
	case 0x9E: {	op_res(3, ram[hl]);				cycles += 16; break; }
	case 0x9F: {	op_res(3, a);					cycles += 8; break; }
	case 0xA0: {	op_res(4, b);					cycles += 8; break; }
	case 0xA1: {	op_res(4, c);					cycles += 8; break; }
	case 0xA2: {	op_res(4, d);					cycles += 8; break; }
	case 0xA3: {	op_res(4, e);					cycles += 8; break; }
	case 0xA4: {	op_res(4, h);					cycles += 8; break; }
	case 0xA5: {	op_res(4, l);					cycles += 8; break; }
	case 0xA6: {	op_res(4, ram[hl]);				cycles += 16; break; }
	case 0xA7: {	op_res(4, a);					cycles += 8; break; }
	case 0xA8: {	op_res(5, b);					cycles += 8; break; }
	case 0xA9: {	op_res(5, c);					cycles += 8; break; }
	case 0xAA: {	op_res(5, d);					cycles += 8; break; }
	case 0xAB: {	op_res(5, e);					cycles += 8; break; }
	case 0xAC: {	op_res(5, h);					cycles += 8; break; }
	case 0xAD: {	op_res(5, l);					cycles += 8; break; }
	case 0xAE: {	op_res(5, ram[hl]);				cycles += 16; break; }
	case 0xAF: {	op_res(5, a);					cycles += 8; break; }
	case 0xB0: {	op_res(6, b);					cycles += 8; break; }
	case 0xB1: {	op_res(6, c);					cycles += 8; break; }
	case 0xB2: {	op_res(6, d);					cycles += 8; break; }
	case 0xB3: {	op_res(6, e);					cycles += 8; break; }
	case 0xB4: {	op_res(6, h);					cycles += 8; break; }
	case 0xB5: {	op_res(6, l);					cycles += 8; break; }
	case 0xB6: {	op_res(6, ram[hl]);				cycles += 16; break; }
	case 0xB7: {	op_res(6, a);					cycles += 8; break; }
	case 0xB8: {	op_res(7, b);					cycles += 8; break; }
	case 0xB9: {	op_res(7, c);					cycles += 8; break; }
	case 0xBA: {	op_res(7, d);					cycles += 8; break; }
	case 0xBB: {	op_res(7, e);					cycles += 8; break; }
	case 0xBC: {	op_res(7, h);					cycles += 8; break; }
	case 0xBD: {	op_res(7, l);					cycles += 8; break; }
	case 0xBE: {	op_res(7, ram[hl]);				cycles += 16; break; }
	case 0xBF: {	op_res(7, a);					cycles += 8; break; }

	case 0xC0: {	op_set(0, b);					cycles += 8; break; }
	case 0xC1: {	op_set(0, c);					cycles += 8; break; }
	case 0xC2: {	op_set(0, d);					cycles += 8; break; }
	case 0xC3: {	op_set(0, e);					cycles += 8; break; }
	case 0xC4: {	op_set(0, h);					cycles += 8; break; }
	case 0xC5: {	op_set(0, l);					cycles += 8; break; }
	case 0xC6: {	op_set(0, ram[hl]);				cycles += 16; break; }
	case 0xC7: {	op_set(0, a);					cycles += 8; break; }
	case 0xC8: {	op_set(1, b);					cycles += 8; break; }
	case 0xC9: {	op_set(1, c);					cycles += 8; break; }
	case 0xCA: {	op_set(1, d);					cycles += 8; break; }
	case 0xCB: {	op_set(1, e);					cycles += 8; break; }
	case 0xCC: {	op_set(1, h);					cycles += 8; break; }
	case 0xCD: {	op_set(1, l);					cycles += 8; break; }
	case 0xCE: {	op_set(1, ram[hl]);				cycles += 16; break; }
	case 0xCF: {	op_set(1, a);					cycles += 8; break; }

	case 0xD0: {	op_set(2, b);					cycles += 8; break; }
	case 0xD1: {	op_set(2, c);					cycles += 8; break; }
	case 0xD2: {	op_set(2, d);					cycles += 8; break; }
	case 0xD3: {	op_set(2, e);					cycles += 8; break; }
	case 0xD4: {	op_set(2, h);					cycles += 8; break; }
	case 0xD5: {	op_set(2, l);					cycles += 8; break; }
	case 0xD6: {	op_set(2, ram[hl]);				cycles += 16; break; }
	case 0xD7: {	op_set(2, a);					cycles += 8; break; }
	case 0xD8: {	op_set(3, b);					cycles += 8; break; }
	case 0xD9: {	op_set(3, c);					cycles += 8; break; }
	case 0xDA: {	op_set(3, d);					cycles += 8; break; }
	case 0xDB: {	op_set(3, e);					cycles += 8; break; }
	case 0xDC: {	op_set(3, h);					cycles += 8; break; }
	case 0xDD: {	op_set(3, l);					cycles += 8; break; }
	case 0xDE: {	op_set(3, ram[hl]);				cycles += 16; break; }
	case 0xDF: {	op_set(3, a);					cycles += 8; break; }

	case 0xE0: {	op_set(4, b);					cycles += 8; break; }
	case 0xE1: {	op_set(4, c);					cycles += 8; break; }
	case 0xE2: {	op_set(4, d);					cycles += 8; break; }
	case 0xE3: {	op_set(4, e);					cycles += 8; break; }
	case 0xE4: {	op_set(4, h);					cycles += 8; break; }
	case 0xE5: {	op_set(4, l);					cycles += 8; break; }
	case 0xE6: {	op_set(4, ram[hl]);				cycles += 16; break; }
	case 0xE7: {	op_set(4, a);					cycles += 8; break; }
	case 0xE8: {	op_set(5, b);					cycles += 8; break; }
	case 0xE9: {	op_set(5, c);					cycles += 8; break; }
	case 0xEA: {	op_set(5, d);					cycles += 8; break; }
	case 0xEB: {	op_set(5, e);					cycles += 8; break; }
	case 0xEC: {	op_set(5, h);					cycles += 8; break; }
	case 0xED: {	op_set(5, l);					cycles += 8; break; }
	case 0xEE: {	op_set(5, ram[hl]);				cycles += 16; break; }
	case 0xEF: {	op_set(5, a);					cycles += 8; break; }

	case 0xF0: {	op_set(6, b);					cycles += 8; break; }
	case 0xF1: {	op_set(6, c);					cycles += 8; break; }
	case 0xF2: {	op_set(6, d);					cycles += 8; break; }
	case 0xF3: {	op_set(6, e);					cycles += 8; break; }
	case 0xF4: {	op_set(6, h);					cycles += 8; break; }
	case 0xF5: {	op_set(6, l);					cycles += 8; break; }
	case 0xF6: {	op_set(6, ram[hl]);				cycles += 16; break; }
	case 0xF7: {	op_set(6, a);					cycles += 8; break; }
	case 0xF8: {	op_set(7, b);					cycles += 8; break; }
	case 0xF9: {	op_set(7, c);					cycles += 8; break; }
	case 0xFA: {	op_set(7, d);					cycles += 8; break; }
	case 0xFB: {	op_set(7, e);					cycles += 8; break; }
	case 0xFC: {	op_set(7, h);					cycles += 8; break; }
	case 0xFD: {	op_set(7, l);					cycles += 8; break; }
	case 0xFE: {	op_set(7, ram[hl]);				cycles += 16; break; }
	case 0xFF: {	op_set(7, a);					cycles += 8; break; }

	}
}
u1 CPU::fetch_opcode()
{
	return u1();
}
void CPU::execute_opcode(u1 opcode)
{
	switch (opcode)
	{
	case 0xCB: { execute_cb_opcode(); break; }

	case 0x00: { op_nop(); cycles += 4; break; }
	case 0x01: { op_ld(bc, hl); cycles += 12; break; }
	case 0x02: { op_ld(ram[bc], a); cycles += 8; break; }
	case 0x03: { op_inc(bc); cycles += 8; break; }
	case 0x04: { op_inc(b); cycles += 4;  break; }
	case 0x05: { op_dec(b); cycles += 4; break; }
	case 0x06: { op_ld(b, get_d16()); cycles += 8; break; }
	case 0x07: { op_rlca(); cycles += 4; break; }
	case 0x08: { set_d16(sp); cycles += 20; break; }
	case 0x09: { op_add(hl, bc); cycles += 8; break; }
	case 0x0A: { op_ld(a, ram[bc]); cycles += 8; break; }
	case 0x0B: { op_dec(bc); cycles += 8; break; }
	case 0x0C: { op_inc(c); cycles += 4; break; }
	case 0x0D: { op_dec(c); cycles += 4; break; }
	case 0x0E: { op_ld(c, get_d8()); cycles += 8; break; }
	case 0x0F: { op_rrca(); cycles += 4; break; }
	case 0x10: { op_stop(); cycles += 4; break; }
	case 0x11: { op_ld(de, get_d16()); cycles += 12; break; }
	case 0x12: { op_ld(ram[de], a); cycles += 8; break; }
	case 0x13: { op_inc(de); cycles += 4; break; }
	case 0x14: { op_inc(d);  cycles += 4; break; }
	case 0x15: { op_dec(d);  cycles += 4; break; }
	case 0x16: { op_ld(d, get_d8()); cycles += 8; break; }
	case 0x17: { op_rlca(); cycles += 4; break; }
	case 0x18: { op_jr();  cycles += 12; break; }
	case 0x19: { op_add(hl, de); cycles += 8; break; }
	case 0x1A: { op_ld(a, ram[de]); cycles += 8; break; }
	case 0x1B: { op_dec(bc); cycles += 8; break; }
	case 0x1C: { op_inc(c); cycles += 4; break; }
	case 0x1D: { op_dec(c); cycles += 4; break; }
	case 0x1E: { op_ld(c, get_d8()); cycles += 8; break; }
	case 0x1F: { op_rra(); cycles += 4; break; }
	case 0x20: { op_jr(NZ); cycles += 12; break; }
	case 0x21: { op_ld(hl, get_d8());  cycles += 12; break; }
	case 0x22: { op_ld(ram[hl], a); hl++; cycles += 8; break; }
	case 0x23: { op_inc(hl); cycles += 8; break; }
	case 0x24: { op_inc(h); cycles += 4; break; }
	case 0x25: { op_dec(h); cycles += 4; break; }
	case 0x26: { op_ld(h, get_d8());  cycles += 8; break; }
	case 0x27: { op_daa(); break; }
	case 0x28: { op_jr(Z); break; }
	case 0x29: { op_add(hl, bc); break; }
	case 0x2A: { op_ld(a, ram[hl]); hl++; cycles += 8; break; }
	case 0x2B: { op_dec(bc); break; }
	case 0x2C: { op_inc(c); break; }
	case 0x2D: { op_dec(c); break; }
	case 0x2E: { op_ld(c, get_d8()); break; }
	case 0x2F: { op_rrca(); break; }
	case 0x30: { op_jr(NC);	cycles += 12; break; }
	case 0x31: { op_ld(sp, get_d16()); break; }
	case 0x32: { op_ld(ram[hl], a); hl--; cycles += 8; break; }
	case 0x33: { op_inc(sp); break; }
	case 0x34: { op_inc(ram[hl]); cycles += 12; break; }
	case 0x35: { op_dec(ram[hl]); cycles += 12; break; }
	case 0x36: { op_ld(ram[hl], get_d8()); cycles += 12; break; }
	case 0x37: { op_scf(); cycles += 4; break; }
	case 0x38: { op_jr(C); cycles += 12; break; }
	case 0x39: { op_add(hl, sp); break; }
	case 0x3A: { op_ld(a, ram[hl]); hl--;  cycles += 8; break; }
	case 0x3B: { op_dec(sp); cycles += 4; break; }
	case 0x3C: { op_inc(a); break; }
	case 0x3D: { op_dec(a); break; }
	case 0x3E: { op_ld(a, get_d8()); break; }
	case 0x3F: { op_ccf(); break; }

	case 0x40: { op_ld(b, b); break; }	
	case 0x41: { op_ld(b, c); break; }	
	case 0x42: { op_ld(b, d); break; }	
	case 0x43: { op_ld(b, e); break; }	
	case 0x44: { op_ld(b, b); break; }	
	case 0x45: { op_ld(b, l); break; }	
	case 0x46: { op_ld(b, ram[hl]); cycles += 8; break; }
	case 0x47: { op_ld(b, a); cycles += 4; break; }	
	case 0x48: { op_ld(c, b); cycles += 4; break; }	
	case 0x49: { op_ld(c, c); cycles += 4; break; }	
	case 0x4A: { op_ld(c, d); cycles += 4; break; }	
	case 0x4B: { op_ld(c, e); cycles += 4; break; }
	case 0x4C: { op_ld(c, h); cycles += 4; break; }
	case 0x4D: { op_ld(c, l); cycles += 4; break; }
	case 0x4E: { op_ld(c, ram[hl]); cycles += 8; break; }
	case 0x4F: { op_ld(c, a);	cycles += 4; break; }
	
	case 0x50: { op_ld(d, b);	cycles += 4; break; }
	case 0x51: { op_ld(d, c);	cycles += 4; break; }
	case 0x52: { op_ld(d, d);	cycles += 4; break; }
	case 0x53: { op_ld(d, e);	cycles += 4; break; }
	case 0x54: { op_ld(d, b);	cycles += 4; break; }
	case 0x55: { op_ld(d, l);	cycles += 4; break; }
	case 0x56: { op_ld(d, ram[hl]); cycles += 8; break; }
	case 0x57: { op_ld(d, a); cycles += 4;	break; }
	case 0x58: { op_ld(e, b); cycles += 4;	break; }
	case 0x59: { op_ld(e, c); cycles += 4;	break; }
	case 0x5A: { op_ld(e, d); cycles += 4;	break; }
	case 0x5B: { op_ld(e, e); cycles += 4;	break; }
	case 0x5C: { op_ld(e, h); cycles += 4;	break; }
	case 0x5D: { op_ld(e, l); cycles += 4;	break; }
	case 0x5E: { op_ld(e, ram[hl]); cycles += 8; break; }
	case 0x5F: { op_ld(e, a);	cycles += 4; break; }

	case 0x60: { op_ld(h, b); cycles += 4;	break; }	
	case 0x61: { op_ld(h, c); cycles += 4;	break; }	
	case 0x62: { op_ld(h, d); cycles += 4;	break; }	
	case 0x63: { op_ld(h, e); cycles += 4;	break; }	
	case 0x64: { op_ld(h, b); cycles += 4;	break; }	
	case 0x65: { op_ld(h, l); cycles += 4;	break; }	
	case 0x66: { op_ld(h, ram[hl]); cycles += 8; break; }
	case 0x67: { op_ld(h, a);	cycles += 4; break; }	
	case 0x68: { op_ld(l, b);	cycles += 4; break; }	
	case 0x69: { op_ld(l, c);	cycles += 4; break; }	
	case 0x6A: { op_ld(l, d);	cycles += 4; break; }	
	case 0x6B: { op_ld(l, e);	cycles += 4; break; }	
	case 0x6C: { op_ld(l, h);	cycles += 4; break; }	
	case 0x6D: { op_ld(l, l);	cycles += 4; break; }	
	case 0x6E: { op_ld(l, ram[hl]); cycles += 8; break; }
	case 0x6F: { op_ld(l, a);	cycles += 4; break; }

	case 0x70: { op_ld(ram[hl], b); cycles += 8; break; }
	case 0x71: { op_ld(ram[hl], c); cycles += 8; break; }
	case 0x72: { op_ld(ram[hl], d); cycles += 8; break; }
	case 0x73: { op_ld(ram[hl], e); cycles += 8; break; }
	case 0x74: { op_ld(ram[hl], h); cycles += 8; break; }
	case 0x75: { op_ld(ram[hl], l); cycles += 8; break; }
	case 0x76: { op_halt();			cycles += 4;  break; }
	case 0x77: { op_ld(ram[hl], a); cycles += 8;  break; }
	case 0x78: { op_ld(a, b); cycles += 4; break; }
	case 0x79: { op_ld(a, c); cycles += 4; break; }
	case 0x7A: { op_ld(a, d); cycles += 4; break; }
	case 0x7B: { op_ld(a, e); cycles += 4; break; }

	case 0x7C: { op_ld(a, h); break; }
	case 0x7D: { op_ld(a, l); break; }
	case 0x7E: { op_ld(a, ram[hl]); cycles += 8; break; }
	case 0x7F: { op_ld(a, a); break; }
	case 0x80: { op_add(a, b);	cycles += 4; break; } 
	case 0x81: { op_add(a, c);	cycles += 4; break; } 
	case 0x82: { op_add(a, d);	cycles += 4; break; } 
	case 0x83: { op_add(a, e);	cycles += 4; break; } 
	case 0x84: { op_add(a, h);	cycles += 4; break; } 
	case 0x85: { op_add(a, l);	cycles += 4; break; } 
	case 0x86: { op_add(a, ram[hl]); cycles += 8; break; }
	case 0x87: { op_add(a, a);	cycles += 4; break; } 
	case 0x88: { op_adc(a, b);	cycles += 4; break; } 
	case 0x89: { op_adc(a, c);	cycles += 4; break; } 
	case 0x8A: { op_adc(a, d);	cycles += 4; break; } 
	case 0x8B: { op_adc(a, e);	cycles += 4; break; } 
	case 0x8C: { op_adc(a, h);	cycles += 4; break; } 
	case 0x8D: { op_adc(a, l);	cycles += 4; break; } 
	case 0x8E: { op_adc(a, ram[hl]); cycles += 8;  break; }
	case 0x8F: { op_adc(a, a); cycles += 4; break; }

	case 0x90: { op_sub(a, b); cycles += 4; break; }
	case 0x91: { op_sub(a, c); cycles += 4; break; }
	case 0x92: { op_sub(a, d); cycles += 4; break; }
	case 0x93: { op_sub(a, e); cycles += 4; break; }
	case 0x94: { op_sub(a, h); cycles += 4; break; }
	case 0x95: { op_sub(a, l); cycles += 4; break; }
	case 0x96: { op_sub(a, ram[hl]); cycles += 8; break; }
	case 0x97: { op_sub(a, a); cycles += 4; break; }
	case 0x98: { op_sbc(a, b); cycles += 4; break; }
	case 0x99: { op_sbc(a, c); cycles += 4; break; }
	case 0x9A: { op_sbc(a, d); cycles += 4; break; }
	case 0x9B: { op_sbc(a, e); cycles += 4; break; }
	case 0x9C: { op_sbc(a, h); cycles += 4; break; }
	case 0x9D: { op_sbc(a, l); cycles += 4; break; }
	case 0x9E: { op_sbc(a, ram[hl]); cycles += 8; break; }
	case 0x9F: { op_sbc(a, a); cycles += 4; break; }

	case 0xA0: { op_and(b); cycles += 4; break; }	
	case 0xA1: { op_and(c); cycles += 4; break; }	
	case 0xA2: { op_and(d); cycles += 4; break; }	
	case 0xA3: { op_and(e); cycles += 4; break; }	
	case 0xA4: { op_and(h); cycles += 4; break; }	
	case 0xA5: { op_and(l); cycles += 4; break; }	
	case 0xA6: { op_and(ram[hl]); cycles += 4; break; }
	case 0xA7: { op_and(a); cycles += 4; break; }	
	case 0xA8: { op_xor(b); cycles += 4; break; }	
	case 0xA9: { op_xor(c); cycles += 4; break; }	
	case 0xAA: { op_xor(d); cycles += 4; break; }	
	case 0xAB: { op_xor(e); cycles += 4; break; }	
	case 0xAC: { op_xor(h); cycles += 4; break; }	
	case 0xAD: { op_xor(l); cycles += 4; break; }	
	case 0xAE: { op_xor(ram[hl]); cycles += 8; break; }
	case 0xAF: { op_xor(a);  cycles += 4; break; }

	case 0xB0: { op_or(b);		cycles += 4;		break; }
	case 0xB1: { op_or(c);		cycles += 4;		break; }
	case 0xB2: { op_or(d);		cycles += 4;		break; }
	case 0xB3: { op_or(e);		cycles += 4;		break; }
	case 0xB4: { op_or(h);		cycles += 4;		break; }
	case 0xB5: { op_or(l);		cycles += 4;		break; }
	case 0xB6: { op_or(ram[hl]);cycles += 8; break; }
	case 0xB7: { op_or(a); cycles += 4;		break; }
	case 0xB8: { op_cp(b); cycles += 4;		break; }
	case 0xB9: { op_cp(c); cycles += 4;		break; }
	case 0xBA: { op_cp(d); cycles += 4;		break; }
	case 0xBB: { op_cp(e); cycles += 4;		break; }
	case 0xBC: { op_cp(h); cycles += 4;		break; }
	case 0xBD: { op_cp(l); cycles += 4;		break; }
	case 0xBE: { op_cp(ram[hl]); cycles += 8; break; }
	case 0xBF: { op_cp(a);		cycles += 4; break; }

	case 0xC0: { op_ret(NZ); break; }		
	case 0xC1: { op_pop(bc); break; }		
	case 0xC2: { op_jp(NZ); break; }	
	case 0xC3: { op_jp(); break; }		
	case 0xC4: { op_call(NZ); break; }	
	case 0xC5: { op_push(bc); break; }		
	case 0xC6: { op_add(a, get_d8()); break; }	
//	case 0xC7: { op_rst(00h); break; }		
	case 0xC8: { op_ret(Z); break; }		
	case 0xC9: { op_ret(); break; }			
	case 0xCA: { op_jp(Z); break; }	
	case 0xCC: { op_call(Z); break; }
	case 0xCD: { op_call(); break; }
	case 0xCE: { op_adc(a, get_d8()); break; }
//	case 0xCF: { op_rst(08H); break; }

	case 0xD0: { op_ret(NC); break; }
	case 0xD1: { op_pop(de); break; }
	case 0xD2: { op_jp(NC); break; }
	case 0xD3: { op_undefined(); break; }
	case 0xD4: { op_call(NC); break; }
	case 0xD5: { op_push(de); break; }
	case 0xD6: { op_sub(a, get_d8()); break; }
//	case 0xD7: { op_rst(10h); break; }
	case 0xD8: { op_ret(C); break; }
	case 0xD9: { op_ret(); op_ei(); break; }
	case 0xDA: { op_jp(C); break; }
	case 0xDB: { op_undefined(); break; }
	case 0xDC: { op_call(C); break; }
	case 0xDD: { op_undefined(); break; }
	case 0xDE: { op_sbc(a, get_d8()); break; }
//	case 0xDF: { op_rst(18h); break; }

	case 0xE0: { op_ld(ram[0xFF00 + get_d8()], a);	cycles += 12; break; }
	case 0xE1: { op_pop(hl); break; }		
	case 0xE2: { op_ld(ram[0xFF00 + c], a); break; }	
	case 0xE3: { op_undefined(); break; }	
	case 0xE4: { op_undefined(); break; }	
	case 0xE5: { op_push(hl); break; }		
	case 0xE6: { op_and(get_d8()); break; }		
	case 0xE7: { op_rst(get_d8()); break; }		
	case 0xE8: { op_add(sp, get_s8()); break; }	
	case 0xE9: { op_jp(ram[hl]); cycles += 4; break; }
	case 0xEA: { set_d16(a); cycles += 16; break; }
	case 0xEB: { op_undefined(); break; }	
	case 0xEC: { op_call(Z); break; }	
	case 0xED: { op_call(); break; }		
	case 0xEE: { op_xor(get_d8()); break; }		
	case 0xEF: { op_rst(get_d8()); break; }		
	
//	case 0xF0: { op_ldh(a, a8); break; }
	case 0xF1: { op_pop(de); break; }
	case 0xF2: { op_ld(a, ram[0xFF00+c]); break; }
	case 0xF3: { op_di(); break; }
	case 0xF4: { op_undefined(); break; }
	case 0xF5: { op_push(af); break; }
	case 0xF6: { op_or(get_d8()); break; }
//	case 0xF7: { op_rst(30h); break; }
//	case 0xF8: { op_ld(hl, (sp + get_s8())); break; }
	case 0xF9: { op_ld(sp, hl); break; }
	case 0xFA: { op_ld(a, get_d16()); break; }
	case 0xFB: { op_ei(); break; }
	case 0xFC: { op_call(C); break; }
	case 0xFD: { op_undefined(); break; }
	case 0xFE: { op_cp(get_d8()); break; }
//	case 0xFF: { op_rst(38h); break; }




	}
}


