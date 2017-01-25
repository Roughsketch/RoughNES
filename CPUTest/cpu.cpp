#pragma once

#include "cpu.h"

namespace CPUTests
{
  TEST_F(CPUTest, CPUMemoryInitializesToZero)
  {
    auto data = cpu->read_bytes(0, CPU::MemorySize);
    bool result = std::all_of(std::begin(data), std::end(data), [](uint8_t i) { return i == 0; });
    EXPECT_EQ(true, result);
  }

  TEST_F(CPUTest, CPUCanReadAndWriteByte)
  {
    cpu->write_byte(0x80, 0xC000);
    EXPECT_EQ(0x80, cpu->read_byte(0xC000));
  }

  TEST_F(CPUTest, CPUCanReadAndWriteWord)
  {
    cpu->write_word(0x1234, 0xC000);
    EXPECT_EQ(0x1234, cpu->read_word(0xC000));
  }

  TEST_F(CPUTest, CPUCanReadAndWriteWordOnBoundary)
  {
    cpu->write_word(0x1234, 0xFFFF);
    EXPECT_EQ(0x1234, cpu->read_word(0xFFFF));
  }

  TEST_F(CPUTest, CPUCanReadAndWriteVector)
  {
    std::vector<uint8_t> data = { 0xCA, 0xFE };
    auto datasize = static_cast<uint16_t>(data.size());
    auto ret = cpu->read_bytes(0xC000, datasize);

    bool result = std::all_of(std::begin(ret), std::end(ret), [](uint8_t i) { return i == 0; });
    EXPECT_EQ(true, result);

    cpu->write_bytes(data, 0xC000);
    ret = cpu->read_bytes(0xC000, datasize);

    EXPECT_EQ(true, std::equal(std::begin(data), std::end(data), std::begin(ret), std::end(ret)));
  }

  TEST_F(CPUTest, CPUCannotReadVectorPastBoundary)
  {
    auto vector = cpu->read_bytes(0xFFFF, 0xFFFF);
    ASSERT_TRUE(vector.empty());
  }

  TEST_F(CPUTest, CPUCannotWriteVectorPastBoundary)
  {
    ASSERT_FALSE(cpu->write_bytes({ 0xCA, 0xFE }, 0xFFFF));
  }

  TEST_F(CPUTest, CPUGetAbsoluteAddress)
  {
    cpu->load_rom({ 0x00, 0x34, 0x12 });
    auto address = cpu->get_address(Instruction::AddressMode::Absolute);
    ASSERT_EQ(0x1234, address);
  }

  TEST_F(CPUTest, CPUGetAbsoluteXAddress)
  {
    cpu->load_rom({ 0x00, 0x34, 0x12 });
    cpu->set_reg_x(0x20);
    auto address = cpu->get_address(Instruction::AddressMode::AbsoluteX);
    ASSERT_EQ(0x1234 + 0x20, address);
  }

  TEST_F(CPUTest, CPUGetAbsoluteYAddress)
  {
    cpu->load_rom({ 0x00, 0x34, 0x12 });
    cpu->set_reg_y(0x20);
    auto address = cpu->get_address(Instruction::AddressMode::AbsoluteY);
    ASSERT_EQ(0x1234 + 0x20, address);
  }

  TEST_F(CPUTest, CPUGetAccumulatorAddress)
  {
    auto address = cpu->get_address(Instruction::AddressMode::Accumulator);
    ASSERT_EQ(0, address);
  }

  TEST_F(CPUTest, CPUGetImmediateAddress)
  {
    auto address = cpu->get_address(Instruction::AddressMode::Immediate);
    ASSERT_EQ(1, address);
  }

  TEST_F(CPUTest, CPUGetImpliedAddress)
  {
    auto address = cpu->get_address(Instruction::AddressMode::Implied);
    ASSERT_EQ(0, address);
  }

  TEST_F(CPUTest, CPUGetIndirectAddress)
  {
    cpu->load_rom({ 0x00, 0x03, 0x00, 0x34, 0x12 });
    auto address = cpu->get_address(Instruction::AddressMode::Indirect);
    ASSERT_EQ(0x1234, address);
  }

  TEST_F(CPUTest, CPUGetIndirectXAddress)
  {
    cpu->load_rom({ 0x00, 0x02, 0x00, 0x34, 0x12 });
    cpu->set_reg_x(0x01);
    auto address = cpu->get_address(Instruction::AddressMode::IndirectX);
    ASSERT_EQ(0x1234, address);
  }

  TEST_F(CPUTest, CPUGetIndirectYAddress)
  {
    cpu->load_rom({ 0x00, 0x03, 0x00, 0x34, 0x12 });
    cpu->set_reg_y(0x20);
    auto address = cpu->get_address(Instruction::AddressMode::IndirectY);
    ASSERT_EQ(0x1234 + 0x20, address);
  }

  TEST_F(CPUTest, CPUGetRelativeAddressNegative)
  {
    cpu->load_rom({ 0x00, 0x80 });
    auto address = cpu->get_address(Instruction::AddressMode::Relative);
    EXPECT_EQ(static_cast<uint16_t>(-126), address);
  }

  TEST_F(CPUTest, CPUGetRelativeAddressPositive)
  {
    cpu->load_rom({ 0x00, 0x7F });
    auto address = cpu->get_address(Instruction::AddressMode::Relative);
    EXPECT_EQ(129, address);
  }

  TEST_F(CPUTest, CPUGetZeroPageAddress)
  {
    cpu->load_rom({ 0x00, 0x03 });
    auto address = cpu->get_address(Instruction::AddressMode::ZeroPage);
    ASSERT_EQ(0x03, address);
  }

  TEST_F(CPUTest, CPUGetZeroPageXAddress)
  {
    cpu->load_rom({ 0x00, 0x02 });
    cpu->set_reg_x(0x01);
    auto address = cpu->get_address(Instruction::AddressMode::ZeroPageX);
    ASSERT_EQ(0x03, address);
  }

  TEST_F(CPUTest, CPUGetZeroPageYAddress)
  {
    cpu->load_rom({ 0x00, 0x02 });
    cpu->set_reg_y(0x01);
    auto address = cpu->get_address(Instruction::AddressMode::ZeroPageY);
    ASSERT_EQ(0x03, address);
  }
}
