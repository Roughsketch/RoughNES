#include "instructions.h"

namespace InstructionTests
{
  struct SystemTest : InstructionTest { };

  TEST_F(SystemTest, BRKStoresState)
  {
    std::vector<uint8_t> brk_rom(CPU::MemorySize);
    brk_rom[0xFFFF] = 0x40;

    cpu->load_rom(brk_rom);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Break));
    EXPECT_EQ(0x4000, regs.pc);
    EXPECT_EQ(0b00100000, cpu->stack_pull_byte());
    EXPECT_EQ(0, cpu->stack_pull_word());
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