#include "mmu.hpp"

MMU::MMU(Cartridge *cart) : cartridge(cart) {
  memory = std::vector<u8>(0xFFFF + 1, 0);
}

u8 MMU::read(u16 loc) const {
  if (0 <= loc && loc < 0x8000)
    return cartridge->read(loc);
  else if (0x8000 <= loc && loc < 0xA000)
    return memory.at(loc);
  else if (0xA000 <= loc && loc < 0xC000)
    return cartridge->read(loc);
  else if (0xC000 <= loc && loc < 0xE000)
    return memory.at(loc);
  else if (0xE000 <= loc && loc < 0xFE00)
    return memory.at(loc - 0x2000);
  else if (0xFE00 <= loc && loc < 0xFEA0)
    return memory.at(loc);
  else if (0xFEA0 <= loc && loc < 0xFF00)
    return 0xFF; // Empty but unusable
  else if (0xFF00 <= loc && loc < 0xFF4C)
    return memory.at(loc); // I/O ports
  else if (0xFF4C <= loc && loc < 0xFF80)
    return 0xFF; // Empty but unusable
  else if (0xFF80 <= loc && loc < 0xFFFF)
    return memory.at(loc);
  else if (loc == 0xFFFF)
    return memory.at(loc); // Interupt enable register

  return 0xFF;
}

void MMU::write(u16 loc, u8 val){
  if (0 <= loc && loc < 0x8000)
    cartridge->write(loc, val);
  else if (0x8000 <= loc && loc < 0xA000)
    memory.at(loc) = val;
  else if (0xA000 <= loc && loc < 0xC000)
    cartridge->write(loc, val);
  else if (0xC000 <= loc && loc < 0xE000)
    memory.at(loc) = val;
  else if (0xE000 <= loc && loc < 0xFE00)
    memory.at(loc - 0x2000) = val;
  else if (0xFE00 <= loc && loc < 0xFEA0)
    memory.at(loc) = val;
  else if (0xFEA0 <= loc && loc < 0xFF00)
    // Not usable
    return;
  else if (0xFF00 <= loc && loc < 0xFF4C)
    // I/O Ports
    memory.at(loc) = val;
  else if (0xFF4C <= loc && loc < 0xFF80)
    // Not usable
    return;
  else if (0xFF80 <= loc && loc < 0xFFFF)
    memory.at(loc) = val;
  else if (loc == 0xFFFF)
    // Interupt Enable Register
    memory.at(loc) = val;
}
