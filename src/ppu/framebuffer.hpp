#pragma once

#include "../definitions.hpp"
#include "color.hpp"

#include <vector>

class FrameBuffer {
public:
  FrameBuffer(uint height, uint width);
  void set_pixel(uint x, uint y, Color color);
  Color get_pixel(uint x, uint y);
  void reset();

private:
  uint height;
  uint width;

  uint get_pixel_index(uint x, uint y);
  std::vector<Color> buffer;
};
