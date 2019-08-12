#include "cpu.hpp"

void CPU::opcode_00() { nop(); }
void CPU::opcode_01() { ld(bc, get_word_from_pc()); }
void CPU::opcode_02() { ld_to_addr(bc.get(), a); }
void CPU::opcode_03() { inc(bc); }
void CPU::opcode_04() { inc(b); }
void CPU::opcode_05() { dec(b); }
void CPU::opcode_06() { ld(b, get_byte_from_pc()); }
void CPU::opcode_07() { rotate_left(a); }
void CPU::opcode_08() {
  u16 address = get_word_from_pc();
  ld_to_addr(address, static_cast<u8>(sp & 0xFF));
  ld_to_addr(address + 1, static_cast<u8>(sp >> 8));
}
void CPU::opcode_09() { add_hl(bc); }
void CPU::opcode_0A() { ld(a, mmu.read(bc.get())); }
void CPU::opcode_0B() { dec(bc); }
void CPU::opcode_0C() { inc(c); }
void CPU::opcode_0D() { dec(c); }
void CPU::opcode_0E() { ld(c, get_byte_from_pc()); }
void CPU::opcode_0F() { rotate_right(a); }

void CPU::opcode_10() {}
void CPU::opcode_11() { ld(de, get_word_from_pc()); }
void CPU::opcode_12() { ld_to_addr(de.get(), a); }
void CPU::opcode_13() { inc(de); }
void CPU::opcode_14() { inc(d); }
void CPU::opcode_15() { dec(d); }
void CPU::opcode_16() { ld(d, get_byte_from_pc()); }
void CPU::opcode_17() { rotate_carry_left(a); }
void CPU::opcode_18() { add_and_jump(); }
void CPU::opcode_19() { add_hl(de); }
void CPU::opcode_1A() { ld(a, mmu.read(de.get())); }
void CPU::opcode_1B() { dec(de); }
void CPU::opcode_1C() { inc(e); }
void CPU::opcode_1D() { dec(e); }
void CPU::opcode_1E() { ld(e, get_byte_from_pc()); }
void CPU::opcode_1F() { rotate_carry_right(a); }

void CPU::opcode_20() { zero_condition_and_jump(false); }
void CPU::opcode_21() { ld(hl, get_word_from_pc()); }
void CPU::opcode_22() {
  ld_to_addr(hl.get(), a);
  hl.set(hl.get() + 1);
}
void CPU::opcode_23() { inc(hl); }
void CPU::opcode_24() { inc(h); }
void CPU::opcode_25() { dec(h); }
void CPU::opcode_26() { ld(h, get_byte_from_pc()); }
void CPU::opcode_27() { }
void CPU::opcode_28() { zero_condition_and_jump(true); }
void CPU::opcode_29() { add_hl(hl); }
void CPU::opcode_2A() {
  ld(a, mmu.read(hl.get()));
  hl.set(hl.get() + 1);
}
void CPU::opcode_2B() { dec(hl); }
void CPU::opcode_2C() { inc(l); }
void CPU::opcode_2D() { dec(l); }
void CPU::opcode_2E() { ld(l, get_byte_from_pc()); }
void CPU::opcode_2F() {}

void CPU::opcode_30() {}
void CPU::opcode_31() { ld(sp, get_word_from_pc()); }
void CPU::opcode_32() {
  ld_to_addr(hl.get(), a);
  hl.set(hl.get() - 1);
}
void CPU::opcode_33() { inc(sp); }
void CPU::opcode_34() { inc_addr(hl.get()); }
void CPU::opcode_35() { dec_addr(hl.get()); }
void CPU::opcode_36() { ld_to_addr(hl.get(), get_byte_from_pc()); }
void CPU::opcode_37() { }
void CPU::opcode_38() {}
void CPU::opcode_39() { add_hl(sp); }
void CPU::opcode_3A() {
  ld(a, mmu.read(hl.get()));
  hl.set(hl.get() - 1);
}
void CPU::opcode_3B() { dec(sp); }
void CPU::opcode_3C() { inc(a); }
void CPU::opcode_3D() { dec(a); }
void CPU::opcode_3E() { ld(a, get_byte_from_pc()); }
void CPU::opcode_3F() {}

void CPU::opcode_40() { ld(b, b); }
void CPU::opcode_41() { ld(b, c); }
void CPU::opcode_42() { ld(b, d); }
void CPU::opcode_43() { ld(b, e); }
void CPU::opcode_44() { ld(b, h); }
void CPU::opcode_45() { ld(b, l); }
void CPU::opcode_46() { ld(b, mmu.read(hl.get())); }
void CPU::opcode_47() { ld(b, a); }
void CPU::opcode_48() { ld(c, b); }
void CPU::opcode_49() { ld(c, c); }
void CPU::opcode_4A() { ld(c, d); }
void CPU::opcode_4B() { ld(c, e); }
void CPU::opcode_4C() { ld(c, h); }
void CPU::opcode_4D() { ld(c, l); }
void CPU::opcode_4E() { ld(c, mmu.read(hl.get())); }
void CPU::opcode_4F() { ld(c, a); }

void CPU::opcode_50() { ld(d, b); }
void CPU::opcode_51() { ld(d, c); }
void CPU::opcode_52() { ld(d, d); }
void CPU::opcode_53() { ld(d, e); }
void CPU::opcode_54() { ld(d, h); }
void CPU::opcode_55() { ld(d, l); }
void CPU::opcode_56() { ld(d, mmu.read(hl.get())); }
void CPU::opcode_57() { ld(d, a); }
void CPU::opcode_58() { ld(e, b); }
void CPU::opcode_59() { ld(e, c); }
void CPU::opcode_5A() { ld(e, d); }
void CPU::opcode_5B() { ld(e, e); }
void CPU::opcode_5C() { ld(e, h); }
void CPU::opcode_5D() { ld(e, l); }
void CPU::opcode_5E() { ld(e, mmu.read(hl.get())); }
void CPU::opcode_5F() { ld(e, a); }

void CPU::opcode_60() { ld(h, b); }
void CPU::opcode_61() { ld(h, c); }
void CPU::opcode_62() { ld(h, d); }
void CPU::opcode_63() { ld(h, e); }
void CPU::opcode_64() { ld(h, h); }
void CPU::opcode_65() { ld(h, l); }
void CPU::opcode_66() { ld(h, mmu.read(hl.get())); }
void CPU::opcode_67() { ld(h, a); }
void CPU::opcode_68() { ld(l, b); }
void CPU::opcode_69() { ld(l, c); }
void CPU::opcode_6A() { ld(l, d); }
void CPU::opcode_6B() { ld(l, e); }
void CPU::opcode_6C() { ld(l, h); }
void CPU::opcode_6D() { ld(l, l); }
void CPU::opcode_6E() { ld(l, mmu.read(hl.get())); }
void CPU::opcode_6F() { ld(l, a); }

void CPU::opcode_70() { ld_to_addr(hl.get(), b); }
void CPU::opcode_71() { ld_to_addr(hl.get(), c); }
void CPU::opcode_72() { ld_to_addr(hl.get(), d); }
void CPU::opcode_73() { ld_to_addr(hl.get(), e); }
void CPU::opcode_74() { ld_to_addr(hl.get(), h); }
void CPU::opcode_75() { ld_to_addr(hl.get(), l); }
void CPU::opcode_76() { halt(); }
void CPU::opcode_77() { ld_to_addr(hl.get(), a); }
void CPU::opcode_78() { ld(a, b); }
void CPU::opcode_79() { ld(a, c); }
void CPU::opcode_7A() { ld(a, d); }
void CPU::opcode_7B() { ld(a, e); }
void CPU::opcode_7C() { ld(a, h); }
void CPU::opcode_7D() { ld(a, l); }
void CPU::opcode_7E() { ld(a, mmu.read(hl.get())); }
void CPU::opcode_7F() { ld(a, a); }

void CPU::opcode_80() { add_a(a, b); }
void CPU::opcode_81() { add_a(a, c); }
void CPU::opcode_82() { add_a(a, d); }
void CPU::opcode_83() { add_a(a, e); }
void CPU::opcode_84() { add_a(a, h); }
void CPU::opcode_85() { add_a(a, l); }
void CPU::opcode_86() { add_a(a, mmu.read(hl.get())); }
void CPU::opcode_87() { add_a(a, a); }
void CPU::opcode_88() { adc(b); }
void CPU::opcode_89() { adc(c); }
void CPU::opcode_8A() { adc(d); }
void CPU::opcode_8B() { adc(e); }
void CPU::opcode_8C() { adc(h); }
void CPU::opcode_8D() { adc(l); }
void CPU::opcode_8E() { adc(mmu.read(hl.get())); }
void CPU::opcode_8F() { adc(a); }

void CPU::opcode_90() { sub_a(a, b); }
void CPU::opcode_91() { sub_a(a, c); }
void CPU::opcode_92() { sub_a(a, d); }
void CPU::opcode_93() { sub_a(a, e); }
void CPU::opcode_94() { sub_a(a, h); }
void CPU::opcode_95() { sub_a(a, l); }
void CPU::opcode_96() { sub_a(a, mmu.read(hl.get())); }
void CPU::opcode_97() { sub_a(a, a); }
void CPU::opcode_98() { sbc(a, b); }
void CPU::opcode_99() { sbc(a, c); }
void CPU::opcode_9A() { sbc(a, d); }
void CPU::opcode_9B() { sbc(a, e); }
void CPU::opcode_9C() { sbc(a, h); }
void CPU::opcode_9D() { sbc(a, l); }
void CPU::opcode_9E() { sbc(a, mmu.read(hl.get())); }
void CPU::opcode_9F() { sbc(a, a); }

void CPU::opcode_A0() { and_a(a, b); }
void CPU::opcode_A1() { and_a(a, c); }
void CPU::opcode_A2() { and_a(a, d); }
void CPU::opcode_A3() { and_a(a, e); }
void CPU::opcode_A4() { and_a(a, h); }
void CPU::opcode_A5() { and_a(a, l); }
void CPU::opcode_A6() { and_a(a, mmu.read(hl.get())); }
void CPU::opcode_A7() { and_a(a, a); }
void CPU::opcode_A8() { xor_a(a, b); }
void CPU::opcode_A9() { xor_a(a, c); }
void CPU::opcode_AA() { xor_a(a, d); }
void CPU::opcode_AB() { xor_a(a, e); }
void CPU::opcode_AC() { xor_a(a, h); }
void CPU::opcode_AD() { xor_a(a, l); }
void CPU::opcode_AE() { xor_a(a, mmu.read(hl.get())); }
void CPU::opcode_AF() { xor_a(a, a); }


void CPU::opcode_B0() { or_a(a, b); }
void CPU::opcode_B1() { or_a(a, c); }
void CPU::opcode_B2() { or_a(a, d); }
void CPU::opcode_B3() { or_a(a, e); }
void CPU::opcode_B4() { or_a(a, h); }
void CPU::opcode_B5() { or_a(a, l); }
void CPU::opcode_B6() { or_a(a, mmu.read(hl.get())); }
void CPU::opcode_B7() { or_a(a, a); }
void CPU::opcode_B8() { cp_a(a, b); }
void CPU::opcode_B9() { cp_a(a, c); }
void CPU::opcode_BA() { cp_a(a, d); }
void CPU::opcode_BB() { cp_a(a, e); }
void CPU::opcode_BC() { cp_a(a, h); }
void CPU::opcode_BD() { cp_a(a, l); }
void CPU::opcode_BE() { cp_a(a, mmu.read(hl.get())); }
void CPU::opcode_BF() { cp_a(a, a); }

void CPU::opcode_C0() {}
void CPU::opcode_C1() { bc.set(stack_pop()); }
void CPU::opcode_C2() {}
void CPU::opcode_C3() {}
void CPU::opcode_C4() {}
void CPU::opcode_C5() { stack_push(bc.get()); }
void CPU::opcode_C6() { add_a(a, get_byte_from_pc()); }
void CPU::opcode_C7() {}
void CPU::opcode_C8() {}
void CPU::opcode_C9() {}
void CPU::opcode_CA() {}
void CPU::opcode_CB() {}
void CPU::opcode_CC() {}
void CPU::opcode_CD() {}
void CPU::opcode_CE() { adc(get_byte_from_pc()); }
void CPU::opcode_CF() {}

void CPU::opcode_D0() {}
void CPU::opcode_D1() { de.set(stack_pop()); }
void CPU::opcode_D2() {}
void CPU::opcode_D3() {}
void CPU::opcode_D4() {}
void CPU::opcode_D5() { stack_push(de.get()); }
void CPU::opcode_D6() { sub_a(a, get_byte_from_pc()); }
void CPU::opcode_D7() {}
void CPU::opcode_D8() {}
void CPU::opcode_D9() {}
void CPU::opcode_DA() {}
void CPU::opcode_DB() {}
void CPU::opcode_DC() {}
void CPU::opcode_DD() {}
void CPU::opcode_DE() { sbc(a, get_byte_from_pc()); }
void CPU::opcode_DF() {}

void CPU::opcode_E0() { ld_to_addr(0xFF00 + get_byte_from_pc(), a); }
void CPU::opcode_E1() { hl.set(stack_pop()); }
void CPU::opcode_E2() { ld_to_addr(0xFF00 + c, a); }
void CPU::opcode_E3() {}
void CPU::opcode_E4() {}
void CPU::opcode_E5() { stack_push(hl.get()); }
void CPU::opcode_E6() { and_a(a, get_byte_from_pc()); }
void CPU::opcode_E7() {}
void CPU::opcode_E8() {}
void CPU::opcode_E9() {}
void CPU::opcode_EA() { ld_to_addr(get_word_from_pc(), a); }
void CPU::opcode_EB() {}
void CPU::opcode_EC() {}
void CPU::opcode_ED() {}
void CPU::opcode_EE() { xor_a(a, get_byte_from_pc()); }
void CPU::opcode_EF() {}

void CPU::opcode_F0() { ld(a, mmu.read(0xFF00 + get_byte_from_pc())); }
void CPU::opcode_F1() { af.set(stack_pop()); }
void CPU::opcode_F2() { ld(a, mmu.read(0xFF00 + c)); }
void CPU::opcode_F3() {}
void CPU::opcode_F4() {}
void CPU::opcode_F5() { stack_push(af.get()); }
void CPU::opcode_F6() { or_a(a, get_byte_from_pc()); }
void CPU::opcode_F7() {}
void CPU::opcode_F8() {}
void CPU::opcode_F9() { ld(sp, hl.get()); }
void CPU::opcode_FA() { ld(a, mmu.read(get_word_from_pc())); }
void CPU::opcode_FB() {}
void CPU::opcode_FC() {}
void CPU::opcode_FD() {}
void CPU::opcode_FE() { cp_a(a, get_byte_from_pc()); }
void CPU::opcode_FF() {}
