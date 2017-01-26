#include "instructions.h"

namespace InstructionTests
{
  TEST_F(InstructionTest, TAXTransfersAToX)
  {
    cpu->load_rom({0xAA});
    cpu->set_reg_a(0x12);
    cpu->set_reg_x(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.x);
  }
}