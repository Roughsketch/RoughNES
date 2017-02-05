#include "instructions.h"

namespace InstructionTests
{
  struct BranchTest : InstructionTest { };

  TEST_F(BranchTest, BCCBranchesOnCarryClear)
  {
    cpu->load_rom({ 0x90, 0x40 });
    cpu->step();

    EXPECT_EQ(0x42, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BCCDoesNothingOnCarrySet)
  {
    cpu->load_rom({ 0x38,           //  SEC
                    0x90, 0x40 });  //  BCC $40

    cpu->step(2);

    EXPECT_EQ(3, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BCCCanBranchNegative)
  {
    cpu->load_rom({ 0x90, 0xFE });
    cpu->step();

    EXPECT_EQ(0, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BCSBranchesOnCarrySet)
  {
    cpu->load_rom({ 0x38,           //  SEC
                    0xB0, 0x40 });  //  BCS $40

    cpu->step(2);

    EXPECT_EQ(0x43, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BCSDoesNothingOnCarryClear)
  {
    cpu->load_rom({ 0xB0, 0x40 });
    cpu->step();

    EXPECT_EQ(2, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BCSCanBranchNegative)
  {
    cpu->load_rom({ 0x38,           //  SEC
                    0xB0, 0xFD });  //  BCS $FE

    cpu->step(2);

    EXPECT_EQ(0, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BEQBranchesOnZeroSet)
  {
    cpu->load_rom({ 0xA9, 0x40,     //  LDA #$40
                    0xC9, 0x40,     //  CMP #$40
                    0xF0, 0x40 });  //  BEQ $40

    cpu->step(3);

    EXPECT_EQ(0x46, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BEQDoesNothingOnZeroClear)
  {
    cpu->load_rom({ 0xF0, 0x40 });
    cpu->step();

    EXPECT_EQ(2, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BEQCanBranchNegative)
  {
    cpu->load_rom({ 0xA9, 0x40,     //  LDA #$40
                    0xC9, 0x40,     //  CMP #$40
                    0xF0, 0xFA });  //  BEQ $FA (-6)

    cpu->step(3);

    EXPECT_EQ(0, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BMIBranchesOnNegativeSet)
  {
    cpu->load_rom({ 0xA9, 0x40,     //  LDA #$40
                    0xC9, 0x41,     //  CMP #$41 ; Set negative flag
                    0x30, 0x40 });  //  BMI $40

    cpu->step(3);

    EXPECT_EQ(0x46, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BMIDoesNothingOnNegativeClear)
  {
    cpu->load_rom({ 0x30, 0x40 });
    cpu->step();

    EXPECT_EQ(2, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BMICanBranchNegative)
  {
    cpu->load_rom({ 0xA9, 0x40,     //  LDA #$40
                    0xC9, 0x41,     //  CMP #$41
                    0x30, 0xFA });  //  BEQ $FA (-6)

    cpu->step(3);

    EXPECT_EQ(0, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BNEBranchesOnZeroClear)
  {
    cpu->load_rom({ 0xD0, 0x40 });
    cpu->step();

    EXPECT_EQ(0x42, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BNEDoesNothingOnZeroSet)
  {
    cpu->load_rom({ 0xA9, 0x40,     //  LDA #$40
                    0xC9, 0x40,     //  CMP #$40
                    0xD0, 0x40 });  //  BNE $40

    cpu->step(3);

    EXPECT_EQ(6, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BNECanBranchNegative)
  {
    cpu->load_rom({ 0xD0, 0xFE });
    cpu->step();

    EXPECT_EQ(0, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BPLBranchesOnNegativeClear)
  {
    cpu->load_rom({ 0x10, 0x40 });
    cpu->step();

    EXPECT_EQ(0x42, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BPLDoesNothingOnNegativeSet)
  {
    cpu->load_rom({ 0xA9, 0x40,     //  LDA #$40
                    0xC9, 0x41,     //  CMP #$41
                    0x10, 0x40 });  //  BPL $40

    cpu->step(3);

    EXPECT_EQ(6, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BPLCanBranchNegative)
  {
    cpu->load_rom({ 0x10, 0xFE });
    cpu->step();

    EXPECT_EQ(0, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BVCBranchesOnOverflowClear)
  {
    cpu->load_rom({ 0x50, 0x40 });
    cpu->step();

    EXPECT_EQ(0x42, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BVCDoesNothingOnOverflowSet)
  {
    cpu->load_rom({ 0xA9, 0x70,     //  LDA #$70
                    0x69, 0x70,     //  ADC #$70  ; Set overflow
                    0x50, 0x40 });  //  BVC $40

    cpu->step(3);

    EXPECT_EQ(6, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BVCCanBranchNegative)
  {
    cpu->load_rom({ 0x50, 0xFE });
    cpu->step();

    EXPECT_EQ(0, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BVSBranchesOnOverflowSet)
  {
    cpu->load_rom({ 0xA9, 0x70,     //  LDA #$70
                    0x69, 0x70,     //  ADC #$70  ; Set overflow
                    0x70, 0x40 });  //  BVS $40

    cpu->step(3);

    EXPECT_EQ(0x46, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BVSDoesNothingOnOverflowClear)
  {
    cpu->load_rom({ 0x70, 0x40 });
    cpu->step();

    EXPECT_EQ(2, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, BVSCanBranchNegative)
  {
    cpu->load_rom({ 0xA9, 0x70,     //  LDA #$70
                    0x69, 0x70,     //  ADC #$70  ; Set overflow
                    0x70, 0xFA });  //  BVS $FA (-6)

    cpu->step(3);

    EXPECT_EQ(0, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, JMPCanSetAddress)
  {
    cpu->load_rom({ 0x4C, 0x03, 0x00, 0x00, 0x40 });
    cpu->step();

    EXPECT_EQ(0x4000, cpu->get_registers().pc);
  }

  TEST_F(BranchTest, JSRCanSetAddress)
  {

  }

  TEST_F(BranchTest, RTSCanSetAddress)
  {

  }
}
