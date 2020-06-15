#pragma once

#include <cstdint>
#include <string>


class Chip8 {
private:
  uint16_t stack[16];             // Stack
  uint16_t sp;                    // Stack pointer

  uint8_t memory[1024 * 4];       // Memory (4k)
  uint8_t V[16];                  // V registers (V0-VF)

  uint16_t pc;                    // Program counter
  uint16_t opcode;                // Current opcode
  uint16_t I;                     // Index register

  uint8_t delay_timer;            // Delay timer
  uint8_t sound_timer;            // Sound timer

  void init();

public:
  uint8_t gfx[64 * 32];           // Graphic buffer
  uint8_t key[16];                // Keypad
  bool drawFlag;                  // Indicates a draw has occured

  Chip8();
  ~Chip8();

  void emulateCycle();           // Emulate one cpu cycle
  bool load(const std::string file_path); // Load the rom file

};


