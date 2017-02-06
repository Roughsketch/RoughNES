#pragma once

#include <vector>

class PPU
{
  std::vector<uint8_t> m_palette;
  std::vector<uint8_t> m_nametable;
  std::vector<uint8_t> m_oam_data;

  struct Registers
  {
    uint16_t v;
    uint16_t t;
    uint8_t x;
    uint8_t w;
    uint8_t f;
  } m_regs;
public:
  PPU();
  void step();
};

