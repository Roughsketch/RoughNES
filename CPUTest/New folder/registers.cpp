#pragma once
#include "gtest/gtest.h"
#include "..\RoughNES\register.h"

namespace RegisterTests
{
  TEST(RegisterTest, RegistersInitializeToZero)
  {
    Registers regs;

    EXPECT_EQ(0, regs.a);
    EXPECT_EQ(0, regs.x);
    EXPECT_EQ(0, regs.y);
    EXPECT_EQ(0, regs.s);
    EXPECT_EQ(0, regs.p);
    EXPECT_EQ(0, regs.pc);
  }

  TEST(RegisterTest, CanSetCarryBit)
  {
    Registers regs;

    regs.set_flag(Status::Carry, true);
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
    EXPECT_EQ(Status::Carry, regs.p & 0b00000001);

    regs.set_flag(Status::Carry, false);
    EXPECT_EQ(false, regs.get_flag(Status::Carry));
    EXPECT_EQ(0, regs.p & 0b00000001);
  }

  TEST(RegisterTest, CanSetZeroBit)
  {
    Registers regs;

    regs.set_flag(Status::Zero, true);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(Status::Zero, regs.p & 0b00000010);

    regs.set_flag(Status::Zero, false);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(0, regs.p & 0b00000010);
  }

  TEST(RegisterTest, CanSetInterruptBit)
  {
    Registers regs;

    regs.set_flag(Status::Interrupt, true);
    EXPECT_EQ(true, regs.get_flag(Status::Interrupt));
    EXPECT_EQ(Status::Interrupt, regs.p & 0b00000100);

    regs.set_flag(Status::Interrupt, false);
    EXPECT_EQ(false, regs.get_flag(Status::Interrupt));
    EXPECT_EQ(0, regs.p & 0b00000100);
  }

  TEST(RegisterTest, CanSetDecimalBit)
  {
    Registers regs;

    regs.set_flag(Status::Decimal, true);
    EXPECT_EQ(true, regs.get_flag(Status::Decimal));
    EXPECT_EQ(Status::Decimal, regs.p & 0b00001000);

    regs.set_flag(Status::Decimal, false);
    EXPECT_EQ(false, regs.get_flag(Status::Decimal));
    EXPECT_EQ(0, regs.p & 0b00001000);
  }

  TEST(RegisterTest, CanSetBreakBit)
  {
    Registers regs;

    regs.set_flag(Status::Break, true);
    EXPECT_EQ(true, regs.get_flag(Status::Break));
    EXPECT_EQ(Status::Break, regs.p & 0b00010000);

    regs.set_flag(Status::Break, false);
    EXPECT_EQ(false, regs.get_flag(Status::Break));
    EXPECT_EQ(0, regs.p & 0b00010000);
  }

  TEST(RegisterTest, CanSetStackBit)
  {
    Registers regs;

    regs.set_flag(Status::Stack, true);
    EXPECT_EQ(true, regs.get_flag(Status::Stack));
    EXPECT_EQ(Status::Stack, regs.p & 0b00100000);

    regs.set_flag(Status::Stack, false);
    EXPECT_EQ(false, regs.get_flag(Status::Stack));
    EXPECT_EQ(0, regs.p & 0b00100000);
  }

  TEST(RegisterTest, CanSetOverflowBit)
  {
    Registers regs;

    regs.set_flag(Status::Overflow, true);
    EXPECT_EQ(true, regs.get_flag(Status::Overflow));
    EXPECT_EQ(Status::Overflow, regs.p & 0b01000000);

    regs.set_flag(Status::Overflow, false);
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
    EXPECT_EQ(0, regs.p & 0b01000000);
  }

  TEST(RegisterTest, CanSetNegativeBit)
  {
    Registers regs;

    regs.set_flag(Status::Negative, true);
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
    EXPECT_EQ(Status::Negative, regs.p & 0b10000000);

    regs.set_flag(Status::Negative, false);
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
    EXPECT_EQ(0, regs.p & 0b10000000);
  }
};