#pragma once

#include <memory>
#include <vector>

#include "nes.h"

class NES;

class PPU
{
  std::shared_ptr<NES> m_console;

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
  explicit PPU(std::shared_ptr<NES> console);

  void step();
};

