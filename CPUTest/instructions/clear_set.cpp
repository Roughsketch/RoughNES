#pragma once

#include "instructions.h"

namespace InstructionTests
{
  TEST_F(InstructionTest, CLCCanClearCarry)
  {
    cpu->load_rom({ 0x18 });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Carry));
  }

  TEST_F(InstructionTest, SECCanSetCarry)
  {
    cpu->load_rom({ 0x38 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Carry));
  }

  TEST_F(InstructionTest, CLDCanClearDecimal)
  {
    cpu->load_rom({ 0xD8 });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Decimal, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Decimal));
  }

  TEST_F(InstructionTest, SEDCanSetDecimal)
  {
    cpu->load_rom({ 0xF8 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Decimal));
  }

  TEST_F(InstructionTest, CLICanClearInterrupt)
  {
    cpu->load_rom({ 0x58 });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Interrupt, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Interrupt));
  }

  TEST_F(InstructionTest, SEICanSetInterrupt)
  {
    cpu->load_rom({ 0x78 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Interrupt));
  }

  TEST_F(InstructionTest, CLVCanClearOverflow)
  {
    cpu->load_rom({ 0xB8 });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Overflow, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
  }
}