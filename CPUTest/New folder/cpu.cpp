#pragma once

#include <memory>

#include "gtest/gtest.h"
#include "..\RoughNES\cpu.h"

namespace InstructionTests
{
  TEST_F(CPUInstructionTest, CPUMemoryInitializesToZero)
  {
    std::vector<uint8_t> data = cpu->get_memory(0, CPU::PPUSize);
    bool result = std::all_of(std::begin(data), std::end(data), [](uint8_t i) { return i == 0; });
    EXPECT_EQ(true, result);
  }

  TEST_F(CPUInstructionTest, CPUCanReadAndWriteMemory)
  {
    EXPECT_EQ(0, cpu->get_memory(0xC000));
    cpu->set_memory(0x80, 0xC000);
    EXPECT_EQ(0x80, cpu->get_memory(0xC000));
  }

  TEST_F(CPUInstructionTest, CPUCanReadAndWriteMemoryVector)
  {
    std::vector<uint8_t> data = { 0xCA, 0xFE };
    uint16_t datasize = static_cast<uint16_t>(data.size());
    std::vector<uint8_t> ret = cpu->get_memory(0xC000, datasize);

    for (auto& value : ret)
    {
      EXPECT_EQ(0, value);
    }

    cpu->set_memory(data, 0xC000);
    ret = cpu->get_memory(0xC000, datasize);

    EXPECT_EQ(true, std::equal(std::begin(data), std::end(data), std::begin(ret), std::end(ret)));
  }
}