#include <iostream>
#include "SDL.h"
#include "Emulator.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    Emulator emu;
    SDL_Window* window = SDL_CreateWindow("SimpleboyGB", 100, 100, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Texture* texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_HEIGHT, SCREEN_WIDTH);
    Uint32* pixels = reinterpret_cast<Uint32*>(*emu.gb.gpu.screen);//static_cast<Uint32>(gb.gpu.screen);//new Uint32[160 * 144];
    while (true)
    {
        emu.update_cpu();
        emu.update_video(emu.gb.cycles);
        SDL_UpdateTexture(texture, NULL, pixels, 160 * sizeof(Uint32));

    }
    delete[] pixels;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    return 0;

}



void Emulator::update_cpu()
{
    int max_cpu_cycles = 69905; // 
       gb.cycles = 0;

    while (gb.cycles < max_cpu_cycles)
    {
        gb.execute_opcode(gb.fetch_opcode());
        update_video(gb.cycles);
        update_input();
        gb.run_interrupts();
        
    }
    
}
void Emulator::update_input()
{
    u8 joypad_state = 0;
    SDL_PumpEvents();
    const Uint8* input = SDL_GetKeyboardState(NULL);
    
    if ( (!input[SDL_SCANCODE_RETURN] && !input[SDL_SCANCODE_SPACE] 
        && !input[SDL_SCANCODE_Z] && !input[SDL_SCANCODE_X]) )
    {
        joypad_state |= 1 << 4; // selects d-pad 

      if (input[SDL_SCANCODE_UP])
        joypad_state |= 1 << 2;//UP BUTTON
      if (input[SDL_SCANCODE_DOWN])
        joypad_state |= 1 << 3;//DOWN BUTTON
      if (input[SDL_SCANCODE_LEFT])
        joypad_state |= 1 << 1;//LEFT BUTTON
      if (input[SDL_SCANCODE_RIGHT])
        joypad_state |= 1 << 0;//RIGHT BUTTON
    }
    else
    {
        joypad_state |= 1 << 5; // selects buttons

       if (input[SDL_SCANCODE_Z])
          joypad_state |= 1 << 0;//A BUTTON
       if (input[SDL_SCANCODE_X])
          joypad_state |= 1 << 1;// B BUTTON
       
       if (input[SDL_SCANCODE_RETURN])
           joypad_state |= 1 << 2; //SELECT BUTTON
       if (input[SDL_SCANCODE_SPACE])
           joypad_state |= 1 << 3; // START BUTTON
    }
    gb.write_mem(0xFF00, joypad_state);
     if (input[SDL_SCANCODE_ESCAPE])
        SDL_Quit();
}
void Emulator::update_video(u8 cycles)
{
    if (gb.gpu.LCD_ENABLE)
        gb.gpu.current_scanline_y -= cycles;

    if (gb.gpu.current_scanline_y > gb.gpu.MAX_SCANLINE_Y)
        gb.gpu.current_scanline_y = 0;
    gb.gpu.draw_scanline();
    
}
