#include "cartridge.h"

#include <fstream>

Cartridge::Cartridge() : m_mapper(0), m_battery(0), m_mirror(0)
{
  
}

Cartridge::Cartridge(std::string filename)
{
  std::ifstream ifs(filename, std::ios::binary);


}

