#pragma once

#include <cstdint>
#include <vector>

#include "register.h"
#include "opcode.h"

class CPU
{
  std::vector<uint8_t> m_rom;
  std::vector<uint8_t> m_ppumem;
  std::vector<uint8_t> m_sysmem;
  Registers m_reg;
  uint64_t m_cycles;

  struct OpcodeInfo
  {
    uint16_t address;
    uint16_t pc;
    Instruction::AddressMode mode;
  };

  static void(CPU::*FuncTable[])(const OpcodeInfo&);

public:
  static const uint16_t MemorySize = std::numeric_limits<uint16_t>::max();

  CPU();
  explicit CPU(const std::vector<uint8_t>& rom);

  bool load_rom(const std::vector<uint8_t>& rom);
  void step();

  void set_registers(Registers regs);
  void write_byte(uint8_t value, uint16_t pos);
  void write_word(uint16_t value, uint16_t pos);
  bool write_bytes(const std::vector<uint8_t>& data, uint16_t start);

  Registers get_registers() const;
  uint16_t get_address(Instruction::AddressMode mode) const;
  uint8_t read_byte(uint16_t pos) const;
  uint16_t read_word(uint16_t pos) const;
  std::vector<uint8_t> read_bytes(uint16_t start, uint16_t size) const;

  inline void set_reg_a(uint8_t value);
  inline void set_reg_x(uint8_t value);
  inline void set_reg_y(uint8_t value);

#pragma region Set and Clear status flags
  //  Set and Clear status flags
  inline void SEC(const OpcodeInfo& info);
  inline void SED(const OpcodeInfo& info);
  inline void SEI(const OpcodeInfo& info);
  inline void CLC(const OpcodeInfo& info);
  inline void CLD(const OpcodeInfo& info);
  inline void CLI(const OpcodeInfo& info);
  inline void CLV(const OpcodeInfo& info);
#pragma endregion

#pragma region Increment and Decrement
  inline void INC(const OpcodeInfo& info);
  inline void INX(const OpcodeInfo& info);
  inline void INY(const OpcodeInfo& info);
  inline void DEC(const OpcodeInfo& info);
  inline void DEX(const OpcodeInfo& info);
  inline void DEY(const OpcodeInfo& info);
#pragma endregion

#pragma region Logical
  inline void AND(const OpcodeInfo& info);
  inline void EOR(const OpcodeInfo& info);
  inline void ORA(const OpcodeInfo& info);
  inline void BIT(const OpcodeInfo& info);
#pragma endregion

#pragma region Arithmetic
  inline void ADC(const OpcodeInfo& info);
  inline void SBC(const OpcodeInfo& info);
  inline void LSR(const OpcodeInfo& info);
  inline void ASL(const OpcodeInfo& info);
  inline void ROR(const OpcodeInfo& info);
  inline void ROL(const OpcodeInfo& info);
#pragma endregion

#pragma region System
  inline void BRK(const OpcodeInfo& info);
  inline void NOP(const OpcodeInfo& info);
  inline void RTI(const OpcodeInfo& info);
#pragma endregion

#pragma region Register Transfer
  inline void TAX(const OpcodeInfo& info);
  inline void TAY(const OpcodeInfo& info);
  inline void TSX(const OpcodeInfo& info);
  inline void TXS(const OpcodeInfo& info);
  inline void TXA(const OpcodeInfo& info);
  inline void TYA(const OpcodeInfo& info);
#pragma endregion

#pragma region Branch and Jump
  inline void BCC(const OpcodeInfo& info);
  inline void BCS(const OpcodeInfo& info);
  inline void BEQ(const OpcodeInfo& info);
  inline void BMI(const OpcodeInfo& info);
  inline void BNE(const OpcodeInfo& info);
  inline void BPL(const OpcodeInfo& info);
  inline void BVC(const OpcodeInfo& info);
  inline void BVS(const OpcodeInfo& info);

  inline void JMP(const OpcodeInfo& info);
  inline void JSR(const OpcodeInfo& info);
  inline void RTS(const OpcodeInfo& info);
#pragma endregion

#pragma region Load
  inline void LDA(const OpcodeInfo& info);
  inline void LDX(const OpcodeInfo& info);
  inline void LDY(const OpcodeInfo& info);
#pragma endregion

#pragma region Store
  inline void STA(const OpcodeInfo& info);
  inline void STX(const OpcodeInfo& info);
  inline void STY(const OpcodeInfo& info);
#pragma endregion

#pragma region Compare
  inline void CMP(const OpcodeInfo& info);
  inline void CPX(const OpcodeInfo& info);
  inline void CPY(const OpcodeInfo& info);
#pragma endregion

#pragma region Stack
  inline void PHA(const OpcodeInfo& info);
  inline void PHP(const OpcodeInfo& info);
  inline void PLA(const OpcodeInfo& info);
  inline void PLP(const OpcodeInfo& info);
#pragma endregion

#pragma region Illegal
  inline void AHX(const OpcodeInfo& info);
  inline void ALR(const OpcodeInfo& info);
  inline void ANC(const OpcodeInfo& info);
  inline void ARR(const OpcodeInfo& info);
  inline void AXS(const OpcodeInfo& info);
  inline void DCP(const OpcodeInfo& info);
  inline void ISC(const OpcodeInfo& info);
  inline void KIL(const OpcodeInfo& info);
  inline void LAS(const OpcodeInfo& info);
  inline void LAX(const OpcodeInfo& info);
  inline void RLA(const OpcodeInfo& info);
  inline void RRA(const OpcodeInfo& info);
  inline void SAX(const OpcodeInfo& info);
  inline void SHX(const OpcodeInfo& info);
  inline void SHY(const OpcodeInfo& info);
  inline void SLO(const OpcodeInfo& info);
  inline void SRE(const OpcodeInfo& info);
  inline void TAS(const OpcodeInfo& info);
  inline void XAA(const OpcodeInfo& info);
#pragma endregion
};

void CPU::set_reg_a(uint8_t value)
{
  m_reg.a = value;
}

void CPU::set_reg_x(uint8_t value)
{
  m_reg.x = value;
}

void CPU::set_reg_y(uint8_t value)
{
  m_reg.y = value;
}

void CPU::SEC(const OpcodeInfo& info)
{
  m_reg.set_flag(Status::Carry, true);
}

void CPU::SED(const OpcodeInfo& info)
{
  m_reg.set_flag(Status::Decimal, true);
}

void CPU::SEI(const OpcodeInfo& info)
{
  m_reg.set_flag(Status::Interrupt, true);
}

void CPU::CLC(const OpcodeInfo& info)
{
  m_reg.set_flag(Status::Carry, false);
}

void CPU::CLD(const OpcodeInfo& info)
{
  m_reg.set_flag(Status::Decimal, false);
}

void CPU::CLI(const OpcodeInfo& info)
{
  m_reg.set_flag(Status::Interrupt, false);
}

void CPU::CLV(const OpcodeInfo& info)
{
  m_reg.set_flag(Status::Overflow, false);
}

void CPU::INC(const OpcodeInfo& info)
{
  write_byte(read_byte(info.address) + 1, info.address);
  m_reg.set_zn(read_byte(info.address));
}

void CPU::INX(const OpcodeInfo& info)
{
  m_reg.x += 1;
  m_reg.set_zn(m_reg.x);
}

void CPU::INY(const OpcodeInfo& info)
{
  m_reg.y += 1;
  m_reg.set_zn(m_reg.y);
}

void CPU::DEC(const OpcodeInfo& info)
{
  write_byte(read_byte(info.address) - 1, info.address);
  m_reg.set_zn(read_byte(info.address));
}

void CPU::DEX(const OpcodeInfo& info)
{
  m_reg.x -= 1;
  m_reg.set_zn(m_reg.x);
}

void CPU::DEY(const OpcodeInfo& info)
{
  m_reg.y -= 1;
  m_reg.set_zn(m_reg.y);
}

void CPU::AND(const OpcodeInfo& info)
{
  m_reg.a &= read_byte(info.address);
  m_reg.set_zn(m_reg.a);
}

void CPU::EOR(const OpcodeInfo& info)
{
  m_reg.a ^= read_byte(info.address);
  m_reg.set_zn(m_reg.a);
}

void CPU::ORA(const OpcodeInfo& info)
{
  m_reg.a |= read_byte(info.address);
  m_reg.set_zn(m_reg.a);
}

void CPU::BIT(const OpcodeInfo& info)
{
  auto value = read_byte(info.address);
  m_reg.set_flag(Status::Zero, (m_reg.a & value) == 0);
  m_reg.set_nv(value);
}

void CPU::ADC(const OpcodeInfo& info)
{
  auto value = read_byte(info.address);
  uint8_t acc = m_reg.a;
  uint8_t carry = m_reg.get_flag(Status::Carry);

  m_reg.a += value + m_reg.get_flag(Status::Carry);

  m_reg.set_flag(Status::Carry, value + acc + carry > 0xFF);
  m_reg.set_zn(m_reg.a);
  m_reg.set_overflow(m_reg.a, acc, value);
}

void CPU::SBC(const OpcodeInfo& info)
{
  auto value = read_byte(info.address);
  auto acc = m_reg.a;
  uint8_t carry = m_reg.get_flag(Status::Carry);

  m_reg.a = acc - value - (1 - carry);

  m_reg.set_flag(Status::Carry, acc - value - (1 - carry) >= 0);
  m_reg.set_zn(m_reg.a);
  m_reg.set_overflow(m_reg.a, acc, value);
}

void CPU::LSR(const OpcodeInfo& info)
{
}

void CPU::ASL(const OpcodeInfo& info)
{
}

void CPU::ROR(const OpcodeInfo& info)
{
}

void CPU::ROL(const OpcodeInfo& info)
{
}

void CPU::BRK(const OpcodeInfo& info)
{
}

void CPU::NOP(const OpcodeInfo& info)
{
}

void CPU::RTI(const OpcodeInfo& info)
{
}

void CPU::TAX(const OpcodeInfo& info)
{
  m_reg.x = m_reg.a;
  m_reg.set_zn(m_reg.x);
}

void CPU::TAY(const OpcodeInfo& info)
{
  m_reg.y = m_reg.a;
  m_reg.set_zn(m_reg.y);
}

void CPU::TSX(const OpcodeInfo& info)
{
  m_reg.x = m_reg.s;
  m_reg.set_zn(m_reg.x);
}

void CPU::TXS(const OpcodeInfo& info)
{
  m_reg.s = m_reg.x;
}

void CPU::TXA(const OpcodeInfo& info)
{
  m_reg.a = m_reg.x;
  m_reg.set_zn(m_reg.a);
}

void CPU::TYA(const OpcodeInfo& info)
{
  m_reg.a = m_reg.y;
  m_reg.set_zn(m_reg.a);
}

void CPU::BCC(const OpcodeInfo& info)
{
}

void CPU::BCS(const OpcodeInfo& info)
{
}

void CPU::BEQ(const OpcodeInfo& info)
{
}

void CPU::BMI(const OpcodeInfo& info)
{
}

void CPU::BNE(const OpcodeInfo& info)
{
}

void CPU::BPL(const OpcodeInfo& info)
{
}

void CPU::BVC(const OpcodeInfo& info)
{
}

void CPU::BVS(const OpcodeInfo& info)
{
}

void CPU::JMP(const OpcodeInfo& info)
{
}

void CPU::JSR(const OpcodeInfo& info)
{
}

void CPU::RTS(const OpcodeInfo& info)
{
}

void CPU::LDA(const OpcodeInfo& info)
{
}

void CPU::LDX(const OpcodeInfo& info)
{
}

void CPU::LDY(const OpcodeInfo& info)
{
}

void CPU::STA(const OpcodeInfo& info)
{
}

void CPU::STX(const OpcodeInfo& info)
{
}

void CPU::STY(const OpcodeInfo& info)
{
}

void CPU::CMP(const OpcodeInfo& info)
{
}

void CPU::CPX(const OpcodeInfo& info)
{
}

void CPU::CPY(const OpcodeInfo& info)
{
}

void CPU::PHA(const OpcodeInfo& info)
{
}

void CPU::PHP(const OpcodeInfo& info)
{
}

void CPU::PLA(const OpcodeInfo& info)
{
}

void CPU::PLP(const OpcodeInfo& info)
{
}

void CPU::AHX(const OpcodeInfo& info)
{
}

void CPU::ALR(const OpcodeInfo& info)
{
}

void CPU::ANC(const OpcodeInfo& info)
{
}

void CPU::ARR(const OpcodeInfo& info)
{
}

void CPU::AXS(const OpcodeInfo& info)
{
}

void CPU::DCP(const OpcodeInfo& info)
{
}

void CPU::ISC(const OpcodeInfo& info)
{
}

void CPU::KIL(const OpcodeInfo& info)
{
}

void CPU::LAS(const OpcodeInfo& info)
{
}

void CPU::LAX(const OpcodeInfo& info)
{
}

void CPU::RLA(const OpcodeInfo& info)
{
}

void CPU::RRA(const OpcodeInfo& info)
{
}

void CPU::SAX(const OpcodeInfo& info)
{
}

void CPU::SHX(const OpcodeInfo& info)
{
}

void CPU::SHY(const OpcodeInfo& info)
{
}

void CPU::SLO(const OpcodeInfo& info)
{
}

void CPU::SRE(const OpcodeInfo& info)
{
}

void CPU::TAS(const OpcodeInfo& info)
{
}

void CPU::XAA(const OpcodeInfo& info)
{
}