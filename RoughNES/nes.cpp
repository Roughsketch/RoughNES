#include "nes.h"

NES::NES()
{
  m_cart = nullptr;
  m_cpu = std::make_shared<CPU>(self());
  m_ppu = std::make_shared<PPU>(self());
}

NES::NES(std::string filename) : NES()
{
  m_cart = std::make_shared<Cartridge>(filename);
}

std::shared_ptr<CPU> NES::cpu() const
{
  return m_cpu;
}

std::shared_ptr<PPU> NES::ppu() const
{
  return m_ppu;
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
