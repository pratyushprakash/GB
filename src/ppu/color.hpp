#pragma once

#include "../definitions.hpp"

enum class GBColor{
  Color0,
  Color1,
  Color2,
  Color3
};

enum class Color{
  White,
  LightGray,
  DarkGray,
  Black,
};

GBColor get_color(u8 pixel_value);
