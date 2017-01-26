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

  TEST_F(InstructionTest, LSRCanShiftAccumulatorRight)
  {
    cpu->load_rom({ 0x4A });
    cpu->set_reg_a(0xA5);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x52, regs.a);
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
  }

  TEST_F(InstructionTest, LSRCanShiftAccumulatorRightWithCarry)
  {
    cpu->load_rom({ 0x4A });

    auto regs = cpu->get_registers();
    regs.a = 0xA4;
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(static_cast<int8_t>(0xD2), regs.a);
    EXPECT_EQ(false, regs.get_flag(Status::Carry));
  }

  TEST_F(InstructionTest, LSRAccumulatorCanSetZeroFlag)
  {
    cpu->load_rom({ 0x4A });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, LSRAccumulatorCanSetNegativeFlag)
  {
    cpu->load_rom({ 0x4A });

    auto regs = cpu->get_registers();
    regs.a = 0xA4;
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(static_cast<int8_t>(0xD2), regs.a);
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, LSRCanShiftRight)
  {
    cpu->load_rom({ 0x46, 0x02, 0xA5 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x52, cpu->read_byte(2));
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
  }

  TEST_F(InstructionTest, LSRCanShiftRightWithCarry)
  {
    cpu->load_rom({ 0x46, 0x02, 0xA4 });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(0xD2, cpu->read_byte(2));
    EXPECT_EQ(false, regs.get_flag(Status::Carry));
  }

  TEST_F(InstructionTest, LSRCanSetZeroFlag)
  {
    cpu->load_rom({ 0x46, 0x02, 0x00 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, LSRCanSetNegativeFlag)
  {
    cpu->load_rom({ 0x46, 0x02, 0xA4 });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(0xD2, cpu->read_byte(2));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, ASLCanShiftAccumulatorLeft)
  {
    cpu->load_rom({ 0x0A });
    cpu->set_reg_a(0xB5);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x6A, regs.a);
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
  }

  TEST_F(InstructionTest, ASLCanShiftAccumulatorLeftWithCarry)
  {
    cpu->load_rom({ 0x0A });

    auto regs = cpu->get_registers();
    regs.a = 0x35;
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(0x6B, regs.a);
    EXPECT_EQ(false, regs.get_flag(Status::Carry));
  }

  TEST_F(InstructionTest, ASLAccumulatorCanSetZeroFlag)
  {
    cpu->load_rom({ 0x0A });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, ASLAccumulatorCanSetNegativeFlag)
  {
    cpu->load_rom({ 0x0A });
    cpu->set_reg_a(0x40);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(static_cast<int8_t>(0x80), regs.a);
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, ASLCanShiftLeft)
  {
    cpu->load_rom({ 0x06, 0x02, 0xB5 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x6A, cpu->read_byte(2));
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
  }

  TEST_F(InstructionTest, ASLCanShiftLeftWithCarry)
  {
    cpu->load_rom({ 0x06, 0x02, 0x35 });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(0x6B, cpu->read_byte(2));
    EXPECT_EQ(false, regs.get_flag(Status::Carry));
  }

  TEST_F(InstructionTest, ASLCanSetZeroFlag)
  {
    cpu->load_rom({ 0x06, 0x02, 0x00 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, ASLCanSetNegativeFlag)
  {
    cpu->load_rom({ 0x06, 0x02, 0x40 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x80, cpu->read_byte(2));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, RORCanRotateRight)
  {
    FAIL();
  }

  TEST_F(InstructionTest, ROLCanRotateLeft)
  {
    FAIL();
  }
}