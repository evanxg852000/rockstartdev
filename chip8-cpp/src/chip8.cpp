#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <fstream>

#include "chip8.hpp"

unsigned char chip8_fontset[80] = {
  0xF0, 0x90, 0x90, 0x90, 0xF0, //0
  0x20, 0x60, 0x20, 0x20, 0x70, //1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
  0x90, 0x90, 0xF0, 0x10, 0x10, //4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
  0xF0, 0x10, 0x20, 0x40, 0x40, //7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
  0xF0, 0x90, 0xF0, 0x90, 0x90, //A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
  0xF0, 0x80, 0x80, 0x80, 0xF0, //C
  0xE0, 0x90, 0x90, 0x90, 0xE0, //D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
  0xF0, 0x80, 0xF0, 0x80, 0x80  //F
};

Chip8::Chip8() {

}

Chip8::~Chip8() {

}

// Initialize
void Chip8::init() {
  pc = 0x200; // set program counter to start 0x200
  opcode = 0; // reset opcode
  I = 0; // reset I
  sp =  0; // reset stack pointer

  // clear the display buffer
  for(int i = 0; i < (64 * 32); ++i) {
    gfx[i] = 0;
  }

  //clear the stack, keyboard, and V registers
  for(int i = 0; i < 16; ++i){
    stack[i] = 0;
    key[i] = 0;
    V[i] = 0;
  }

  // clear memory
  for(int i = 0; i < (1024 * 4); ++i) {
    memory[i] = 0;
  }

  // Load font set into memory
  for(int i = 0; i < 80; ++i) {
    memory[i] = chip8_fontset[i];
  }

  //reset timers
  delay_timer = 0;
  sound_timer = 0;

  srand(time(NULL));

}

// init and load room
bool Chip8::load(std::string fpath) {
  init();
  std::cout << "Loading ROM: " << fpath << std::endl;

  std::ifstream ifile(fpath, std::ios::binary);
  std::vector<char> rom(
    (std::istreambuf_iterator<char>(ifile)),
    (std::istreambuf_iterator<char>())
  );
  ifile.close();

  if( (4096-512) <= rom.size()) {
    std::cerr << "ROM too large to fit in memory" << std::endl;
    return false;
  }

  // copy rom to memory
  for (size_t i=0; i < rom.size(); ++i) {
    memory[512+i] = (uint8_t) rom.at(i);
  }
  
  return true;
}

// emulate 
void Chip8::emulateCycle(){
  //fetch opcode
  opcode = memory[pc] << 8 | memory[pc+1]; //op[code is two bytes
  
  switch(opcode & 0xF000) {
    // 00E_
    case 0x000:
      switch(opcode &0x000F){
        //00E0 - clear screen
        case 0x000:
          for(int i=0; i<2048; ++i){
            gfx[i]=0;
          }
          drawFlag = true;
          pc += 2;
          break;

        //00EE - return from subroutine
        case 0x000E:
          --sp;
          pc = stack[sp];
          pc += 2;
          break;

        default:
          std::cerr << "unknow opcode" << opcode << std::endl;
          exit(3);
      }
      break;
    
    // 1NNN - jumps to address NNN
    case 0x1000:
      pc = opcode & 0x0FFF;
      break;

    // 2NNN - calls subroutine at NNN
    case 0x2000:
      stack[sp]=pc;
      ++sp;
      pc = opcode & 0x0FFF;
      break;

    // 3XNN - skips the next instruction if VX equals NN
    case 0x3000:
      if(V[(opcode &0x0F00) >> 8] == (opcode & 0x00FF)){
        pc += 4;
      } else {
        pc += 2;
      }
      break;

    // 4XNN - skips the next instruction if VX does not equal NN
    case 0x4000:
      if(V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
        pc += 4;
      } else {
        pc += 2;
      }
      break;

    // 5XY0 - skips the next instruction if VX equals VY
    case 0x5000:
      if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]){
        pc += 4;
      } else {
        pc += 2;
      }
      break;

  // 6XNN - sets VX to NN.
  case 0x6000:
    V[(opcode & 0x0F00) >> 8] = opcode & 0x00FF;
    pc += 2;
    break;

  // 7XNN - adds NN to VX.
  case 0x7000:
    V[(opcode & 0x0F00) >> 8] += opcode & 0x00FF;
    pc += 2;
    break;
  
  // 8XY_
  case 0x8000:
    switch (opcode & 0x000F){

      //8XY0 - sets VX to the value of VY
      case 0x0000:
        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4];
        pc += 2;
        break;

      // 8XY1 - sets VX to (VX OR VY)
      case 0x0001:
        V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];
        pc += 2;
        break;

      // 8XY2 - sets VX to (VX AND VY)
      case 0x0002:
        V[(opcode & 0x0F00) >> 8]  &= V[(opcode & 0x00F0) >> 4];
        pc += 2;
        break;

      // 8XY3 - sets VX to (VX XOR VY)
      case 0x0003:
        V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];
        pc += 2;
        break;

      // 8XY4 - adds VY to VX, VF is set to 1 when there's a carry
      // and to 0 when there isn't
      case 0x0004:
        V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];
        if( V[(opcode & 0x00F0) >> 4] > (0xFF - V[(opcode & 0x0F00) >> 8]))
            V[0xF] = 1;
        else 
          V[0xF] = 0;
        pc += 2;
        break;

      // 8XY5 - VY is subtracted from VX. VF is set to 0 when
      // there's a borrow, and 1 when there isn't.
      case 0x0005:
        if(V[(opcode & 0x00F0) >> 4] > V[(opcode & 0x0F00) >> 8])
            V[0xF] = 0; // there is a borrow
        else
            V[0xF] = 1;
        V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];
        pc += 2;
        break;

      // 0x8XY6 - Shifts VX right by one. VF is set to the value of
      // the least significant bit of VX before the shift.
      case 0x0006:
        V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;
        V[(opcode & 0x0F00) >> 8] >>= 1;
        pc += 2;
        break;

      // 0x8XY7: Sets VX to VY minus VX. VF is set to 0 when there's
      // a borrow, and 1 when there isn't.
      case 0x0007:
        if(V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4])	// VY-VX
            V[0xF] = 0; // there is a borrow
        else
            V[0xF] = 1;
        V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];
        pc += 2;
        break;

      // 0x8XYE: Shifts VX left by one. VF is set to the value of
      // the most significant bit of VX before the shift.
      case 0x000E:
        V[0xF] = V[(opcode & 0x0F00) >> 8] >> 7;
        V[(opcode & 0x0F00) >> 8] <<= 1;
        pc += 2;
        break;

      default:
        std::cerr << "unknow opcode" << opcode << std::endl;
        exit(3);
    }
    break;

    // 9XY0 - Skips the next instruction if VX doesn't equal VY.
    case 0x9000:
        if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4])
            pc += 4;
        else
            pc += 2;
        break;

    // ANNN - Sets I to the address NNN.
    case 0xA000:
        I = opcode & 0x0FFF;
        pc += 2;
        break;

    // BNNN - Jumps to the address NNN plus V0.
    case 0xB000:
        pc = (opcode & 0x0FFF) + V[0];
        break;

    // CXNN - Sets VX to a random number, masked by NN.
    case 0xC000:
        V[(opcode & 0x0F00) >> 8] = (rand() % (0xFF + 1)) & (opcode & 0x00FF);
        pc += 2;
        break;

    // DXYN: Draws a sprite at coordinate (VX, VY) that has a width of 8
    // pixels and a height of N pixels.
    // Each row of 8 pixels is read as bit-coded starting from memory
    // location I;
    // I value doesn't change after the execution of this instruction.
    // VF is set to 1 if any screen pixels are flipped from set to unset
    // when the sprite is drawn, and to 0 if that doesn't happen.
    case 0xD000: {
      unsigned short x = V[(opcode & 0x0F00) >> 8];
      unsigned short y = V[(opcode & 0x00F0) >> 4];
      unsigned short height = opcode & 0x000F;
      unsigned short pixel;

      V[0xF] = 0;
      for (int yline = 0; yline < height; yline++) {
        pixel = memory[I + yline];
        for(int xline = 0; xline < 8; xline++) {
          if((pixel & (0x80 >> xline)) != 0) {
            if(gfx[(x + xline + ((y + yline) * 64))] == 1) {
                V[0xF] = 1;
            }
            gfx[x + xline + ((y + yline) * 64)] ^= 1;
          }
        }
      }

      drawFlag = true;
      pc += 2;
    }
    break;

    // EX__
    case 0xE000:
      switch (opcode & 0x00FF) {
          // EX9E - Skips the next instruction if the key stored
          // in VX is pressed.
          case 0x009E:
              if (key[V[(opcode & 0x0F00) >> 8]] != 0)
                  pc +=  4;
              else
                  pc += 2;
              break;

          // EXA1 - Skips the next instruction if the key stored
          // in VX isn't pressed.
          case 0x00A1:
              if (key[V[(opcode & 0x0F00) >> 8]] == 0)
                  pc +=  4;
              else
                  pc += 2;
              break;

          default:
              printf("\nUnknown op code: %.4X\n", opcode);
              exit(3);
      }
      break;

    // FX__
    case 0xF000:
      switch(opcode & 0x00FF)
      {
          // FX07 - Sets VX to the value of the delay timer
          case 0x0007:
              V[(opcode & 0x0F00) >> 8] = delay_timer;
              pc += 2;
              break;

          // FX0A - A key press is awaited, and then stored in VX
          case 0x000A:
          {
              bool key_pressed = false;

              for(int i = 0; i < 16; ++i)
              {
                  if(key[i] != 0)
                  {
                      V[(opcode & 0x0F00) >> 8] = i;
                      key_pressed = true;
                  }
              }

              // If no key is pressed, return and try again.
              if(!key_pressed)
                  return;

              pc += 2;
          }
              break;

          // FX15 - Sets the delay timer to VX
          case 0x0015:
              delay_timer = V[(opcode & 0x0F00) >> 8];
              pc += 2;
              break;

          // FX18 - Sets the sound timer to VX
          case 0x0018:
              sound_timer = V[(opcode & 0x0F00) >> 8];
              pc += 2;
              break;

          // FX1E - Adds VX to I
          case 0x001E:
              // VF is set to 1 when range overflow (I+VX>0xFFF), and 0
              // when there isn't.
              if(I + V[(opcode & 0x0F00) >> 8] > 0xFFF)
                  V[0xF] = 1;
              else
                  V[0xF] = 0;
              I += V[(opcode & 0x0F00) >> 8];
              pc += 2;
              break;

          // FX29 - Sets I to the location of the sprite for the
          // character in VX. Characters 0-F (in hexadecimal) are
          // represented by a 4x5 font
          case 0x0029:
              I = V[(opcode & 0x0F00) >> 8] * 0x5;
              pc += 2;
              break;

          // FX33 - Stores the Binary-coded decimal representation of VX
          // at the addresses I, I plus 1, and I plus 2
          case 0x0033:
              memory[I]     = V[(opcode & 0x0F00) >> 8] / 100;
              memory[I + 1] = (V[(opcode & 0x0F00) >> 8] / 10) % 10;
              memory[I + 2] = V[(opcode & 0x0F00) >> 8] % 10;
              pc += 2;
              break;

          // FX55 - Stores V0 to VX in memory starting at address I
          case 0x0055:
              for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
                  memory[I + i] = V[i];

              // On the original interpreter, when the
              // operation is done, I = I + X + 1.
              I += ((opcode & 0x0F00) >> 8) + 1;
              pc += 2;
              break;

          case 0x0065:
              for (int i = 0; i <= ((opcode & 0x0F00) >> 8); ++i)
                  V[i] = memory[I + i];

              // On the original interpreter,
              // when the operation is done, I = I + X + 1.
              I += ((opcode & 0x0F00) >> 8) + 1;
              pc += 2;
              break;

          default:
              std::cerr << "Unknown opcode" << opcode << std::endl;
      }
      break;

    default:
      std::cerr << "Unimplemented op code" << opcode << std::endl;
      exit(3);
  }

  // Update timers
  if (delay_timer > 0)
    --delay_timer;

  if (sound_timer > 0)
      //if(sound_timer == 1);
      // TODO: Implement sound
      --sound_timer;
}



