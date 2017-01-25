#pragma once
#include <memory>

#include "gtest/gtest.h"

namespace InstructionTests
{
  TEST_F(CPUInstructionTest, CLCCanClearCarry)
  {
    Registers regs;
    regs.set_flag(Status::Carry, true);

    cpu->set_registers(regs);
    cpu->CLC_18();

    regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Carry));
  }

  TEST_F(CPUInstructionTest, SECCanSetCarry)
  {
    cpu->SEC_38();

    Registers regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Carry));
  }

  TEST_F(CPUInstructionTest, CLDCanClearDecimal)
  {
    Registers regs;
    regs.set_flag(Status::Decimal, true);

    cpu->set_registers(regs);
    cpu->CLD_D8();

    regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Decimal));
  }

  TEST_F(CPUInstructionTest, SEDCanSetDecimal)
  {
    cpu->SED_F8();

    Registers regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Decimal));
  }

  TEST_F(CPUInstructionTest, CLICanClearInterrupt)
  {
    Registers regs;
    regs.set_flag(Status::Interrupt, true);

    cpu->set_registers(regs);
    cpu->CLI_58();

    regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Interrupt));
  }

  TEST_F(CPUInstructionTest, SEICanSetInterrupt)
  {
    cpu->SEI_78();

    Registers regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Interrupt));
  }

  TEST_F(CPUInstructionTest, CLVCanClearOverflow)
  {
    Registers regs;
    regs.set_flag(Status::Overflow, true);

    cpu->set_registers(regs);
    cpu->CLV_B8();

    regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
  }
}