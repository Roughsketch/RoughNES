#include "nes_header.h"

NESHeader::NESHeader(std::vector<uint8_t>& header)
{
  if (header[0] != 'N' ||
      header[1] != 'E' ||
      header[2] != 'S' ||
      header[3] != 0x1A)
  {
    throw std::invalid_argument("Not a valid NES ROM: Header is invalid.");
  }

  m_prg_pages = header[4];
  m_chr_pages = header[5];

  m_mapper_index = ((header[6] & 0xF0) >> 4) | (header[7] & 0xF0);

  m_fourscreen = (header[6] & 0x08) > 0;
  m_trainer = (header[6] & 0x04) > 0;
  m_sram = (header[6] & 0x02) > 0;
  m_mirror = (header[6] & 0x01) > 0;

  m_playchoice = (header[7] & 0x02) > 0;
  m_vs_unisystem = (header[7] & 0x01) > 0;

  m_submapper = 0;

  m_is_nes2 = ((header[7] & 0x0C) >> 2) == 2;

  if (m_is_nes2)
  {
    m_prg_pages |= ((header[9] & 0x0F) << 8);
    m_chr_pages |= ((header[9] >> 4) << 8);
    m_mapper_index |= ((header[8] & 0x0F) << 8);
    m_submapper = header[8] >> 4;
  }
}
