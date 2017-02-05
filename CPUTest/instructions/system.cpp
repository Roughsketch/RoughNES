#include "instructions.h"

namespace InstructionTests
{
  struct SystemTest : InstructionTest { };

  TEST_F(SystemTest, BRKStoresState)
  {
    cpu->load_rom({ 0x00 });
    cpu->step();

    FAIL() << "Not implemented";
  }

  TEST_F(SystemTest, NOPDoesNothing)
  {
    auto before_regs = cpu->get_registers();

    cpu->load_rom({ 0xEA });
    cpu->step();

    auto after_regs = cpu->get_registers();

    EXPECT_EQ(1, after_regs.pc);
    after_regs.pc = before_regs.pc;  //  Make sure pc is same for comparison

    EXPECT_EQ(before_regs, after_regs);
  }
}