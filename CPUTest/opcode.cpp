#include "gtest/gtest.h"
#include "../RoughNES/opcode.h"

namespace Opcodes
{
  TEST(OpcodeTest, OpcodeDataStoresCorrectly)
  {
    EXPECT_EQ(0, Instruction::Table[0].opcode);
    EXPECT_EQ(1, Instruction::Table[0].size);
    EXPECT_EQ(Instruction::AddressMode::Implied, Instruction::Table[0].mode);
    EXPECT_EQ("BRK", Instruction::Table[0].name);
  }
}