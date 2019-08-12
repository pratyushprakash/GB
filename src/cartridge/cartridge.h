#pragma once

#include "../definitions.hpp"
#include <string>
#include <vector>

namespace header {
const int entry_point = 0x100;
const int logo = 0x104;
const int title_start = 0x134;
const int title_end = 0x142;
const int gbc_flag = 0x143;
const int new_licensee_code_high_nibble = 0x144;
const int new_licensee_code_low_nibble = 0x145;
const int sgb_flag = 0x146;
const int cartridge_type = 0x147;
const int rom_size = 0x148;
const int ram_size = 0x149;
const int destination_code = 0x14A;
const int licensee_code = 0x14B;
const int rom_version_no = 0x14C;
const int complement_check = 0x14D;
const int checksum = 0x14E;
} // namespace header

enum class CartridgeType {
  ROMOnly,
  MBC1,
  MBC2,
  MBC3,
  MBC5,
  HuC1,
  Rumble,
  Unknown
};

enum class ROMSize {
  KB32,
  KB64,
  KB128,
  KB256,
  KB512,
  MB1,
  MB2,
  MB1_1,
  MB1_2,
  MB1_5
};

enum class Mode {
  RAMBanking,
  ROMBanking
};

std::string get_title(std::vector<u8> rom);

ROMSize get_rom_size(u8 code);
CartridgeType get_cartridge_type(u8 code);

enum class RAMSize { None, KB2, KB8, KB32, KB128 };

RAMSize get_ram_size(u8 code);
uint get_actual_ram_size(RAMSize ram_size) ;

enum class DestinationCode { Japanese, NonJapanese };

DestinationCode get_destination_code(u8 code);

class CartridgeInfo {
public:
  std::string title;

  CartridgeType type;
  RAMSize ram_size;
  ROMSize rom_size;
  DestinationCode destination;

  bool supports_cgb;
  bool supports_sgb;
};

CartridgeInfo *get_cartridge_info(std::vector<u8> rom_data);

class Cartridge {
public:
  Cartridge(std::vector<u8> rom_data);
  virtual u8 read(u16 loc) const;
  virtual void write(u16 loc, u8 val);

protected:
  CartridgeInfo *cartridge_info;
  std::vector<u8> rom;
  std::vector<u8> ram;
};

class RomOnly : Cartridge {
public:
  RomOnly(std::vector<u8> rom_data);
  u8 read(u16 loc) const override;
  void write(u16 loc, u8 val) override;
};

class MBC1 : Cartridge {
private:
  std::vector<u8> rom_bank;
  std::vector<u8> ram_bank;
  bool ram_banking_enabled = false;
  u8 ram_bank_no = 0;
  u8 rom_bank_no = 1;
  Mode mode = Mode::ROMBanking;

public:
  MBC1(std::vector<u8> rom_data);
  u8 read(u16 loc) const override;
  void write(u16 loc, u8 val) override;
};

class MBC3 : Cartridge {
private:
  std::vector<u8> rom_bank;
  std::vector<u8> ram_bank;
  bool ram_banking_enabled = false;
  bool ram_over_rtc = true;


public:
  MBC3(std::vector<u8> rom_data);
  u8 read(u16 loc) const override;
  void write(u16 loc, u8 val) override;
};
