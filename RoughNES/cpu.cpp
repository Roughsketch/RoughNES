#include "cpu.h"

void(CPU::*CPU::FuncTable[])(const OpcodeInfo&) = {
  &CPU::BRK, &CPU::ORA, &CPU::KIL, &CPU::SLO, &CPU::NOP, &CPU::ORA, &CPU::ASL, &CPU::SLO,
  &CPU::PHP, &CPU::ORA, &CPU::ASL, &CPU::ANC, &CPU::NOP, &CPU::ORA, &CPU::ASL, &CPU::SLO,
  &CPU::BPL, &CPU::ORA, &CPU::KIL, &CPU::SLO, &CPU::NOP, &CPU::ORA, &CPU::ASL, &CPU::SLO,
  &CPU::CLC, &CPU::ORA, &CPU::NOP, &CPU::SLO, &CPU::NOP, &CPU::ORA, &CPU::ASL, &CPU::SLO,
  &CPU::JSR, &CPU::AND, &CPU::KIL, &CPU::RLA, &CPU::BIT, &CPU::AND, &CPU::ROL, &CPU::RLA,
  &CPU::PLP, &CPU::AND, &CPU::ROL, &CPU::ANC, &CPU::BIT, &CPU::AND, &CPU::ROL, &CPU::RLA,
  &CPU::BMI, &CPU::AND, &CPU::KIL, &CPU::RLA, &CPU::NOP, &CPU::AND, &CPU::ROL, &CPU::RLA,
  &CPU::SEC, &CPU::AND, &CPU::NOP, &CPU::RLA, &CPU::NOP, &CPU::AND, &CPU::ROL, &CPU::RLA,
  &CPU::RTI, &CPU::EOR, &CPU::KIL, &CPU::SRE, &CPU::NOP, &CPU::EOR, &CPU::LSR, &CPU::SRE,
  &CPU::PHA, &CPU::EOR, &CPU::LSR, &CPU::ALR, &CPU::JMP, &CPU::EOR, &CPU::LSR, &CPU::SRE,
  &CPU::BVC, &CPU::EOR, &CPU::KIL, &CPU::SRE, &CPU::NOP, &CPU::EOR, &CPU::LSR, &CPU::SRE,
  &CPU::CLI, &CPU::EOR, &CPU::NOP, &CPU::SRE, &CPU::NOP, &CPU::EOR, &CPU::LSR, &CPU::SRE,
  &CPU::RTS, &CPU::ADC, &CPU::KIL, &CPU::RRA, &CPU::NOP, &CPU::ADC, &CPU::ROR, &CPU::RRA,
  &CPU::PLA, &CPU::ADC, &CPU::ROR, &CPU::ARR, &CPU::JMP, &CPU::ADC, &CPU::ROR, &CPU::RRA,
  &CPU::BVS, &CPU::ADC, &CPU::KIL, &CPU::RRA, &CPU::NOP, &CPU::ADC, &CPU::ROR, &CPU::RRA,
  &CPU::SEI, &CPU::ADC, &CPU::NOP, &CPU::RRA, &CPU::NOP, &CPU::ADC, &CPU::ROR, &CPU::RRA,
  &CPU::NOP, &CPU::STA, &CPU::NOP, &CPU::SAX, &CPU::STY, &CPU::STA, &CPU::STX, &CPU::SAX,
  &CPU::DEY, &CPU::NOP, &CPU::TXA, &CPU::XAA, &CPU::STY, &CPU::STA, &CPU::STX, &CPU::SAX,
  &CPU::BCC, &CPU::STA, &CPU::KIL, &CPU::AHX, &CPU::STY, &CPU::STA, &CPU::STX, &CPU::SAX,
  &CPU::TYA, &CPU::STA, &CPU::TXS, &CPU::TAS, &CPU::SHY, &CPU::STA, &CPU::SHX, &CPU::AHX,
  &CPU::LDY, &CPU::LDA, &CPU::LDX, &CPU::LAX, &CPU::LDY, &CPU::LDA, &CPU::LDX, &CPU::LAX,
  &CPU::TAY, &CPU::LDA, &CPU::TAX, &CPU::LAX, &CPU::LDY, &CPU::LDA, &CPU::LDX, &CPU::LAX,
  &CPU::BCS, &CPU::LDA, &CPU::KIL, &CPU::LAX, &CPU::LDY, &CPU::LDA, &CPU::LDX, &CPU::LAX,
  &CPU::CLV, &CPU::LDA, &CPU::TSX, &CPU::LAS, &CPU::LDY, &CPU::LDA, &CPU::LDX, &CPU::LAX,
  &CPU::CPY, &CPU::CMP, &CPU::NOP, &CPU::DCP, &CPU::CPY, &CPU::CMP, &CPU::DEC, &CPU::DCP,
  &CPU::INY, &CPU::CMP, &CPU::DEX, &CPU::AXS, &CPU::CPY, &CPU::CMP, &CPU::DEC, &CPU::DCP,
  &CPU::BNE, &CPU::CMP, &CPU::KIL, &CPU::DCP, &CPU::NOP, &CPU::CMP, &CPU::DEC, &CPU::DCP,
  &CPU::CLD, &CPU::CMP, &CPU::NOP, &CPU::DCP, &CPU::NOP, &CPU::CMP, &CPU::DEC, &CPU::DCP,
  &CPU::CPX, &CPU::SBC, &CPU::NOP, &CPU::ISC, &CPU::CPX, &CPU::SBC, &CPU::INC, &CPU::ISC,
  &CPU::INX, &CPU::SBC, &CPU::NOP, &CPU::SBC, &CPU::CPX, &CPU::SBC, &CPU::INC, &CPU::ISC,
  &CPU::BEQ, &CPU::SBC, &CPU::KIL, &CPU::ISC, &CPU::NOP, &CPU::SBC, &CPU::INC, &CPU::ISC,
  &CPU::SED, &CPU::SBC, &CPU::NOP, &CPU::ISC, &CPU::NOP, &CPU::SBC, &CPU::INC, &CPU::ISC,
};

bool CPU::pages_differ(uint16_t a, uint16_t b)
{
  return (a & 0xFF00) != (b & 0xFF00);
}

CPU::CPU() : m_cycles(0)
{
  m_sysmem.resize(MemorySize + 1);
};

CPU::CPU(const std::vector<uint8_t>& rom) : CPU()
{
  load_rom(rom);
}

bool CPU::load_rom(const std::vector<uint8_t>& rom)
{
  if (rom.size() < MemorySize)
  {
    std::copy(std::begin(rom), std::end(rom), std::begin(m_sysmem));
    return true;
  }
  return false;
}

void CPU::step(size_t times)
{
  while (times-- > 0)
  {
    auto opcode = read_byte(m_reg.pc);
    auto info = Instruction::Table[opcode];
    auto address = get_address(info.mode);
    OpcodeInfo opinfo = { address, m_reg.pc, info.mode, info.size };

    (this->*FuncTable[opcode])(opinfo);

    m_reg.pc += info.size;
    m_cycles += info.cycles + pages_differ(m_reg.pc, address);
  }
}

Registers CPU::get_registers() const
{
  return m_reg;
}

uint16_t CPU::get_address(Instruction::AddressMode mode) const
{
  switch (mode)
  {
  case Instruction::AddressMode::Absolute:
    return read_word(m_reg.pc + 1);
  case Instruction::AddressMode::AbsoluteX:
    return read_word(m_reg.pc + 1) + m_reg.x;
  case Instruction::AddressMode::AbsoluteY:
    return read_word(m_reg.pc + 1) + m_reg.y;
  case Instruction::AddressMode::Accumulator:
    return 0;
  case Instruction::AddressMode::Immediate:
    return m_reg.pc + 1;
  case Instruction::AddressMode::Implied:
    return 0;
  case Instruction::AddressMode::Indirect:
    return read_word(read_word(m_reg.pc + 1));
  case Instruction::AddressMode::IndirectX:
    return read_word(read_byte(m_reg.pc + 1) + m_reg.x);
  case Instruction::AddressMode::IndirectY:
    return read_word(read_byte(m_reg.pc + 1)) + m_reg.y;
  case Instruction::AddressMode::Relative:
    return static_cast<int8_t>(read_byte(m_reg.pc + 1)) + m_reg.pc;
  case Instruction::AddressMode::ZeroPage:
    return read_byte(m_reg.pc + 1);
  case Instruction::AddressMode::ZeroPageX:
    return read_byte(m_reg.pc + 1) + m_reg.x;;
  case Instruction::AddressMode::ZeroPageY:
    return read_byte(m_reg.pc + 1) + m_reg.y;
  }
  return 0;
}

void CPU::set_registers(Registers regs)
{
  m_reg = regs;
}

void CPU::write_byte(uint8_t value, uint16_t pos)
{
  m_sysmem[pos] = value;
}

void CPU::write_word(uint16_t value, uint16_t pos)
{
  m_sysmem[pos] = value & 0xFF;
  ++pos;  //  Increment to avoid modulus logic in vector access (overflow will wrap around correctly)
  m_sysmem[pos] = (value >> 8) & 0xFF;
}

bool CPU::write_bytes(const std::vector<uint8_t>& data, uint16_t start)
{
  // Only set if data can fit inside memory
  if (data.size() + start < MemorySize)
  {
    uint16_t offset = 0;
    for (auto& value : data)
    {
      write_byte(value, start + offset++);
    }

    return true;
  }
  return false;
}

uint8_t CPU::read_byte(uint16_t pos) const
{
  return m_sysmem[pos];
}

uint16_t CPU::read_word(uint16_t pos) const
{
  return read_byte(pos) | (read_byte(pos + 1) << 8);
}

std::vector<uint8_t> CPU::read_bytes(uint16_t start, uint16_t size) const
{
  std::vector<uint8_t> data;

  if (start + size < MemorySize)
  {
    data.resize(size);
    std::copy(std::begin(m_sysmem) + start, std::begin(m_sysmem) + start + size, std::begin(data));
  }

  return data;
}
