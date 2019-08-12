#include "cpu.hpp"

void CPU::nop() {
  // Do Nothing
}

void CPU::ld(RegisterPair &reg, u16 d16) { reg.set(d16); }

void CPU::ld(u16 &reg, u16 d16) { reg = d16; }

void CPU::ld(u8 &reg, u8 d8) { reg = d8; }

void CPU::ld_to_addr(u16 addr, u8 d8) { mmu.write(addr, d8); }

void CPU::halt() { halted = true; }

void CPU::inc(RegisterPair &reg) { reg.set(reg.get() + 1); }

void CPU::inc(u16 &reg) { reg = reg + 1; }

void CPU::inc(u8 &reg) {
  reg = reg + 1;

  set_flag_zero(reg == 0);
  set_flag_subtract(false);
  set_flag_half_carry((reg & 0x0F) == 0x0F);
}

void CPU::inc_addr(u16 addr) {
  u8 val = mmu.read(addr) + 1;
  mmu.write(addr, val);

  set_flag_zero(val == 0);
  set_flag_subtract(false);
  set_flag_half_carry((val & 0x0F) == 0x0F);
}

void CPU::dec(u8 &reg) {
  reg = reg - 1;

  set_flag_zero(reg == 0);
  set_flag_subtract(true);
  set_flag_half_carry((reg & 0x0F) == 0x0F);
}

void CPU::dec(RegisterPair &reg) { reg.set(reg.get() - 1); }

void CPU::dec(u16 &reg) { reg = reg - 1; }

void CPU::dec_addr(u16 addr) {
  u8 val = mmu.read(addr) - 1;
  mmu.write(addr, val);

  set_flag_zero(val == 0);
  set_flag_subtract(true);
  set_flag_half_carry((val & 0x0F) == 0x0F);
}

void CPU::add_a(u8 reg, u8 val) {
  u8 result = reg + val;

  a = static_cast<u8>(result);

  set_flag_subtract(false);
  set_flag_zero(a == 0);
  set_flag_half_carry((reg & 0xf) + (val & 0xf) > 0xf);
  set_flag_carry(result > 0xff);
}

void CPU::add_hl(u16 val) {
  u16 result = hl.get() + val;

  set_flag_subtract(false);
  set_flag_half_carry((hl.get() & 0xf) + (val & 0xf) > 0xf);
  set_flag_carry(result > 0xff);

  hl.set(static_cast<u16>(result));
}

void CPU::add_hl(RegisterPair val) {
  u16 result = hl.get() + val.get();

  set_flag_subtract(false);
  set_flag_half_carry((hl.get() & 0xf) + (val.get() & 0xf) > 0xf);
  set_flag_carry(result > 0xff);

  hl.set(static_cast<u16>(result));
}

void CPU::adc(u8 val) {
  u8 carry = get_flag_carry();
  u8 result_full = a + val + carry;
  u8 result = static_cast<u8>(result_full);

  set_flag_subtract(false);
  set_flag_zero(result == 0);
  set_flag_half_carry((a & 0xf) + (val & 0xf) + carry > 0xf);
  set_flag_carry(result_full > 0xff);

  a = result;
}

void CPU::sub_a(u8 reg, u8 val) {
  u8 result = reg - val;

  a = static_cast<u8>(result);

  set_flag_subtract(true);
  set_flag_zero(a == 0);
  set_flag_half_carry((reg & 0xf) - (val & 0xf) < 0);
  set_flag_carry(reg < val);
}

void CPU::sbc(u8 reg, u8 val) {
  u8 carry = get_flag_carry();
  u8 result_full = reg - val - carry;
  u8 result = static_cast<u8>(result_full);

  set_flag_subtract(true);
  set_flag_zero(result == 0);
  set_flag_half_carry((a & 0xf) - (val & 0xf) - carry < 0);
  set_flag_carry(result_full < 0);

  a = result;
}

void CPU::and_a(u8 reg, u8 val) {
  u8 result = reg & val;
  a = result;

  set_flag_zero(result == 0);
  set_flag_subtract(false);
  set_flag_carry(false);
  set_flag_half_carry(true);
}

void CPU::or_a(u8 reg, u8 val) {
  u8 result = reg | val;
  a = result;

  set_flag_zero(result == 0);
  set_flag_subtract(false);
  set_flag_carry(false);
  set_flag_half_carry(false);
}

void CPU::xor_a(u8 reg, u8 val) {
  u8 result = reg ^ val;
  a = result;

  set_flag_zero(result == 0);
  set_flag_subtract(false);
  set_flag_carry(false);
  set_flag_half_carry(false);
}

void CPU::cp_a(u8 reg, u8 val) {
  u8 result = static_cast<u8>(reg - val);

  set_flag_zero(result == 0);
  set_flag_subtract(true);
  set_flag_half_carry((reg & 0xf) - (val & 0xf) < 0);
  set_flag_carry(reg < val);
}

void CPU::rotate_left(u8 &reg) {
  u8 carry = static_cast<u8>(bool(reg & 0b10000000));
  reg = (reg << 1) | carry;

  set_flag_half_carry(false);
  set_flag_carry(carry);
  set_flag_subtract(false);
  set_flag_zero(false);
}

void CPU::rotate_right(u8 &reg) {
  u8 carry = static_cast<u8>(bool(reg & 0b1));
  reg = (reg >> 1) | (carry << 7);

  set_flag_half_carry(false);
  set_flag_carry(carry);
  set_flag_subtract(false);
  set_flag_zero(false);
}

void CPU::rotate_carry_left(u8 &reg) {
  u8 carry = static_cast<u8>(bool(reg & 0b10000000));
  reg = (reg << 1) | get_flag_carry();

  set_flag_half_carry(false);
  set_flag_carry(carry);
  set_flag_subtract(false);
  set_flag_zero(false);
}

void CPU::rotate_carry_right(u8 &reg) {
  u8 carry = static_cast<u8>(bool(reg & 0b1));
  reg = (reg >> 1) | (get_flag_carry() << 7);

  set_flag_half_carry(false);
  set_flag_carry(carry);
  set_flag_subtract(false);
  set_flag_zero(false);
}

void CPU::add_and_jump() {
  u8 r8 = get_byte_from_pc();
  pc = pc + r8;
}

void CPU::carry_condition_and_jump(bool set) {
  bool flag = get_flag_carry();
  if (flag == set) {
    add_and_jump();
  }
  else
    get_byte_from_pc();
}

void CPU::zero_condition_and_jump(bool set) {
  bool flag = get_flag_zero();
  if (flag == set) {
    add_and_jump();
  }
  else
    get_byte_from_pc();
}
