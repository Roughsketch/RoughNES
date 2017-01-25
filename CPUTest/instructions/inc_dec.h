#pragma once

#include "gtest/gtest.h"

namespace InstructionTests
{
  TEST_F(CPUInstructionTest, INCZeroPage)
  {
    cpu->INC_E6();


  }

  TEST_F(CPUInstructionTest, INXZeroPage)
  {
    cpu->INX_E8();

    Registers regs = cpu->get_registers();

    EXPECT_EQ(1, regs.x);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(CPUInstructionTest, INXZeroPageCanSetNegativeFlag)
  {
    for (int i = 0; i < 128; i++)
    {
      cpu->INX_E8();
    }

    Registers regs = cpu->get_registers();

    EXPECT_EQ(-128, regs.x);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(CPUInstructionTest, INXZeroPageCanSetZeroFlag)
  {
    for (int i = 0; i < 256; i++)
    {
      cpu->INX_E8();
    }

    Registers regs = cpu->get_registers();

    EXPECT_EQ(0, regs.x);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }


  TEST_F(CPUInstructionTest, INYZeroPage)
  {
    cpu->INY_C8();

    Registers regs = cpu->get_registers();

    EXPECT_EQ(1, regs.y);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(CPUInstructionTest, INYZeroPageCanSetNegativeFlag)
  {
    for (int i = 0; i < 128; i++)
    {
      cpu->INY_C8();
    }

    Registers regs = cpu->get_registers();

    EXPECT_EQ(-128, regs.y);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(CPUInstructionTest, INYZeroPageCanSetZeroFlag)
  {
    for (int i = 0; i < 256; i++)
    {
      cpu->INY_C8();
    }

    Registers regs = cpu->get_registers();

    EXPECT_EQ(0, regs.y);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }


  TEST_F(CPUInstructionTest, DEXZeroPage)
  {
    cpu->DEX_CA();

    Registers regs = cpu->get_registers();

    EXPECT_EQ(-1, regs.x);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(CPUInstructionTest, DEXZeroPageCanSetZeroFlag)
  {
    for (int i = 0; i < 256; i++)
    {
      cpu->DEX_CA();
    }

    Registers regs = cpu->get_registers();

    EXPECT_EQ(0, regs.x);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }


  TEST_F(CPUInstructionTest, DEYZeroPage)
  {
    cpu->DEY_88();

    Registers regs = cpu->get_registers();

    EXPECT_EQ(-1, regs.y);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(CPUInstructionTest, DEYZeroPageCanSetZeroFlag)
  {
    for (int i = 0; i < 256; i++)
    {
      cpu->DEY_88();
    }

    Registers regs = cpu->get_registers();

    EXPECT_EQ(0, regs.y);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }
}