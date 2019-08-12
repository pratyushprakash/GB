#include "tile.hpp"

Tile::Tile(u16 addr, MMU &mmu_t, uint multiplier) : mmu(mmu_t) {
  for (uint y = 0; y < TILE_PIXEL_HEIGHT * multiplier; y++) {
    for (uint x = 0; x < TILE_PIXEL_WIDTH; x++)
      buffer[get_pixel_index(x, y)] = GBColor::Color0;
  }

  for (uint y = 0; y < TILE_PIXEL_HEIGHT * multiplier; y++) {
    std::vector<u8> pixel_line = get_pixel_line_from_memory(addr);
    // Two bytes per pixel line in a tile
    addr += 2;
    for (uint x = 0; x < TILE_PIXEL_WIDTH; x++)
      buffer[get_pixel_index(x, y)] = get_color(pixel_line[x]);
  }
}

std::vector<u8> Tile::get_pixel_line_from_memory(u16 addr) {
  u8 byte1 = mmu.read(addr);
  u8 byte2 = mmu.read(addr + 1);

  std::vector<u8> pixel_line;

  for (int i = 0; i < 8; i++) {
    u8 upper_bit = (byte2 >> (7 - i)) & 1;
    u8 lower_bit = (byte1 >> (7 - i)) & 1;
    u8 color_val = upper_bit << 1 | lower_bit;
    pixel_line.push_back(color_val);
  }

  return pixel_line;
}

GBColor Tile::get_pixel(uint x, uint y) const {
  return buffer[get_pixel_index(x, y)];
}

uint Tile::get_pixel_index(uint x, uint y) { return y * TILE_PIXEL_HEIGHT + x; }
