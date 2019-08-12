#pragma once

#include "color.hpp"
#include "../mmu/mmu.hpp"

#include <vector>

const uint TILE_PIXEL_HEIGHT = 8;
const uint TILE_PIXEL_WIDTH = 8;

class Tile {
public:
  Tile(u16 addr, MMU& mmu, uint multiplier);

  GBColor get_pixel(uint x, uint y) const;
private:
  MMU &mmu;

  static uint get_pixel_index(uint x, uint y);
  std::vector<u8> get_pixel_line_from_memory(u16 addr);

  GBColor buffer[TILE_PIXEL_HEIGHT * TILE_PIXEL_WIDTH];
};
