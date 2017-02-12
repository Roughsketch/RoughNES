#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include "register.h"
#include "opcode.h"
#include "cartridge.h"
#include "nes.h"

class NES;

class CPU
{
  const uint16_t NMIVectorAddress = 0xFFFA;
  const uint16_t IRQVectorAddress = 0xFFFE;
  const uint16_t StackStart = 0x100;

  std::shared_ptr<NES> m_console;

  std::vector<uint8_t> m_rom;
  std::vector<uint8_t> m_sysmem;
  Registers m_reg;
  uint64_t m_cycles;

  enum Interrupt : uint8_t
  {
    None,
    NMI,
    IRQ
  };

  std::shared_ptr<NES> m_console;

  std::vector<uint8_t> m_rom;
  std::vector<uint8_t> m_sysmem;
  Registers m_reg;
  uint64_t m_cycles;
  Interrupt m_interrupt;

  struct OpcodeInfo
  {
    uint16_t address;
    uint16_t pc;
    Instruction::AddressMode mode;
    uint8_t size;
  };

  static void(CPU::*FuncTable[])(const OpcodeInfo&);

  static inline bool pages_differ(uint16_t a, uint16_t b);
public:
  static const size_t MemorySize = 0x10000;

  CPU();
  explicit CPU(const std::vector<uint8_t>& rom);
  explicit CPU(Cartridge& cart);
  explicit CPU(std::shared_ptr<NES> console);

  bool load_rom(const std::vector<uint8_t>& rom);
  uint64_t step(size_t times = 1);
  void stall(uint64_t cycles);

  void set_registers(Registers regs);
  void write_byte(uint8_t value, uint16_t pos);
  void write_word(uint16_t value, uint16_t pos);
  bool write_bytes(const std::vector<uint8_t>& data, uint16_t start);

  Registers get_registers() const;
  uint16_t get_address(Instruction::AddressMode mode) const;
  uint8_t read_byte(uint16_t pos) const;
  uint16_t read_word(uint16_t pos) const;
  std::vector<uint8_t> read_bytes(uint16_t start, size_t size) const;

  inline void set_reg_a(uint8_t value);
  inline void set_reg_x(uint8_t value);
  inline void set_reg_y(uint8_t value);
  inline void set_reg_s(uint8_t value);

  inline void stack_push_byte(uint8_t value);
  inline uint8_t stack_pull_byte();
  inline void stack_push_word(uint16_t value);
  inline uint16_t stack_pull_word();

  inline void trigger_nmi();
  inline void trigger_irq();
  inline void interrupt(Interrupt inter);

#pragma region Set and Clear status flags
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

void CPU::set_reg_s(uint8_t value)
{
  m_reg.s = value;
}

void CPU::stack_push_byte(uint8_t value)
{
  write_byte(value, StackStart | m_reg.s);
  --m_reg.s;
}

uint8_t CPU::stack_pull_byte()
{
  ++m_reg.s;
  return read_byte(StackStart | m_reg.s);
}

void CPU::stack_push_word(uint16_t value)
{
  write_word(value, StackStart | m_reg.s);
  --m_reg.s;
}

uint16_t CPU::stack_pull_word()
{
  ++m_reg.s;
  return read_word(StackStart | m_reg.s);
}

void CPU::interrupt(Interrupt inter)
{
  stack_push_word(m_reg.pc);
  PHP(OpcodeInfo{});

  switch (inter)
  { 
    case Interrupt::NMI:
      m_reg.pc = read_word(NMIVectorAddress);
      break;
    case Interrupt::IRQ:
      m_reg.pc = read_word(IRQVectorAddress);
      break;
    default:
      break;
  }

  m_reg.set_flag(Status::Interrupt, true);
  m_cycles += 7;
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
  uint8_t temp;

  if (info.mode == Instruction::AddressMode::Accumulator)
  {
    temp = m_reg.a;
    m_reg.a = (temp / 2) | (m_reg.get_flag(Status::Carry) << 7);
    m_reg.set_flag(Status::Carry, (temp & 1) > 0);
    m_reg.set_zn(m_reg.a);
  }
  else
  {
    temp = read_byte(info.address);
    int8_t result = (temp / 2) | (m_reg.get_flag(Status::Carry) << 7);
    m_reg.set_flag(Status::Carry, (temp & 1) > 0);
    m_reg.set_zn(result);
    write_byte(result, info.address);
  }
}

void CPU::ASL(const OpcodeInfo& info)
{
  if (info.mode == Instruction::AddressMode::Accumulator)
  {
    uint8_t temp = m_reg.a;
    m_reg.a = (temp * 2) | static_cast<int>(m_reg.get_flag(Status::Carry));;
    m_reg.set_flag(Status::Carry, (temp & 0x80) > 0);
    m_reg.set_zn(m_reg.a);
  }
  else
  {
    auto temp = read_byte(info.address);
    int8_t result = (temp * 2) | static_cast<int>(m_reg.get_flag(Status::Carry));
    m_reg.set_flag(Status::Carry, (temp & 0x80) > 0);
    m_reg.set_zn(result);
    write_byte(result, info.address);
  }
}

void CPU::ROR(const OpcodeInfo& info)
{
  if (info.mode == Instruction::AddressMode::Accumulator)
  {
    auto bit_zero = (m_reg.a & 1) > 0;
    m_reg.a = (static_cast<uint8_t>(m_reg.a) >> 1) | (m_reg.get_flag(Status::Carry) << 7);
    m_reg.set_flag(Status::Carry, bit_zero);
    m_reg.set_zn(m_reg.a);
  }
  else
  {
    auto value = read_byte(info.address);
    auto bit_zero = (value & 1) > 0;
    value = (value >> 1) | (m_reg.get_flag(Status::Carry) << 7);
    m_reg.set_flag(Status::Carry, bit_zero);
    m_reg.set_zn(value);
    write_byte(value, info.address);
  }
}

void CPU::ROL(const OpcodeInfo& info)
{
  if (info.mode == Instruction::AddressMode::Accumulator)
  {
    auto last_bit = (m_reg.a & 0x80) > 0;
    m_reg.a = (static_cast<uint8_t>(m_reg.a) << 1) | static_cast<int>(m_reg.get_flag(Status::Carry));
    m_reg.set_flag(Status::Carry, last_bit);
    m_reg.set_zn(m_reg.a);
  }
  else
  {
    auto value = read_byte(info.address);
    auto last_bit = (value & 0x80) > 0;
    value = (value << 1) | static_cast<int>(m_reg.get_flag(Status::Carry));
    m_reg.set_flag(Status::Carry, last_bit);
    m_reg.set_zn(value);
    write_byte(value, info.address);
  }
}

void CPU::BRK(const OpcodeInfo& info)
{
  stack_push_word(m_reg.pc);
  stack_push_byte(m_reg.p);

  m_reg.pc = read_word(IRQVectorAddress) - info.size;
  m_reg.set_flag(Status::Break, true);
}

void CPU::NOP(const OpcodeInfo& info)
{
  //  Do nothing
}

void CPU::RTI(const OpcodeInfo& info)
{
  m_reg.p = stack_pull_byte();
  m_reg.pc = stack_pull_word();
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
  if (!m_reg.get_flag(Status::Carry))
  {
    m_reg.pc = info.address;
  }
}

void CPU::BCS(const OpcodeInfo& info)
{
  if (m_reg.get_flag(Status::Carry))
  {
    m_reg.pc = info.address;
  }
}

void CPU::BEQ(const OpcodeInfo& info)
{
  if (m_reg.get_flag(Status::Zero))
  {
    m_reg.pc = info.address;
  }
}

void CPU::BMI(const OpcodeInfo& info)
{
  if (m_reg.get_flag(Status::Negative))
  {
    m_reg.pc = info.address;
  }
}

void CPU::BNE(const OpcodeInfo& info)
{
  if (!m_reg.get_flag(Status::Zero))
  {
    m_reg.pc = info.address;
  }
}

void CPU::BPL(const OpcodeInfo& info)
{
  if (!m_reg.get_flag(Status::Negative))
  {
    m_reg.pc = info.address;
  }
}

void CPU::BVC(const OpcodeInfo& info)
{
  if (!m_reg.get_flag(Status::Overflow))
  {
    m_reg.pc = info.address;
  }
}

void CPU::BVS(const OpcodeInfo& info)
{
  if (m_reg.get_flag(Status::Overflow))
  {
    m_reg.pc = info.address;
  }
}

void CPU::JMP(const OpcodeInfo& info)
{
  m_reg.pc = read_word(info.address) - info.size;
}

void CPU::JSR(const OpcodeInfo& info)
{
  stack_push_word(m_reg.pc - 1);
  m_reg.pc = info.address;
}

void CPU::RTS(const OpcodeInfo& info)
{
  m_reg.pc = stack_pull_word() - 1;
}

void CPU::LDA(const OpcodeInfo& info)
{
  m_reg.a = read_byte(info.address);
  m_reg.set_zn(m_reg.a);
}

void CPU::LDX(const OpcodeInfo& info)
{
  m_reg.x = read_byte(info.address);
  m_reg.set_zn(m_reg.x);
}

void CPU::LDY(const OpcodeInfo& info)
{
  m_reg.y = read_byte(info.address);
  m_reg.set_zn(m_reg.y);
}

void CPU::STA(const OpcodeInfo& info)
{
  write_byte(m_reg.a, info.address);
}

void CPU::STX(const OpcodeInfo& info)
{
  write_byte(m_reg.x, info.address);
}

void CPU::STY(const OpcodeInfo& info)
{
  write_byte(m_reg.y, info.address);
}

void CPU::CMP(const OpcodeInfo& info)
{
  int8_t mem = read_byte(info.address);
  int8_t value = m_reg.a - mem;

  m_reg.set_flag(Status::Carry, m_reg.a >= mem);
  m_reg.set_zn(value);
}

void CPU::CPX(const OpcodeInfo& info)
{
  int8_t mem = read_byte(info.address);
  int8_t value = m_reg.x - mem;

  m_reg.set_flag(Status::Carry, m_reg.x >= mem);
  m_reg.set_zn(value);
}

void CPU::CPY(const OpcodeInfo& info)
{
  int8_t mem = read_byte(info.address);
  int8_t value = m_reg.y - mem;

  m_reg.set_flag(Status::Carry, m_reg.y >= mem);
  m_reg.set_zn(value);
}

void CPU::PHA(const OpcodeInfo& info)
{
  stack_push_byte(m_reg.a);
}

void CPU::PHP(const OpcodeInfo& info)
{
  stack_push_byte(m_reg.p);
}

void CPU::PLA(const OpcodeInfo& info)
{
  m_reg.a = stack_pull_byte();
  m_reg.set_zn(m_reg.a);
}

void CPU::PLP(const OpcodeInfo& info)
{
  m_reg.p = stack_pull_byte();
}

//
//Illegal Opcodes Below.
//
#pragma region Illegal Opcodes
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
#pragma endregion