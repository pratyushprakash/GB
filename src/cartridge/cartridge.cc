#include "cartridge.h"

CartridgeType get_cartridge_type(u8 code) {
  switch (code) {
  case 0x00:
  case 0x08:
  case 0x09:
    return CartridgeType::ROMOnly;

  case 0x01:
  case 0x02:
  case 0x03:
    return CartridgeType::MBC1;

  case 0x05:
  case 0x06:
    return CartridgeType::MBC2;

  case 0x0F:
  case 0x10:
  case 0x11:
  case 0x12:
  case 0x13:
    return CartridgeType::MBC3;

  case 0x19:
  case 0x1A:
  case 0x1B:
  case 0x1C:
  case 0x1D:
  case 0x1E:
    return CartridgeType::MBC5;

  default:
    return CartridgeType::Unknown;
  }
}

ROMSize get_rom_size(u8 code) {
  switch (code) {
  case 0x00:
    return ROMSize::KB32;
  case 0x01:
    return ROMSize::KB64;
  case 0x02:
    return ROMSize::KB128;
  case 0x03:
    return ROMSize::KB256;
  case 0x04:
    return ROMSize::KB512;
  case 0x05:
    return ROMSize::MB1;
  case 0x06:
    return ROMSize::MB2;
  case 0x52:
    return ROMSize::MB1_1;
  case 0x53:
    return ROMSize::MB1_2;
  case 0x54:
    return ROMSize::MB1_5;
  default:
    return ROMSize::KB32;
  }
}

std::string get_title(std::vector<u8> rom) {
  char name[header::title_end - header::title_start + 2];
  for (u8 i = 0; i + header::title_start <= header::title_end; i++) {
    name[i] = (char)rom[header::title_start + i];
  }

  return std::string(name);
}

RAMSize get_ram_size(u8 code) {
  switch (code) {

  case 0x00:
    return RAMSize::KB2;

  case 0x01:
    return RAMSize::KB8;

  case 0x02:
    return RAMSize::KB32;

  case 0x03:
    return RAMSize::KB128;

  default:
    return RAMSize::None;
  }
}

DestinationCode get_destination_code(u8 code) {
  switch (code) {
  case 0x00:
    return DestinationCode::Japanese;
  case 0x01:
    return DestinationCode::NonJapanese;
  default:
    return DestinationCode::NonJapanese;
  }
}

CartridgeInfo *get_cartridge_info(std::vector<u8> rom_data) {
  CartridgeInfo *cartridge_info = new CartridgeInfo();

  u8 rom_size_code = rom_data[header::rom_size];
  u8 cartridge_type_code = rom_data[header::cartridge_type];
  u8 ram_size_code = rom_data[header::ram_size];
  u8 destination_code = rom_data[header::destination_code];

  cartridge_info->title = get_title(rom_data);
  cartridge_info->ram_size = get_ram_size(ram_size_code);
  cartridge_info->rom_size = get_rom_size(rom_size_code);
  cartridge_info->destination = get_destination_code(destination_code);
  cartridge_info->type = get_cartridge_type(cartridge_type_code);
  cartridge_info->supports_cgb = rom_data[header::gbc_flag] == 0x80;
  cartridge_info->supports_sgb = rom_data[header::sgb_flag] == 0x03;

  return cartridge_info;
}

uint get_actual_ram_size(RAMSize ram_size) {
  switch (ram_size) {
  case RAMSize::KB2:
    return 2048;
  case RAMSize::KB8:
    return 8192;
  case RAMSize::KB32:
    return 32768;
  case RAMSize::KB128:
    return 131072;
  default:
    return 0;
  }
}

Cartridge::Cartridge(std::vector<u8> rom_data)
    : rom(std::move(rom_data)), cartridge_info(get_cartridge_info(rom_data)) {}

u8 Cartridge::read(u16 loc) const { return rom.at(loc) ;}
void Cartridge::write(u16 loc, u8 val) {}

RomOnly::RomOnly(std::vector<u8> rom_data) : Cartridge(rom_data) {
  ram = std::vector<u8>();
  ram.reserve(get_actual_ram_size(cartridge_info->ram_size));
}

u8 RomOnly::read(u16 loc) const { return rom.at(loc); }

void RomOnly::write(u16 loc, u8 val) {}

MBC1::MBC1(std::vector<u8> rom_data) : Cartridge(rom_data) {
  ram = std::vector<u8>(get_actual_ram_size(cartridge_info->ram_size) + 1, 0);
}

void MBC1::write(u16 loc, u8 val) {
  if (loc >= 0x0 && loc <= 0x1FFF) {
    u8 test_val = val & 0xF;
    if (test_val == 0xA)
      ram_banking_enabled = true;
    else
      ram_banking_enabled = false;
  } else if (loc >= 0x2000 && loc <= 0x3FFF) {
    u8 lower5 = val & 0b11111;
    rom_bank_no = rom_bank_no & 0b11100000;
    rom_bank_no = rom_bank_no | lower5;
    if (rom_bank_no == 0)
      rom_bank_no++;
  } else if (loc >= 0x4000 && loc <= 0x5FFF) {
    if (mode == Mode::ROMBanking) {
      u8 upper2 = val & 0b11100000;
      rom_bank_no = rom_bank_no & 0b11111;
      rom_bank_no = rom_bank_no | upper2;
      if (rom_bank_no == 0)
        rom_bank_no++;
    } else if (mode == Mode::RAMBanking) {
      ram_bank_no = val & 0b11;
    }
  } else if (loc >= 0x6000 && loc <= 0x7FFF) {
    val = val & 0b1;
    mode = val == 0 ? Mode::ROMBanking : Mode::RAMBanking;
    if (mode == Mode::ROMBanking)
      ram_bank_no = 0;
  } else if (loc >= 0xA000 && loc < 0xC000) {
    if (!ram_banking_enabled)
      return;
    u16 ram_offset = 0x2000 * ram_bank_no;
    u16 actual_ram_loc = (loc - 0xA000) + ram_offset;
    ram.at(actual_ram_loc) = val;
  }
}

u8 MBC1::read(u16 loc) const {
  if (loc >= 0x0000 && loc < 0x4000)
    return rom.at(loc);
  else if (loc >= 0x4000 && loc < 0x8000) {
    u16 rom_offset = 0x4000 * rom_bank_no;
    u16 actual_rom_loc = (loc - 0x4000) + rom_offset;
    return rom.at(actual_rom_loc);
  } else if (loc >= 0xA000 && loc < 0xC000) {
    u16 ram_offset = 0x2000 * ram_bank_no;
    u16 actual_ram_loc = (loc - 0xA000) + ram_offset;
    return ram.at(actual_ram_loc);
  }

  return -1;
}
