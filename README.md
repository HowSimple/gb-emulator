# simpleboy
This is a work-in-progress Gameboy emulator, written in C++, using [SDL2](https://www.libsdl.org/download-2.0.php).

Unit tests use [Google Test](https://github.com/google/googletest).

Status:

Most CPU instructions work. 
Opcode fetching/decoding works. 
Loading a ROM file works.

Keyboard input is implemented, but has not yet been tested.
Interrupt handling is implemented, but has not yet been tested.
Graphics are not working. 

TODO:
Sprite support.

Timer register support.

Unit tests for the graphics system.
Unit tests for interrupt handling.

MBC support (to support games larger than 32KB). 

Sound support.

