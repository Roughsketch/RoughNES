#pragma once

#include <cstdint>

enum Status : uint8_t
{
  Carry     = 1 << 0,
  Zero      = 1 << 1,
  Interrupt = 1 << 2,
  Decimal   = 1 << 3,
  Break     = 1 << 4,
  Unused    = 1 << 5,
  Overflow  = 1 << 6,
  Negative  = 1 << 7
};

struct Registers
{
  int8_t a;     //  Accumulator
  int8_t x;     //  X index
  int8_t y;     //  Y index
  uint8_t s;    //  Stack pointer
  uint8_t p;    //  Status register
  uint16_t pc;  //  Program counter

  Registers()
  {
    a = 0;
    x = 0;
    y = 0;
    s = 0;
    p = 0;
    pc = 0;

    set_flag(Status::Unused, true);
  }

  bool operator==(const Registers& other) const
  {
    return  a == other.a && 
            x == other.x &&
            y == other.y &&
            s == other.s &&
            p == other.p &&
            pc == other.pc;
  }


  void set_flag(Status status, bool value)
  {
    p = (p & ~status) | (static_cast<int>(value) * status);
  }

  bool get_flag(Status status) const
  {
    return (p & status) > 0;
  }

  void set_zn(int8_t value)
  {
    set_flag(Zero, value == 0);
    set_flag(Negative, value < 0);
  }

  void set_nv(int8_t value)
  {
    p = p & 0b00111111 | value & 0b11000000;
  }

  /**
   * \brief 
   * \param output The result of the operation that potentially produced overflow.
   * \param value1 One of the values in the operation that produced output
   * \param value2 The other value in the operation that produced output
   */
  void set_overflow(int8_t output, int8_t value1, uint8_t value2)
  {
    auto values_same_sign = ((value1 ^ value2) & 0x80) == 0;
    auto output_same_sign = ((value2 ^ output) & 0x80) == 0;
    set_flag(Overflow, values_same_sign && !output_same_sign);
  }
};