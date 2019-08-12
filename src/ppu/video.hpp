#pragma once

#include "../cpu/cpu.hpp"
#include "../mmu/mmu.hpp"
#include "framebuffer.hpp"
#include "tile.hpp"

enum class PPUMode { OAMAccess, VRAMAccess, HBlank, VBlank };

class PPU {
public:
  PPU(CPU &cpu, MMU &mmu);
  void tick(uint cycles);

  u8 LCD_control;
  u8 LCD_status;

private:
};
