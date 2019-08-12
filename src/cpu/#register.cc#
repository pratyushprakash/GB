#include "cpu.hpp"

RegisterPair::RegisterPair() : upper(nullptr), lower(nullptr) {}

RegisterPair::RegisterPair(u8 *upper, u8 *lower) : upper(upper), lower(lower) {}

u16 RegisterPair::get() { return (*upper << 8 | *lower); }

void RegisterPair::set(u16 val) {
  *upper = val >> 8;
  *lower = val & 0x00FF;
}

void CPU::set_flag_zero(bool set){
  if(set) f = f | (1 << 7);
  else
    f = f & ~(1 << 7);
}

void CPU::set_flag_subtract(bool set){
  if(set) f = f | (1 << 6);
  else
    f = f & ~(1 << 6);
}

void CPU::set_flag_half_carry(bool set){
  if(set) f = f | (1 << 5);
  else
    f = f & ~(1 << 5);
}

void CPU::set_flag_carry(bool set){
  if(set) f = f | (1 << 4);
  else
    f = f & ~(1 << 4);
}

bool CPU::get_flag_zero(){
  return (((f >> 7) & 1) == 1);
}

bool CPU::get_flag_subtract(){
  return (((f >> 6) & 1) == 1);
}

bool CPU::get_flag_half_carry(){
  return (((f >> 5) & 1) == 1);
}

bool CPU::get_flag_carry(){
  return (((f >> 4) & 1) == 1);
}
