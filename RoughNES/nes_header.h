#pragma once

#include <vector>

class NESHeader
{
  bool m_is_nes2;
  uint16_t m_prg_pages;
  uint16_t m_chr_pages;
  uint16_t m_mapper_index;
  bool m_fourscreen;
  bool m_trainer;
  bool m_sram;
  bool m_mirror;
  bool m_playchoice;
  bool m_vs_unisystem;

  uint8_t m_submapper;
public:
  static const size_t Size = 0x10;

  NESHeader(){};
  explicit NESHeader(std::vector<uint8_t>& header);

  inline uint16_t prg_pages() const { return m_prg_pages; }
  inline uint16_t chr_pages() const { return m_chr_pages; }
};
