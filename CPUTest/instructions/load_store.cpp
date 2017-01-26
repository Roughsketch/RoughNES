#include "instructions.h"

namespace InstructionTests
{
  TEST_F(InstructionTest, LDALoadsIntoA)
  {
    cpu->load_rom({ 0xA9, 0x12 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.a);
  }

  TEST_F(InstructionTest, LDACanSetZeroFlag)
  {
    cpu->load_rom({ 0xA9, 0x00 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, LDACanSetNegativeFlag)
  {
    cpu->load_rom({ 0xA9, 0xFF });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, LDXLoadsIntoX)
  {
    cpu->load_rom({ 0xA2, 0x12 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.x);
  }

  TEST_F(InstructionTest, LDXCanSetZeroFlag)
  {
    cpu->load_rom({ 0xA2, 0x00 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, LDXCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xA2, 0xFF });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, LDYLoadsIntoY)
  {
    cpu->load_rom({ 0xA0, 0x12 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.y);
  }

  TEST_F(InstructionTest, LDYCanSetZeroFlag)
  {
    cpu->load_rom({ 0xA0, 0x00 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, LDYCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xA0, 0xFF });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, STACanStoreA)
  {
    cpu->load_rom({ 0x85, 0x01 });
    cpu->set_reg_a(0x12);
    cpu->step();

    EXPECT_EQ(0x12, cpu->read_byte(0x01));
  }

  TEST_F(InstructionTest, STXCanStoreX)
  {
    cpu->load_rom({ 0x86, 0x01 });
    cpu->set_reg_x(0x12);
    cpu->step();

    EXPECT_EQ(0x12, cpu->read_byte(0x01));
  }

  TEST_F(InstructionTest, STYCanStoreY)
  {
    cpu->load_rom({ 0x84, 0x01 });
    cpu->set_reg_y(0x12);
    cpu->step();

    EXPECT_EQ(0x12, cpu->read_byte(0x01));
  }
}