#pragma once

#include <vector>

class NESHeader
{
public:
  explicit NESHeader(std::vector<uint8_t>& header);
};