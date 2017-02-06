#pragma once

#include "instructions.h"

namespace InstructionTests
{
  struct LogicalTest : InstructionTest { };

  TEST_F(LogicalTest, ANDDoesBitwiseAnd)
  {
    cpu->load_rom({ 0x29, 0b10100101 });
    cpu->set_reg_a(0b01010101);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(5, regs.a);
  }

  TEST_F(LogicalTest, ANDCanMaskBits)
  {
    cpu->load_rom({ 0x29, 0x18 });
    cpu->set_reg_a(0xFF);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x18, regs.a);
  }

  TEST_F(LogicalTest, EORDoesBitwiseXor)
  {
    cpu->load_rom({ 0x49, 0b10100101 });
    cpu->set_reg_a(0b01010101);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(static_cast<int8_t>(0xF0u), regs.a);
  }

  TEST_F(LogicalTest, ORADoesBitwiseOr)
  {
    cpu->load_rom({ 0x09, 0b10100101 });
    cpu->set_reg_a(0b01010101);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(static_cast<int8_t>(0xF5u), regs.a);
  }

  TEST_F(LogicalTest, BITCanSetNegative)
  {
    cpu->load_rom({ 0x24, 0x02, 0b10100101 });
    cpu->set_reg_a(0b11010101);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(LogicalTest, BITCanSetOverflow)
  {
    cpu->load_rom({ 0x24, 0x02, 0b01100101 });
    cpu->set_reg_a(0b11010101);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Overflow));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(LogicalTest, BITCanSetZero)
  {
    cpu->load_rom({ 0x24, 0x02, 0b00010101 });
    cpu->set_reg_a(0b10101010);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }
}