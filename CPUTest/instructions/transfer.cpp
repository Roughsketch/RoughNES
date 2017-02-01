#include "instructions.h"

namespace InstructionTests
{
  struct TransferTest : InstructionTest { };

  TEST_F(TransferTest, TAXTransfersAToX)
  {
    cpu->load_rom({ 0xAA });
    cpu->set_reg_a(0x12);
    cpu->set_reg_x(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.x);
  }

  TEST_F(TransferTest, TAXCanSetZeroFlag)
  {
    cpu->load_rom({ 0xAA });
    cpu->set_reg_x(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(TransferTest, TAXCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xAA });
    cpu->set_reg_a(0xFF);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(TransferTest, TAYTransfersAToY)
  {
    cpu->load_rom({ 0xA8 });
    cpu->set_reg_a(0x12);
    cpu->set_reg_y(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.y);
  }

  TEST_F(TransferTest, TAYCanSetZeroFlag)
  {
    cpu->load_rom({ 0xA8 });
    cpu->set_reg_y(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(TransferTest, TAYCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xA8 });
    cpu->set_reg_a(0xFF);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(TransferTest, TXATransfersXToA)
  {
    cpu->load_rom({ 0x8A });
    cpu->set_reg_a(0x12);
    cpu->set_reg_x(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x34, regs.a);
  }

  TEST_F(TransferTest, TXACanSetZeroFlag)
  {
    cpu->load_rom({ 0x8A });
    cpu->set_reg_a(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(TransferTest, TXACanSetNegativeFlag)
  {
    cpu->load_rom({ 0x8A });
    cpu->set_reg_x(0xFF);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(TransferTest, TYATransfersYToA)
  {
    cpu->load_rom({ 0x98 });
    cpu->set_reg_a(0x12);
    cpu->set_reg_y(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x34, regs.a);
  }

  TEST_F(TransferTest, TYACanSetZeroFlag)
  {
    cpu->load_rom({ 0x98 });
    cpu->set_reg_a(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(TransferTest, TYACanSetNegativeFlag)
  {
    cpu->load_rom({ 0x98 });
    cpu->set_reg_y(0xFF);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(TransferTest, TSXTransfersSToX)
  {
    cpu->load_rom({ 0xBA });
    cpu->set_reg_s(0x12);
    cpu->set_reg_x(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.x);
  }

  TEST_F(TransferTest, TSXCanSetZeroFlag)
  {
    cpu->load_rom({ 0xBA });
    cpu->set_reg_x(0x34);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(TransferTest, TSXCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xBA });
    cpu->set_reg_s(0xFF);
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }
}
