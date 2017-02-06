#include "cartridge.h"

#include <fstream>
#include <iterator>

Cartridge::Cartridge(std::string filename)
{
  std::ifstream ifs(filename, std::ios::binary);

  if (!ifs.is_open())
  {
    throw std::invalid_argument("Could not open file");
  }
  
  ifs.unsetf(std::ios::skipws);

  ifs.seekg(0, std::ios::end);
  auto filesize = static_cast<size_t>(ifs.tellg());
  ifs.seekg(0, std::ios::beg);

  std::vector<uint8_t> rom(filesize);

  rom.insert(std::begin(rom),
    std::istream_iterator<uint8_t>(ifs),
    std::istream_iterator<uint8_t>());

  m_header = NESHeader(rom);

  auto prg_size = m_header.prg_pages() * PRGSize;
  auto chr_size = m_header.chr_pages() * CHRSize;

  m_prgrom.resize(prg_size);
  m_chrrom.resize(chr_size);

  std::copy(std::begin(rom) + 0x10, std::begin(rom) + 0x10 + prg_size, std::begin(m_prgrom));
  std::copy(std::begin(rom) + 0x10 + prg_size, std::begin(rom) + 0x10 + prg_size + chr_size, std::begin(m_chrrom));
}

