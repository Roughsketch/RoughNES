#pragma once

#include <vector>

class Cartridge
{
  std::vector<uint8_t> m_prgrom;
  std::vector<uint8_t> m_chrrom;
  std::vector<uint8_t> m_sram;
  uint8_t m_mapper;
  uint8_t m_battery;
  uint8_t m_mirror;

public:
  Cartridge();
  explicit Cartridge(std::string filename);
};