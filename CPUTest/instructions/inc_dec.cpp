#pragma once

#include "instructions.h"

namespace InstructionTests
{
  struct IncDecTest : InstructionTest { };

#pragma region INC Zero Page
  TEST_F(IncDecTest, INCZeroPageIsTwoBytes)
  {
    cpu->load_rom({ 0xE6, 0x01 });
    cpu->step();
    EXPECT_EQ(2, cpu->get_registers().pc);
  }

  TEST_F(IncDecTest, INCZeroPage)
  {
    cpu->load_rom({ 0xE6, 0x01 });
    cpu->step();

    EXPECT_EQ(2, cpu->read_byte(1));
  }

  TEST_F(IncDecTest, INCZeroPageCanSetZeroFlag)
  {
    cpu->load_rom({ 0xE6, 0x02, 0xFF });
    cpu->step();

    EXPECT_EQ(0, cpu->read_byte(2));
    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Zero));
  }

  TEST_F(IncDecTest, INCZeroPageCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xE6, 0x02, 0x7F });
    cpu->step();

    EXPECT_EQ(0x80, cpu->read_byte(2));
    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Negative));
  }
#pragma endregion

#pragma region INC Zero Page X
  TEST_F(IncDecTest, INCZeroPageXIsTwoBytes)
  {
    cpu->load_rom({ 0xF6, 0x01, 0x00 });
    cpu->step();
    EXPECT_EQ(2, cpu->get_registers().pc);
  }

  TEST_F(IncDecTest, INCZeroPageX)
  {
    cpu->load_rom({ 0xF6, 0x01, 0x00 });

    auto regs = cpu->get_registers();
    regs.x = 0x01;
    cpu->set_registers(regs);

    cpu->step();

    EXPECT_EQ(1, cpu->read_byte(2));
  }

  TEST_F(IncDecTest, INCZeroPageXCanSetZeroFlag)
  {
    cpu->load_rom({ 0xF6, 0x01, 0xFF });

    auto regs = cpu->get_registers();
    regs.x = 0x01;
    cpu->set_registers(regs);

    cpu->step();

    EXPECT_EQ(0, cpu->read_byte(2));
    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Zero));
  }

  TEST_F(IncDecTest, INCZeroPageXCanSetNegativeFlag)
  {
    cpu->load_rom({ 0xF6, 0x01, 0x7F });

    auto regs = cpu->get_registers();
    regs.x = 0x01;
    cpu->set_registers(regs);

    cpu->step();

    EXPECT_EQ(0x80, cpu->read_byte(2));
    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Negative));
  }

  TEST_F(IncDecTest, INCZeroPageXClamps)
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
  TEST_F(IncDecTest, INCAbsoluteIsThreeBytes)
  {
    cpu->load_rom({ 0xEE, 0x00, 0x01 });
    cpu->step();
    EXPECT_EQ(3, cpu->get_registers().pc);
  }

  TEST_F(IncDecTest, INCAbsolute)
  {
    cpu->load_rom({ 0xEE, 0x00, 0x01 });
    cpu->step();
    EXPECT_EQ(1, cpu->read_byte(0x0100));
  }

  TEST_F(IncDecTest, INCAbsoluteCanSetZeroFlag)
  {
    cpu->load_rom({ 0xEE, 0x03, 0x00, 0xFF });

    cpu->step();

    EXPECT_EQ(0, cpu->read_byte(3));
    EXPECT_EQ(true, cpu->get_registers().get_flag(Status::Zero));
  }

  TEST_F(IncDecTest, INCAbsoluteCanSetNegativeFlag)
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
  TEST_F(IncDecTest, INXImplied)
  {
    cpu->load_rom({ 0xE8 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(1, regs.x);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(IncDecTest, INXImpliedCanSetNegativeFlag)
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

  TEST_F(IncDecTest, INXImpliedCanSetZeroFlag)
  {
    cpu->load_rom({ 0xE8 });

    auto regs = cpu->get_registers();
    regs.x = 0xFFu;
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(0, regs.x);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }
#pragma endregion

#pragma region INY Implied
  TEST_F(IncDecTest, INYImplied)
  {
    cpu->load_rom({ 0xC8 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(1, regs.y);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }

  TEST_F(IncDecTest, INYImpliedCanSetNegativeFlag)
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

  TEST_F(IncDecTest, INYImpliedCanSetZeroFlag)
  {
    cpu->load_rom({ 0xC8 });

    auto regs = cpu->get_registers();
    regs.y = 0xFFu;
    cpu->set_registers(regs);

    cpu->step();

    regs = cpu->get_registers();

    EXPECT_EQ(0, regs.y);
    EXPECT_EQ(true, regs.get_flag(Status::Zero));
    EXPECT_EQ(false, regs.get_flag(Status::Negative));
  }
#pragma endregion

#pragma region DEX Implied
  TEST_F(IncDecTest, DEXImplied)
  {
    cpu->load_rom({ 0xCA });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(-1, regs.x);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(IncDecTest, DEXImpliedCanSetZeroFlag)
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
  TEST_F(IncDecTest, DEYImplied)
  {
    cpu->load_rom({ 0x88 });
    cpu->step();

    auto regs = cpu->get_registers();

    EXPECT_EQ(-1, regs.y);
    EXPECT_EQ(false, regs.get_flag(Status::Zero));
    EXPECT_EQ(true, regs.get_flag(Status::Negative));
  }

  TEST_F(IncDecTest, DEYImpliedCanSetZeroFlag)
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