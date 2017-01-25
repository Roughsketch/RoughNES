#pragma once

#include "instructions.h"

namespace InstructionTests
{
#pragma region INC Zero Page
  TEST_F(InstructionTest, INCZeroPageIsTwoBytes)
  {
    cpu->load_rom({ 0xE6, 0x01 });
    cpu->step();
    EXPECT_EQ(2, cpu->get_registers().pc);
  }

  TEST_F(InstructionTest, INCZeroPage)
  {
    cpu->load_rom({ 0xE6, 0x01 });
    cpu->step();

    EXPECT_EQ(2, cpu->read_byte(1));
  }

  TEST_F(InstructionTest, INCZeroPageCanSetZeroFlag)
  {
    cpu->load_rom({ 0xE6, 0x02, 0xFF });
    cpu->step();

    EXPECT_EQ(0, cpu->read_byte(2));
    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, INCZeroPageCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xE6, 0x02, 0x7F });
    cpu->step();

    EXPECT_EQ(0x80, cpu->read_byte(2));
    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Negative));
  }
#pragma endregion

#pragma region INC Zero Page X
  TEST_F(InstructionTest, INCZeroPageXIsTwoBytes)
  {
    cpu->load_rom({ 0xF6, 0x01, 0x00 });
    cpu->step();
    EXPECT_EQ(2, cpu->get_registers().pc);
  }

  TEST_F(InstructionTest, INCZeroPageX)
  {
    cpu->load_rom({ 0xF6, 0x01, 0x00 });

    auto regs = cpu->get_registers();
    regs.x = 0x01;
    cpu->set_registers(regs);

    cpu->step();

    EXPECT_EQ(1, cpu->read_byte(2));
  }

  TEST_F(InstructionTest, INCZeroPageXCanSetZeroFlag)
  {
    cpu->load_rom({ 0xF6, 0x01, 0xFF });

    auto regs = cpu->get_registers();
    regs.x = 0x01;
    cpu->set_registers(regs);

    cpu->step();

    EXPECT_EQ(0, cpu->read_byte(2));
    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, INCZeroPageXCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xF6, 0x01, 0x7F });

    auto regs = cpu->get_registers();
    regs.x = 0x01;
    cpu->set_registers(regs);

    cpu->step();

    EXPECT_EQ(0x80, cpu->read_byte(2));
    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, INCZeroPageXClamps)
  {
    cpu->load_rom({ 0xF6, 0x00, 0xFF });

    auto regs = cpu->get_registers();
    regs.x = 0x02;
    cpu->set_registers(regs);

    cpu->step();

    EXPECT_EQ(0, cpu->read_byte(1));
  }
#pragma endregion

#pragma region INC Absolute
  TEST_F(InstructionTest, INCAbsoluteIsThreeBytes)
  {
    cpu->load_rom({ 0xEE, 0x00, 0x01 });
    cpu->step();
    EXPECT_EQ(3, cpu->get_registers().pc);
  }

  TEST_F(InstructionTest, INCAbsolute)
  {
    cpu->load_rom({ 0xEE, 0x00, 0x01 });
    cpu->step();
    EXPECT_EQ(1, cpu->read_byte(0x0100));
  }

  TEST_F(InstructionTest, INCAbsoluteCanSetZeroFlag)
  {
    cpu->load_rom({ 0xEE, 0x03, 0x00, 0xFF });

    cpu->step();

    EXPECT_EQ(0, cpu->read_byte(3));
    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Zero));
  }

  TEST_F(InstructionTest, INCAbsoluteCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xEE, 0x03, 0x00, 0x7F });

    cpu->step();

    EXPECT_EQ(0x80, cpu->read_byte(3));
    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Negative));
  }
#pragma endregion

#pragma region INC Absolute X
#pragma endregion

#pragma region INX Implied
  TEST_F(InstructionTest, INXImplied)
  {
    cpu->load_rom({ 0xE8 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(1, regs.x);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, INXImpliedCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xE8 });

    auto regs = cpu->get_registers();
    regs.x = 0x7F;
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(-128, regs.x);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, INXImpliedCanSetZeroFlag)
  {
    cpu->load_rom({ 0xE8 });

    auto regs = cpu->get_registers();
    regs.x = 0xFF;
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(0, regs.x);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }
#pragma endregion

#pragma region INY Implied
  TEST_F(InstructionTest, INYImplied)
  {
    cpu->load_rom({ 0xC8 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(1, regs.y);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, INYImpliedCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xC8 });

    auto regs = cpu->get_registers();
    regs.y = 0x7F;
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(-128, regs.y);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, INYImpliedCanSetZeroFlag)
  {
    cpu->load_rom({ 0xC8 });

    auto regs = cpu->get_registers();
    regs.y = 0xFF;
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(0, regs.y);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }
#pragma endregion

#pragma region DEX Implied
  TEST_F(InstructionTest, DEXImplied)
  {
    cpu->load_rom({ 0xCA });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(-1, regs.x);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, DEXImpliedCanSetZeroFlag)
  {
    cpu->load_rom({ 0xCA });

    auto regs = cpu->get_registers();
    regs.x = 0x01;
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(0, regs.x);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }
#pragma endregion

#pragma region DEY Implied
  TEST_F(InstructionTest, DEYImplied)
  {
    cpu->load_rom({ 0x88 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(-1, regs.y);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(InstructionTest, DEYImpliedCanSetZeroFlag)
  {
    cpu->load_rom({ 0x88 });

    auto regs = cpu->get_registers();
    regs.y = 0x01;
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(0, regs.y);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }
#pragma endregion
}