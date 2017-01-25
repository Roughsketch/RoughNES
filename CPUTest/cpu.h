#pragma once

#include <memory>

#include "gtest/gtest.h"
#include "../RoughNES/cpu.h"

namespace CPUTests
{
  struct CPUTest : testing::Test
  {
    std::unique_ptr<CPU> cpu;

    CPUTest()
    {
      cpu = std::make_unique<CPU>();
    }
  };
}
