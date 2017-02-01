#include "instructions.h"

namespace InstructionTests
{
  struct SystemTest : InstructionTest { };

  TEST_F(SystemTest, BRKStoresState)
  {
    cpu->load_rom({ 0x00 });
    cpu->step();

    FAIL() << "Not implemented";
  }
}