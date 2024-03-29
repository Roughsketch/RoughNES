#pragma once

#include <cstdint>
#include <vector>
#include <ostream>
#include <string>

namespace Instruction
{
  enum AddressMode
  {
    Absolute,
    AbsoluteX,
    AbsoluteY,
    Accumulator,
    Immediate,
    Implied,
    Indirect,
    IndirectX,  //  Indexed Indirect
    IndirectY,  //  Indirect Indexed
    Relative,
    ZeroPage,
    ZeroPageX,
    ZeroPageY
  };

  struct Info
  {
    uint8_t opcode;       //  Instruction opcode
    std::string name;     //  Instruction name
    uint8_t size;         //  Instruction size in bytes
    uint8_t cycles;       //  Instruction cycles used by instruction
    uint8_t page_cycles;  //  How many cycles are added if a page boundary is crossed
    AddressMode mode;     //  Addressing mode used by instruction

    friend std::ostream& operator<<(std::ostream& os, const Info& obj)
    {
      return os
        << "opcode: " << obj.opcode
        << " name: " << obj.name
        << " size: " << obj.size
        << " cycles: " << obj.cycles
        << " page_cycles: " << obj.page_cycles
        << " mode: " << obj.mode;
    }
  };

  static const std::vector<Info> Table = {
    { 0x00, "BRK", 1, 7, 0, Implied },
    { 0x01, "ORA", 2, 6, 0, IndirectX },
    { 0x02, "KIL", 0, 2, 0, Implied },
    { 0x03, "SLO", 0, 8, 0, IndirectX },
    { 0x04, "NOP", 2, 3, 0, ZeroPage },
    { 0x05, "ORA", 2, 3, 0, ZeroPage },
    { 0x06, "ASL", 2, 5, 0, ZeroPage },
    { 0x07, "SLO", 0, 5, 0, ZeroPage },
    { 0x08, "PHP", 1, 3, 0, Implied },
    { 0x09, "ORA", 2, 2, 0, Immediate },
    { 0x0A, "ASL", 1, 2, 0, Accumulator },
    { 0x0B, "ANC", 0, 2, 0, Immediate },
    { 0x0C, "NOP", 3, 4, 0, Absolute },
    { 0x0D, "ORA", 3, 4, 0, Absolute },
    { 0x0E, "ASL", 3, 6, 0, Absolute },
    { 0x0F, "SLO", 0, 6, 0, Absolute },
    { 0x10, "BPL", 2, 2, 1, Relative },
    { 0x11, "ORA", 2, 5, 1, IndirectY },
    { 0x12, "KIL", 0, 2, 0, Implied },
    { 0x13, "SLO", 0, 8, 0, IndirectY },
    { 0x14, "NOP", 2, 4, 0, ZeroPageX },
    { 0x15, "ORA", 2, 4, 0, ZeroPageX },
    { 0x16, "ASL", 2, 6, 0, ZeroPageX },
    { 0x17, "SLO", 0, 6, 0, ZeroPageX },
    { 0x18, "CLC", 1, 2, 0, Implied },
    { 0x19, "ORA", 3, 4, 1, AbsoluteY },
    { 0x1A, "NOP", 1, 2, 0, Implied },
    { 0x1B, "SLO", 0, 7, 0, AbsoluteY },
    { 0x1C, "NOP", 3, 4, 1, AbsoluteX },
    { 0x1D, "ORA", 3, 4, 1, AbsoluteX },
    { 0x1E, "ASL", 3, 7, 0, AbsoluteX },
    { 0x1F, "SLO", 0, 7, 0, AbsoluteX },
    { 0x20, "JSR", 3, 6, 0, Absolute },
    { 0x21, "AND", 2, 6, 0, IndirectX },
    { 0x22, "KIL", 0, 2, 0, Implied },
    { 0x23, "RLA", 0, 8, 0, IndirectX },
    { 0x24, "BIT", 2, 3, 0, ZeroPage },
    { 0x25, "AND", 2, 3, 0, ZeroPage },
    { 0x26, "ROL", 2, 5, 0, ZeroPage },
    { 0x27, "RLA", 0, 5, 0, ZeroPage },
    { 0x28, "PLP", 1, 4, 0, Implied },
    { 0x29, "AND", 2, 2, 0, Immediate },
    { 0x2A, "ROL", 1, 2, 0, Accumulator },
    { 0x2B, "ANC", 0, 2, 0, Immediate },
    { 0x2C, "BIT", 3, 4, 0, Absolute },
    { 0x2D, "AND", 3, 4, 0, Absolute },
    { 0x2E, "ROL", 3, 6, 0, Absolute },
    { 0x2F, "RLA", 0, 6, 0, Absolute },
    { 0x30, "BMI", 2, 2, 1, Relative },
    { 0x31, "AND", 2, 5, 1, IndirectY },
    { 0x32, "KIL", 0, 2, 0, Implied },
    { 0x33, "RLA", 0, 8, 0, IndirectY },
    { 0x34, "NOP", 2, 4, 0, ZeroPageX },
    { 0x35, "AND", 2, 4, 0, ZeroPageX },
    { 0x36, "ROL", 2, 6, 0, ZeroPageX },
    { 0x37, "RLA", 0, 6, 0, ZeroPageX },
    { 0x38, "SEC", 1, 2, 0, Implied },
    { 0x39, "AND", 3, 4, 1, AbsoluteY },
    { 0x3A, "NOP", 1, 2, 0, Implied },
    { 0x3B, "RLA", 0, 7, 0, AbsoluteY },
    { 0x3C, "NOP", 3, 4, 1, AbsoluteX },
    { 0x3D, "AND", 3, 4, 1, AbsoluteX },
    { 0x3E, "ROL", 3, 7, 0, AbsoluteX },
    { 0x3F, "RLA", 0, 7, 0, AbsoluteX },
    { 0x40, "RTI", 1, 6, 0, Implied },
    { 0x41, "EOR", 2, 6, 0, IndirectX },
    { 0x42, "KIL", 0, 2, 0, Implied },
    { 0x43, "SRE", 0, 8, 0, IndirectX },
    { 0x44, "NOP", 2, 3, 0, ZeroPage },
    { 0x45, "EOR", 2, 3, 0, ZeroPage },
    { 0x46, "LSR", 2, 5, 0, ZeroPage },
    { 0x47, "SRE", 0, 5, 0, ZeroPage },
    { 0x48, "PHA", 1, 3, 0, Implied },
    { 0x49, "EOR", 2, 2, 0, Immediate },
    { 0x4A, "LSR", 1, 2, 0, Accumulator },
    { 0x4B, "ALR", 0, 2, 0, Immediate },
    { 0x4C, "JMP", 3, 3, 0, Absolute },
    { 0x4D, "EOR", 3, 4, 0, Absolute },
    { 0x4E, "LSR", 3, 6, 0, Absolute },
    { 0x4F, "SRE", 0, 6, 0, Absolute },
    { 0x50, "BVC", 2, 2, 1, Relative },
    { 0x51, "EOR", 2, 5, 1, IndirectY },
    { 0x52, "KIL", 0, 2, 0, Implied },
    { 0x53, "SRE", 0, 8, 0, IndirectY },
    { 0x54, "NOP", 2, 4, 0, ZeroPageX },
    { 0x55, "EOR", 2, 4, 0, ZeroPageX },
    { 0x56, "LSR", 2, 6, 0, ZeroPageX },
    { 0x57, "SRE", 0, 6, 0, ZeroPageX },
    { 0x58, "CLI", 1, 2, 0, Implied },
    { 0x59, "EOR", 3, 4, 1, AbsoluteY },
    { 0x5A, "NOP", 1, 2, 0, Implied },
    { 0x5B, "SRE", 0, 7, 0, AbsoluteY },
    { 0x5C, "NOP", 3, 4, 1, AbsoluteX },
    { 0x5D, "EOR", 3, 4, 1, AbsoluteX },
    { 0x5E, "LSR", 3, 7, 0, AbsoluteX },
    { 0x5F, "SRE", 0, 7, 0, AbsoluteX },
    { 0x60, "RTS", 1, 6, 0, Implied },
    { 0x61, "ADC", 2, 6, 0, IndirectX },
    { 0x62, "KIL", 0, 2, 0, Implied },
    { 0x63, "RRA", 0, 8, 0, IndirectX },
    { 0x64, "NOP", 2, 3, 0, ZeroPage },
    { 0x65, "ADC", 2, 3, 0, ZeroPage },
    { 0x66, "ROR", 2, 5, 0, ZeroPage },
    { 0x67, "RRA", 0, 5, 0, ZeroPage },
    { 0x68, "PLA", 1, 4, 0, Implied },
    { 0x69, "ADC", 2, 2, 0, Immediate },
    { 0x6A, "ROR", 1, 2, 0, Accumulator },
    { 0x6B, "ARR", 0, 2, 0, Immediate },
    { 0x6C, "JMP", 3, 5, 0, Indirect },
    { 0x6D, "ADC", 3, 4, 0, Absolute },
    { 0x6E, "ROR", 3, 6, 0, Absolute },
    { 0x6F, "RRA", 0, 6, 0, Absolute },
    { 0x70, "BVS", 2, 2, 1, Relative },
    { 0x71, "ADC", 2, 5, 1, IndirectY },
    { 0x72, "KIL", 0, 2, 0, Implied },
    { 0x73, "RRA", 0, 8, 0, IndirectY },
    { 0x74, "NOP", 2, 4, 0, ZeroPageX },
    { 0x75, "ADC", 2, 4, 0, ZeroPageX },
    { 0x76, "ROR", 2, 6, 0, ZeroPageX },
    { 0x77, "RRA", 0, 6, 0, ZeroPageX },
    { 0x78, "SEI", 1, 2, 0, Implied },
    { 0x79, "ADC", 3, 4, 1, AbsoluteY },
    { 0x7A, "NOP", 1, 2, 0, Implied },
    { 0x7B, "RRA", 0, 7, 0, AbsoluteY },
    { 0x7C, "NOP", 3, 4, 1, AbsoluteX },
    { 0x7D, "ADC", 3, 4, 1, AbsoluteX },
    { 0x7E, "ROR", 3, 7, 0, AbsoluteX },
    { 0x7F, "RRA", 0, 7, 0, AbsoluteX },
    { 0x80, "NOP", 2, 2, 0, Immediate },
    { 0x81, "STA", 2, 6, 0, IndirectX },
    { 0x82, "NOP", 0, 2, 0, Immediate },
    { 0x83, "SAX", 0, 6, 0, IndirectX },
    { 0x84, "STY", 2, 3, 0, ZeroPage },
    { 0x85, "STA", 2, 3, 0, ZeroPage },
    { 0x86, "STX", 2, 3, 0, ZeroPage },
    { 0x87, "SAX", 0, 3, 0, ZeroPage },
    { 0x88, "DEY", 1, 2, 0, Implied },
    { 0x89, "NOP", 0, 2, 0, Immediate },
    { 0x8A, "TXA", 1, 2, 0, Implied },
    { 0x8B, "XAA", 0, 2, 0, Immediate },
    { 0x8C, "STY", 3, 4, 0, Absolute },
    { 0x8D, "STA", 3, 4, 0, Absolute },
    { 0x8E, "STX", 3, 4, 0, Absolute },
    { 0x8F, "SAX", 0, 4, 0, Absolute },
    { 0x90, "BCC", 2, 2, 1, Relative },
    { 0x91, "STA", 2, 6, 0, IndirectY },
    { 0x92, "KIL", 0, 2, 0, Implied },
    { 0x93, "AHX", 0, 6, 0, IndirectY },
    { 0x94, "STY", 2, 4, 0, ZeroPageX },
    { 0x95, "STA", 2, 4, 0, ZeroPageX },
    { 0x96, "STX", 2, 4, 0, ZeroPageY },
    { 0x97, "SAX", 0, 4, 0, ZeroPageY },
    { 0x98, "TYA", 1, 2, 0, Implied },
    { 0x99, "STA", 3, 5, 0, AbsoluteY },
    { 0x9A, "TXS", 1, 2, 0, Implied },
    { 0x9B, "TAS", 0, 5, 0, AbsoluteY },
    { 0x9C, "SHY", 0, 5, 0, AbsoluteX },
    { 0x9D, "STA", 3, 5, 0, AbsoluteX },
    { 0x9E, "SHX", 0, 5, 0, AbsoluteY },
    { 0x9F, "AHX", 0, 5, 0, AbsoluteY },
    { 0xA0, "LDY", 2, 2, 0, Immediate },
    { 0xA1, "LDA", 2, 6, 0, IndirectX },
    { 0xA2, "LDX", 2, 2, 0, Immediate },
    { 0xA3, "LAX", 0, 6, 0, IndirectX },
    { 0xA4, "LDY", 2, 3, 0, ZeroPage },
    { 0xA5, "LDA", 2, 3, 0, ZeroPage },
    { 0xA6, "LDX", 2, 3, 0, ZeroPage },
    { 0xA7, "LAX", 0, 3, 0, ZeroPage },
    { 0xA8, "TAY", 1, 2, 0, Implied },
    { 0xA9, "LDA", 2, 2, 0, Immediate },
    { 0xAA, "TAX", 1, 2, 0, Implied },
    { 0xAB, "LAX", 0, 2, 0, Immediate },
    { 0xAC, "LDY", 3, 4, 0, Absolute },
    { 0xAD, "LDA", 3, 4, 0, Absolute },
    { 0xAE, "LDX", 3, 4, 0, Absolute },
    { 0xAF, "LAX", 0, 4, 0, Absolute },
    { 0xB0, "BCS", 2, 2, 1, Relative },
    { 0xB1, "LDA", 2, 5, 1, IndirectY },
    { 0xB2, "KIL", 0, 2, 0, Implied },
    { 0xB3, "LAX", 0, 5, 1, IndirectY },
    { 0xB4, "LDY", 2, 4, 0, ZeroPageX },
    { 0xB5, "LDA", 2, 4, 0, ZeroPageX },
    { 0xB6, "LDX", 2, 4, 0, ZeroPageY },
    { 0xB7, "LAX", 0, 4, 0, ZeroPageY },
    { 0xB8, "CLV", 1, 2, 0, Implied },
    { 0xB9, "LDA", 3, 4, 1, AbsoluteY },
    { 0xBA, "TSX", 1, 2, 0, Implied },
    { 0xBB, "LAS", 0, 4, 1, AbsoluteY },
    { 0xBC, "LDY", 3, 4, 1, AbsoluteX },
    { 0xBD, "LDA", 3, 4, 1, AbsoluteX },
    { 0xBE, "LDX", 3, 4, 1, AbsoluteY },
    { 0xBF, "LAX", 0, 4, 1, AbsoluteY },
    { 0xC0, "CPY", 2, 2, 0, Immediate },
    { 0xC1, "CMP", 2, 6, 0, IndirectX },
    { 0xC2, "NOP", 0, 2, 0, Immediate },
    { 0xC3, "DCP", 0, 8, 0, IndirectX },
    { 0xC4, "CPY", 2, 3, 0, ZeroPage },
    { 0xC5, "CMP", 2, 3, 0, ZeroPage },
    { 0xC6, "DEC", 2, 5, 0, ZeroPage },
    { 0xC7, "DCP", 0, 5, 0, ZeroPage },
    { 0xC8, "INY", 1, 2, 0, Implied },
    { 0xC9, "CMP", 2, 2, 0, Immediate },
    { 0xCA, "DEX", 1, 2, 0, Implied },
    { 0xCB, "AXS", 0, 2, 0, Immediate },
    { 0xCC, "CPY", 3, 4, 0, Absolute },
    { 0xCD, "CMP", 3, 4, 0, Absolute },
    { 0xCE, "DEC", 3, 6, 0, Absolute },
    { 0xCF, "DCP", 0, 6, 0, Absolute },
    { 0xD0, "BNE", 2, 2, 1, Relative },
    { 0xD1, "CMP", 2, 5, 1, IndirectY },
    { 0xD2, "KIL", 0, 2, 0, Implied },
    { 0xD3, "DCP", 0, 8, 0, IndirectY },
    { 0xD4, "NOP", 2, 4, 0, ZeroPageX },
    { 0xD5, "CMP", 2, 4, 0, ZeroPageX },
    { 0xD6, "DEC", 2, 6, 0, ZeroPageX },
    { 0xD7, "DCP", 0, 6, 0, ZeroPageX },
    { 0xD8, "CLD", 1, 2, 0, Implied },
    { 0xD9, "CMP", 3, 4, 1, AbsoluteY },
    { 0xDA, "NOP", 1, 2, 0, Implied },
    { 0xDB, "DCP", 0, 7, 0, AbsoluteY },
    { 0xDC, "NOP", 3, 4, 1, AbsoluteX },
    { 0xDD, "CMP", 3, 4, 1, AbsoluteX },
    { 0xDE, "DEC", 3, 7, 0, AbsoluteX },
    { 0xDF, "DCP", 0, 7, 0, AbsoluteX },
    { 0xE0, "CPX", 2, 2, 0, Immediate },
    { 0xE1, "SBC", 2, 6, 0, IndirectX },
    { 0xE2, "NOP", 0, 2, 0, Immediate },
    { 0xE3, "ISC", 0, 8, 0, IndirectX },
    { 0xE4, "CPX", 2, 3, 0, ZeroPage },
    { 0xE5, "SBC", 2, 3, 0, ZeroPage },
    { 0xE6, "INC", 2, 5, 0, ZeroPage },
    { 0xE7, "ISC", 0, 5, 0, ZeroPage },
    { 0xE8, "INX", 1, 2, 0, Implied },
    { 0xE9, "SBC", 2, 2, 0, Immediate },
    { 0xEA, "NOP", 1, 2, 0, Implied },
    { 0xEB, "SBC", 0, 2, 0, Immediate },
    { 0xEC, "CPX", 3, 4, 0, Absolute },
    { 0xED, "SBC", 3, 4, 0, Absolute },
    { 0xEE, "INC", 3, 6, 0, Absolute },
    { 0xEF, "ISC", 0, 6, 0, Absolute },
    { 0xF0, "BEQ", 2, 2, 1, Relative },
    { 0xF1, "SBC", 2, 5, 1, IndirectY },
    { 0xF2, "KIL", 0, 2, 0, Implied },
    { 0xF3, "ISC", 0, 8, 0, IndirectY },
    { 0xF4, "NOP", 2, 4, 0, ZeroPageX },
    { 0xF5, "SBC", 2, 4, 0, ZeroPageX },
    { 0xF6, "INC", 2, 6, 0, ZeroPageX },
    { 0xF7, "ISC", 0, 6, 0, ZeroPageX },
    { 0xF8, "SED", 1, 2, 0, Implied },
    { 0xF9, "SBC", 3, 4, 1, AbsoluteY },
    { 0xFA, "NOP", 1, 2, 0, Implied },
    { 0xFB, "ISC", 0, 7, 0, AbsoluteY },
    { 0xFC, "NOP", 3, 4, 1, AbsoluteX },
    { 0xFD, "SBC", 3, 4, 1, AbsoluteX },
    { 0xFE, "INC", 3, 7, 0, AbsoluteX },
    { 0xFF, "ISC", 0, 7, 0, AbsoluteX }
  };
}
