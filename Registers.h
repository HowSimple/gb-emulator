#pragma once
#include <cstdint>


typedef uint8_t _8b;
typedef uint16_t _16b;

struct Registers
{	// registers can be accessed individually or as a pair
	// each pair of registers occupies the same 16bit location
	struct {
		union {
			struct {
				_8b f;
				_8b a;
			};
			_16b af;
		};
	};
	struct {
		union {
			struct {
				_8b c;
				_8b b;
			};
			_16b bc;
		};
	};
	struct {
		union {
			struct {
				_8b e;
				_8b d;
			};
			_16b de;
		};
	};
	struct {
		union {
			struct {
				_8b l;
				_8b h;
			};
			_16b hl;
		};
	};
	_16b sp;
	_16b pc;

};

