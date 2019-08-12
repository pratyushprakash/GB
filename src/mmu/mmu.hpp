// WORK IN PROGRESS
//   FINISH VIDEO, INPUT, TIMER FIRST


#pragma once

#include "../definitions.hpp"
#include "../cartridge/cartridge.h"

#include <vector>

class MMU {
  public:
  MMU(Cartridge *cart);
  u8 read(u16 loc) const;
  void write(u16 loc, u8 val);
  private:
  std::vector<u8> memory;
  Cartridge *cartridge ;
};
