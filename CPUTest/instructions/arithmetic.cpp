#include "instructions.h"

namespace InstructionTests
{
  TEST_F(InstructionTest, ADCCanAdd)
  {
    cpu->load_rom({ 0x69, 0x10 });
    cpu->set_reg_a(0x10);
    cpu->step();
    
    auto regs = cpu->get_registers();
    EXPECT_EQ(0x20, regs.a);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Carry));
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, ADCCarryAddsOne)
  {
    cpu->load_rom({ 0x69, 0x10 });

    auto regs = cpu->get_registers();
    regs.a = 0x10;
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs); 
    
    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(0x21, regs.a);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Carry));
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, ADCOverflowSetsCarry)
  {
    cpu->load_rom({ 0x69, 0x80 });
    cpu->set_reg_a(0x80);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0, regs.a);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
    EXPECT_EQ(true, regs.get_flag(Status::Overflow));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, ADCCanSetZero)
  {
    cpu->load_rom({ 0x69, 0xFF });
    cpu->set_reg_a(1);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0, regs.a);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, SBCCanSubtract)
  {
    cpu->load_rom({ 0xE9, 0x0F });
    cpu->set_reg_a(0x10);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0, regs.a);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
    EXPECT_EQ(false, regs.get_flag(Status::Overflow));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, SBCUnderflowClearsCarry)
  {
    cpu->load_rom({ 0xE9, 0x1F });
    cpu->set_reg_a(0x10);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(static_cast<int8_t>(0xF0), regs.a);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Carry));
    EXPECT_EQ(true, regs.get_flag(Status::Overflow));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }
}