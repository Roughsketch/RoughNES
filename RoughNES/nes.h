#pragma once

#include "cartridge.h"
#include "cpu.h"
#include "ppu.h"

#include <memory>

class NES : std::enable_shared_from_this<NES>
{
  std::shared_ptr<NES> m_self;
  std::shared_ptr<Cartridge> m_cart;
  std::shared_ptr<CPU> m_cpu;
  std::shared_ptr<PPU> m_ppu;

  std::shared_ptr<NES> self()
  {
    return shared_from_this();
  }
public:
  NES();
  explicit NES(std::string filename);

  inline std::shared_ptr<CPU> cpu() const;
  inline std::shared_ptr<PPU> ppu() const;

  int step() const;
};