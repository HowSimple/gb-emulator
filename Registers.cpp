#include "Registers.h"

void Registers::set_af(_16b data)
{
	a = data << a;
	f = data >> f;
}
