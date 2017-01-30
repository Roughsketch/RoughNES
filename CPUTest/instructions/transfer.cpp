#include "instructions.h"

namespace InstructionTests
{
  TEST_F(InstructionTest, TAXTransfersAToX)
  {
    cpu->load_rom({ 0xAA });
    cpu->set_reg_a(0x12);
    cpu->set_reg_x(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.x);
  }

  TEST_F(InstructionTest, TAXCanSetZeroFlag)
  {
    cpu->load_rom({ 0xAA });
    cpu->set_reg_x(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, TAXCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xAA });
    cpu->set_reg_a(0xFF);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, TAYTransfersAToY)
  {
    cpu->load_rom({ 0xA8 });
    cpu->set_reg_a(0x12);
    cpu->set_reg_y(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.y);
  }

  TEST_F(InstructionTest, TAYCanSetZeroFlag)
  {
    cpu->load_rom({ 0xA8 });
    cpu->set_reg_y(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, TAYCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xA8 });
    cpu->set_reg_a(0xFF);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, TXATransfersXToA)
  {
    cpu->load_rom({ 0x8A });
    cpu->set_reg_a(0x12);
    cpu->set_reg_x(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x34, regs.a);
  }

  TEST_F(InstructionTest, TXACanSetZeroFlag)
  {
    cpu->load_rom({ 0x8A });
    cpu->set_reg_a(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, TXACanSetNegativeFlag)
  {
    cpu->load_rom({ 0x8A });
    cpu->set_reg_x(0xFF);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, TYATransfersYToA)
  {
    cpu->load_rom({ 0x98 });
    cpu->set_reg_a(0x12);
    cpu->set_reg_y(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x34, regs.a);
  }

  TEST_F(InstructionTest, TYACanSetZeroFlag)
  {
    cpu->load_rom({ 0x98 });
    cpu->set_reg_a(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, TYACanSetNegativeFlag)
  {
    cpu->load_rom({ 0x98 });
    cpu->set_reg_y(0xFF);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, TSXTransfersSToX)
  {
    cpu->load_rom({ 0xBA });
    cpu->set_reg_s(0x12);
    cpu->set_reg_x(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.x);
  }

  TEST_F(InstructionTest, TSXCanSetZeroFlag)
  {
    cpu->load_rom({ 0xBA });
    cpu->set_reg_x(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, TSXCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xBA });
    cpu->set_reg_s(0xFF);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }
}
