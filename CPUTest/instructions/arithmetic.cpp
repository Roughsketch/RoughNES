#include "instructions.h"

namespace InstructionTests
{
  struct ArithmeticTest : InstructionTest { };

  TEST_F(ArithmeticTest, ADCCanAdd)
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

  TEST_F(ArithmeticTest, ADCCarryAddsOne)
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

  TEST_F(ArithmeticTest, ADCOverflowSetsCarry)
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

  TEST_F(ArithmeticTest, ADCCanSetZero)
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

  TEST_F(ArithmeticTest, SBCCanSubtract)
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

  TEST_F(ArithmeticTest, SBCUnderflowClearsCarry)
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

  TEST_F(ArithmeticTest, LSRCanShiftAccumulatorRight)
  {
    cpu->load_rom({ 0x4A });
    cpu->set_reg_a(0xA5);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x52, regs.a);
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
  }

  TEST_F(ArithmeticTest, LSRCanShiftAccumulatorRightWithCarry)
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

  TEST_F(ArithmeticTest, LSRAccumulatorCanSetZeroFlag)
  {
    cpu->load_rom({ 0x4A });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(ArithmeticTest, LSRAccumulatorCanSetNegativeFlag)
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

  TEST_F(ArithmeticTest, LSRCanShiftRight)
  {
    cpu->load_rom({ 0x46, 0x02, 0xA5 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x52, cpu->read_byte(2));
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
  }

  TEST_F(ArithmeticTest, LSRCanShiftRightWithCarry)
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

  TEST_F(ArithmeticTest, LSRCanSetZeroFlag)
  {
    cpu->load_rom({ 0x46, 0x02, 0x00 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(ArithmeticTest, LSRCanSetNegativeFlag)
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

  TEST_F(ArithmeticTest, ASLCanShiftAccumulatorLeft)
  {
    cpu->load_rom({ 0x0A });
    cpu->set_reg_a(0xB5);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x6A, regs.a);
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
  }

  TEST_F(ArithmeticTest, ASLCanShiftAccumulatorLeftWithCarry)
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

  TEST_F(ArithmeticTest, ASLAccumulatorCanSetZeroFlag)
  {
    cpu->load_rom({ 0x0A });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(ArithmeticTest, ASLAccumulatorCanSetNegativeFlag)
  {
    cpu->load_rom({ 0x0A });
    cpu->set_reg_a(0x40);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(static_cast<int8_t>(0x80), regs.a);
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(ArithmeticTest, ASLCanShiftLeft)
  {
    cpu->load_rom({ 0x06, 0x02, 0xB5 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x6A, cpu->read_byte(2));
    EXPECT_EQ(true, regs.get_flag(Status::Carry));
  }

  TEST_F(ArithmeticTest, ASLCanShiftLeftWithCarry)
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

  TEST_F(ArithmeticTest, ASLCanSetZeroFlag)
  {
    cpu->load_rom({ 0x06, 0x02, 0x00 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(ArithmeticTest, ASLCanSetNegativeFlag)
  {
    cpu->load_rom({ 0x06, 0x02, 0x40 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x80, cpu->read_byte(2));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(ArithmeticTest, RORCanRotateAccumulatorRight)
  {
    cpu->load_rom({ 0x6A });
    cpu->set_reg_a(0xAA);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(0x55, regs.a);
  }

  TEST_F(ArithmeticTest, RORCanRotateAccumulatorRightWithCarry)
  {
    cpu->load_rom({ 0x6A });

    auto regs = cpu->get_registers();
    regs.a = 0xAA;
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(static_cast<int8_t>(0xD5), regs.a);
  }

  TEST_F(ArithmeticTest, RORCanRotateRight)
  {
    cpu->load_rom({ 0x66, 0x02, 0xAA });
    cpu->step();

    EXPECT_EQ(0x55, cpu->read_byte(2));
  }

  TEST_F(ArithmeticTest, RORCanRotateRightWithCarry)
  {
    cpu->load_rom({ 0x66, 0x02, 0xAA });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    EXPECT_EQ(0xD5, cpu->read_byte(2));
  }

  TEST_F(ArithmeticTest, ROLCanRotateAccumulatorLeft)
  {
    cpu->load_rom({ 0x2A });
    cpu->set_reg_a(0x55);
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(static_cast<int8_t>(0xAA), regs.a);
  }

  TEST_F(ArithmeticTest, ROLCanRotateAccumulatorLeftWithCarry)
  {
    cpu->load_rom({ 0x2A });

    auto regs = cpu->get_registers();
    regs.a = 0x55;
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(static_cast<int8_t>(0xAB), regs.a);
  }

  TEST_F(ArithmeticTest, ROLCanRotateLeft)
  {
    cpu->load_rom({ 0x26, 0x02, 0x55 });
    cpu->step();

    EXPECT_EQ(0xAA, cpu->read_byte(2));
  }

  TEST_F(ArithmeticTest, ROLCanRotateLeftWithCarry)
  {
    cpu->load_rom({ 0x26, 0x02, 0x55 });

    auto regs = cpu->get_registers();
    regs.set_flag(Status::Carry, true);
    cpu->set_registers(regs);

    cpu->step();

    EXPECT_EQ(0xAB, cpu->read_byte(2));
  }
}