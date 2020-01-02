#include <iostream>
#include "SDL.h"
#include "Emulator.h"

void Emulator::updateCPU()
{
    int max_cpu_cycles = 69905; // 
    gb.cycles = 0;

    while (gb.cycles < max_cpu_cycles)
    {
        gb.execute_opcode(gb.fetch_opcode());
        updateVideo(gb.cycles);
    }
    renderScreen();
}
void Emulator::updateVideo(u8 cycles)
{



}
int Emulator::main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
     SDL_Window* win = SDL_CreateWindow("my window", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
     while (true)
     {

     }
    
    
    return 0;

}
