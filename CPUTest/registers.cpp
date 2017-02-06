#pragma once

#include "registers.h"

namespace RegisterTests
{
  TEST_F(RegisterTest, RegistersInitializeToZero)
  {
    EXPECT_EQ(0, regs.a);
    EXPECT_EQ(0, regs.x);
    EXPECT_EQ(0, regs.y);
    EXPECT_EQ(0, regs.s);
    EXPECT_EQ(Status::Unused, regs.p);  //  Unused flag starts set
    EXPECT_EQ(0, regs.pc);
  }

  TEST_F(RegisterTest, CanSetCarryBit)
  {
    regs.set_flag(Status::Carry, true);
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
    EXPECT_EQ(Status::Carry, regs.p & 0b00000001);

    regs.set_flag(Status::Carry, false);
    EXPECT_EQ(false, regs.get_flag(Status::Carry));
    EXPECT_EQ(0, regs.p & 0b00000001);
  }

  TEST_F(RegisterTest, CanSetZeroBit)
  {
    regs.set_flag(Status::Zero, true);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(Status::Zero, regs.p & 0b00000010);

    regs.set_flag(Status::Zero, false);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(0, regs.p & 0b00000010);
  }

  TEST_F(RegisterTest, CanSetInterruptBit)
  {
    regs.set_flag(Status::Interrupt, true);
    EXPECT_EQ(true, regs.get_flag(Status::Interrupt));
    EXPECT_EQ(Status::Interrupt, regs.p & 0b00000100);

    regs.set_flag(Status::Interrupt, false);
    EXPECT_EQ(false, regs.get_flag(Status::Interrupt));
    EXPECT_EQ(0, regs.p & 0b00000100);
  }

  TEST_F(RegisterTest, CanSetDecimalBit)
  {
    regs.set_flag(Status::Decimal, true);
    EXPECT_EQ(true, regs.get_flag(Status::Decimal));
    EXPECT_EQ(Status::Decimal, regs.p & 0b00001000);

    regs.set_flag(Status::Decimal, false);
    EXPECT_EQ(false, regs.get_flag(Status::Decimal));
    EXPECT_EQ(0, regs.p & 0b00001000);
  }

  TEST_F(RegisterTest, CanSetBreakBit)
  {
    regs.set_flag(Status::Break, true);
    EXPECT_EQ(true, regs.get_flag(Status::Break));
    EXPECT_EQ(Status::Break, regs.p & 0b00010000);

    regs.set_flag(Status::Break, false);
    EXPECT_EQ(false, regs.get_flag(Status::Break));
    EXPECT_EQ(0, regs.p & 0b00010000);
  }

  TEST_F(RegisterTest, CanSetStackBit)
  {
    regs.set_flag(Status::Unused, true);
    EXPECT_EQ(true, regs.get_flag(Status::Unused));
    EXPECT_EQ(Status::Unused, regs.p & 0b00100000);

    regs.set_flag(Status::Unused, false);
    EXPECT_EQ(false, regs.get_flag(Status::Unused));
    EXPECT_EQ(0, regs.p & 0b00100000);
  }

  TEST_F(RegisterTest, CanSetOverflowBit)
  {
    regs.set_flag(Status::Overflow, true);
    EXPECT_EQ(true, regs.get_flag(Status::Overflow));
    EXPECT_EQ(Status::Overflow, regs.p & 0b01000000);

    regs.set_flag(Status::Overflow, false);
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
    EXPECT_EQ(0, regs.p & 0b01000000);
  }

  TEST_F(RegisterTest, CanSetNegativeBit)
  {
    regs.set_flag(Status::Negative, true);
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
    EXPECT_EQ(Status::Negative, regs.p & 0b10000000);

    regs.set_flag(Status::Negative, false);
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
    EXPECT_EQ(0, regs.p & 0b10000000);
  }

  TEST_F(RegisterTest, CanSetNegativeAndOverflowBits)
  {
    //  Only negative
    regs.set_nv(0x80u);
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));

    //  Only overflow
    regs.set_nv(0x40);
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
    EXPECT_EQ(true, regs.get_flag(Status::Overflow));

    //  Both negative and overflow
    regs.set_nv(0xC0u);
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
    EXPECT_EQ(true, regs.get_flag(Status::Overflow));

    //  Neither negative nor overflow
    regs.set_nv(0x3F);
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
  }

  TEST_F(RegisterTest, CanSetZeroAndNegativeBits)
  {
    //  Only negative
    regs.set_zn(0x80u);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));

    //  Only zero
    regs.set_zn(0x00);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));

    //  Neither zero nor negative
    regs.set_zn(0x3F);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(RegisterTest, OverflowSetWithTwoLargeValues)
  {
    regs.set_overflow(0, 0x80u, 0x80u);
    EXPECT_EQ(true, regs.get_flag(Status::Overflow));
  }

  TEST_F(RegisterTest, SmallValuesDoNotSetOverflow)
  {
    regs.set_overflow(0x10 + 0x10, 0x10, 0x10);
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
  }

  TEST_F(RegisterTest, OppositeSignsDoNotSetOverflow)
  {
    regs.set_overflow(0xFFu, 0x80u, 0x7Fu);
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
  }

  TEST_F(RegisterTest, OverflowSetWithSmallAndLargeValues)
  {
    regs.set_overflow(0x01 + 0x7Fu, 0x01, 0x7Fu);
    EXPECT_EQ(true, regs.get_flag(Status::Overflow));
  }
};