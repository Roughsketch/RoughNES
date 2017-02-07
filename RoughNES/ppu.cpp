#include "ppu.h"

PPU::PPU()
{

}

PPU::PPU(std::shared_ptr<NES> console) : PPU()
{
  m_console = console;
}

void PPU::step()
{
}
