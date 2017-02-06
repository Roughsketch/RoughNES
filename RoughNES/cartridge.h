#pragma once

#include <vector>

#include "nes_header.h"

class Cartridge
{
  static const size_t PRGSize = 0x4000;
  static const size_t CHRSize = 0x2000;

  std::vector<uint8_t> m_prgrom;
  std::vector<uint8_t> m_chrrom;
  std::vector<uint8_t> m_sram;

  NESHeader m_header;
public:
  explicit Cartridge(std::string filename);

  inline std::vector<uint8_t> prg_rom() const { return m_prgrom; }
};