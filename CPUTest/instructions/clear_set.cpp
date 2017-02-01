#include "instructions.h"

namespace InstructionTests
{
  struct ClearSetTest : InstructionTest { };

  TEST_F(ClearSetTest, CLCCanClearCarry)
  {
    cpu->load_rom({ 0x18 });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Carry));
  }

  TEST_F(ClearSetTest, SECCanSetCarry)
  {
    cpu->load_rom({ 0x38 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Carry));
  }

  TEST_F(ClearSetTest, CLDCanClearDecimal)
  {
    cpu->load_rom({ 0xD8 });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Decimal, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Decimal));
  }

  TEST_F(ClearSetTest, SEDCanSetDecimal)
  {
    cpu->load_rom({ 0xF8 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Decimal));
  }

  TEST_F(ClearSetTest, CLICanClearInterrupt)
  {
    cpu->load_rom({ 0x58 });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Interrupt, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(false, regs.get_flag(Status::Interrupt));
  }

  TEST_F(ClearSetTest, SEICanSetInterrupt)
  {
    cpu->load_rom({ 0x78 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Interrupt));
  }

  TEST_F(ClearSetTest, CLVCanClearOverflow)
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