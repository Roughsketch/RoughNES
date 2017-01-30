#include "instructions.h"

namespace InstructionTests
{
  TEST_F(InstructionTest, BCCBranchesOnCarryClear)
  {
    cpu->load_rom({ 0x90, 0x40 });
    cpu->step();

    EXPECT_EQ(0x42, cpu->get_registers().pc);
  }

  TEST_F(InstructionTest, BCCDoesNothingOnCarrySet)
  {

  }

  TEST_F(InstructionTest, BCCCanBranchNegative)
  {
    cpu->load_rom({ 0x90, 0xFE });
    cpu->step();

    EXPECT_EQ(0, cpu->get_registers().pc);
  }

  TEST_F(InstructionTest, BCSBranchesOnCarrySet)
  {

  }

  TEST_F(InstructionTest, BCSDoesNothingOnCarryClear)
  {

  }

  TEST_F(InstructionTest, BCSCanBranchNegative)
  {

  }

  TEST_F(InstructionTest, BEQBranchesOnZeroSet)
  {

  }

  TEST_F(InstructionTest, BEQDoesNothingOnZeroClear)
  {

  }

  TEST_F(InstructionTest, BEQCanBranchNegative)
  {

  }

  TEST_F(InstructionTest, BMIBranchesOnNegativeSet)
  {

  }

  TEST_F(InstructionTest, BMIDoesNothingOnNegativeClear)
  {

  }

  TEST_F(InstructionTest, BMICanBranchNegative)
  {

  }

  TEST_F(InstructionTest, BNEBranchesOnZeroClear)
  {

  }

  TEST_F(InstructionTest, BNEDoesNothingOnZeroSet)
  {

  }

  TEST_F(InstructionTest, BNECanBranchNegative)
  {

  }

  TEST_F(InstructionTest, BPLBranchesOnNegativeClear)
  {

  }

  TEST_F(InstructionTest, BPLDoesNothingOnNegativeSet)
  {

  }

  TEST_F(InstructionTest, BPLCanBranchNegative)
  {

  }

  TEST_F(InstructionTest, BVCBranchesOnOverflowClear)
  {

  }

  TEST_F(InstructionTest, BVCDoesNothingOnOverflowSet)
  {

  }

  TEST_F(InstructionTest, BVCCanBranchNegative)
  {

  }

  TEST_F(InstructionTest, BVSBranchesOnOverflowSet)
  {

  }

  TEST_F(InstructionTest, BVSDoesNothingOnOverflowClear)
  {

  }

  TEST_F(InstructionTest, BVSCanBranchNegative)
  {

  }

  TEST_F(InstructionTest, JMPCanSetAddress)
  {

  }

  TEST_F(InstructionTest, JSRCanSetAddress)
  {

  }

  TEST_F(InstructionTest, RTSCanSetAddress)
  {

  }
}
