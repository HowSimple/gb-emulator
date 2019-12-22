#include "Registers.h"
#include"CPU.h"
enum operand { A , B, C, D, E, H, L , HL};
enum operation {LD, ADD, ADC, SUB, SBC, AND, XOR, OR, CP};
operand operand_offset(operand op, int offset)
{
	return static_cast<operand>(static_cast<int>(static_cast<operand>(offset) + op));
}


void CPU::decode_opcode(u1 opcode)
{
	
	unsigned char high = opcode & 0x0f;
	unsigned char low = (opcode >> 4) & 0x0f;
	operand operand1;
	operand operand2;
	operation op;
	int offset = 0; //
	switch (low)
	{
	case 1: {
		operand2 = operand::C;
		break;
	}
	case 2: {
		operand2 = D;
		break;
	}
	case 3: {
		operand2 = E;
		break;
	}
	case 4: {
		operand2 = H;
		break;
	}
	case 5: {
		operand2 = L;
		break;
	}
	case 6: {
		operand2 = HL;
		break;
	}
	case 7: {
		operand2 = A;
		break;
	}
	case 8: {
		operand2 = B;
		offset = 1;
		break;
	}
	case 9: {
		operand2 = C;
		offset = 1;
		break;
	}
	case 'A': {
		operand2 = D;
		offset = 1;
		break;
	}
	case 'B': {
		operand2 = E;
		offset = 1;
		break;
	}
	case 'C': {
		operand2 = H;
		offset = 1;
		break;
	}
	case 'D': {
		operand2 = L;
		offset = 1;
		break;
	}
	case 'E': {
		operand2 = HL;
		offset = 1;
		break;
	}
	case 'F': {
		operand2 = A;
		offset = 1;
		break;
	}
	}
	
	
	switch (high)
	{
	case 4: {
		op = LD;
		operand1 = operand_offset(B, offset);
		break;
	}
	case 5: {
		op = LD;
		operand1 = operand_offset(D, offset);
		break;
	}
	case 6: {
		op = LD;
		operand1 = operand_offset(H, offset);
		break;
	}

	case 7: {
		op = LD;
		operand1 = operand_offset(HL, offset);
		break;
	}
	case 8: {
		operand1 = A;
		op = operand_offset(ADD, offset);
		break;
	}

	case 9: {
		operand1 = A;
		op = operand_offset(SUB, offset);
		break;
	}
	case 'A': {
		operand1 = operand2;
		op = operand_offset(AND, offset);
		break;
	}
	case 'B': {
		operand1 = operand2;
		op = operand_offset(ADD, offset);
		break;
	}



	}



}