#pragma once

#include "cartridge.h"
#include "cpu.h"
#include "ppu.h"

#include <memory>

class NES
{
  std::unique_ptr<Cartridge> m_cart;
  std::unique_ptr<CPU> m_cpu;
  std::unique_ptr<PPU> m_ppu;
public:
  NES();
  explicit NES(std::string filename);

  int step() const;
};