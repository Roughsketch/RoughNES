#include "instructions.h"

namespace InstructionTests
{
  struct CompareTest : InstructionTest { };

  TEST_F(CompareTest, CMPSetsZeroOnEqual)
  {
    cpu->load_rom({ 0xA9, 0x40,     //  LDA #$40
                    0xC9, 0x40 });  //  CMP #$40

    cpu->step();
    cpu->step();

    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Zero));
  }

  TEST_F(CompareTest, CMPClearsZeroOnNotEqual)
  {
    cpu->load_rom({ 0xA9, 0x40,     //  LDA #$40
                    0xC9, 0x41 });  //  CMP #$41

    cpu->step();
    cpu->step();

    EXPECT_EQ(false, cpu->get_registers().get_flag(Status::Zero));
  }

  TEST_F(CompareTest, CPXSetsZeroOnEqual)
  {
    cpu->load_rom({ 0xA2, 0x40,     //  LDX #$40
                    0xE0, 0x40 });  //  CPX #$40

    cpu->step();
    cpu->step();

    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Zero));
  }

  TEST_F(CompareTest, CPXClearsZeroOnNotEqual)
  {
    cpu->load_rom({ 0xA2, 0x40,     //  LDX #$40
                    0xE0, 0x41 });  //  CPX #$41

    cpu->step();
    cpu->step();

    EXPECT_EQ(false, cpu->get_registers().get_flag(Status::Zero));
  }

  TEST_F(CompareTest, CPYSetsZeroOnEqual)
  {
    cpu->load_rom({ 0xA0, 0x40,     //  LDY #$40
                    0xC0, 0x40 });  //  CPY #$40

    cpu->step();
    cpu->step();

    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Zero));
  }

  TEST_F(CompareTest, CPYClearsZeroOnNotEqual)
  {
    cpu->load_rom({ 0xA0, 0x40,     //  LDY #$40
                    0xC0, 0x41 });  //  CPY #$41

    cpu->step();
    cpu->step();

    EXPECT_EQ(false, cpu->get_registers().get_flag(Status::Zero));
  }
}