#include "instructions.h"

namespace InstructionTests
{
  struct StackTest : InstructionTest { };

  TEST_F(StackTest, PHAPushesA)
  {
    cpu->load_rom({ 0xA9, 0x40, //  LDA #$40
                    0x48 });    //  PHA

    cpu->step(2);
    
    EXPECT_EQ(0x40, cpu->stack_pull_byte());
  }

  TEST_F(StackTest, PHPPushesP)
  {
    cpu->load_rom({ 0x38,       //  SEC
                    0xF8,       //  SED
                    0x78,       //  SEI
                    0x08 });    //  PHP

    cpu->step(4);

    //  0b00101101 is mask for Unused, Interrupt, Decimal, and Carry flags.
    EXPECT_EQ(0b00101101, cpu->stack_pull_byte());
  }

  TEST_F(StackTest, PLAPullsA)
  {
    cpu->load_rom({ 0xA9, 0x40, //  LDA #$40
                    0x68 });    //  PLA

    cpu->step(2);

    EXPECT_EQ(0, cpu->get_registers().a);
  }

  TEST_F(StackTest, PLPPullsP)
  {
    cpu->load_rom({ 0x38,       //  SEC
                    0xF8,       //  SED
                    0x78,       //  SEI
                    0x28 });    //  PLP

    cpu->step(4);

    EXPECT_EQ(0, cpu->stack_pull_byte());
  }
}