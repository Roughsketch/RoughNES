#pragma once

#include "gtest/gtest.h"
#include "../RoughNES/register.h"

namespace RegisterTests
{
  struct RegisterTest : testing::Test
  {
    Registers regs;

    RegisterTest()
    {
    }
  };
}
