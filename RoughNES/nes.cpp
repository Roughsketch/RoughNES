#include "nes.h"

NES::NES()
{
  m_cart = nullptr;
  m_cpu = std::make_unique<CPU>();
  m_ppu = std::make_unique<PPU>();
}

NES::NES(std::string filename) : NES()
{
  m_cart = std::make_unique<Cartridge>(filename);
}

int NES::step() const
{
  auto cpu_cycles = m_cpu->step();
  auto ppu_cycles = cpu_cycles * 3;

  for (auto i = 0; i < ppu_cycles; ++i)
  {
    m_ppu->step();
  }

  return cpu_cycles;
}
