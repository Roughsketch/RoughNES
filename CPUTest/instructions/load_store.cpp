#include "instructions.h"

namespace InstructionTests
{
  struct LoadStoreTest : InstructionTest { };

  TEST_F(LoadStoreTest, LDALoadsIntoA)
  {
    cpu->load_rom({ 0xA9, 0x12 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.a);
  }

  TEST_F(LoadStoreTest, LDACanSetZeroFlag)
  {
    cpu->load_rom({ 0xA9, 0x00 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(LoadStoreTest, LDACanSetNegativeFlag)
  {
    cpu->load_rom({ 0xA9, 0xFF });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(LoadStoreTest, LDXLoadsIntoX)
  {
    cpu->load_rom({ 0xA2, 0x12 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.x);
  }

  TEST_F(LoadStoreTest, LDXCanSetZeroFlag)
  {
    cpu->load_rom({ 0xA2, 0x00 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(LoadStoreTest, LDXCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xA2, 0xFF });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(LoadStoreTest, LDYLoadsIntoY)
  {
    cpu->load_rom({ 0xA0, 0x12 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(0x12, regs.y);
  }

  TEST_F(LoadStoreTest, LDYCanSetZeroFlag)
  {
    cpu->load_rom({ 0xA0, 0x00 });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
  }

  TEST_F(LoadStoreTest, LDYCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xA0, 0xFF });
    cpu->step();

    auto regs = cpu->get_registers();
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(LoadStoreTest, STACanStoreA)
  {
    cpu->load_rom({ 0x85, 0x01 });
    cpu->set_reg_a(0x12);
    cpu->step();

    EXPECT_EQ(0x12, cpu->read_byte(0x01));
  }

  TEST_F(LoadStoreTest, STXCanStoreX)
  {
    cpu->load_rom({ 0x86, 0x01 });
    cpu->set_reg_x(0x12);
    cpu->step();

    EXPECT_EQ(0x12, cpu->read_byte(0x01));
  }

  TEST_F(LoadStoreTest, STYCanStoreY)
  {
    cpu->load_rom({ 0x84, 0x01 });
    cpu->set_reg_y(0x12);
    cpu->step();

    EXPECT_EQ(0x12, cpu->read_byte(0x01));
  }
}