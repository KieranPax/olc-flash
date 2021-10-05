#pragma once

#include "swftypes.h"

namespace Flash
{
  class SWFRuntime
  {
  public:
    SWFRect FrameSize;
    fixed8 FrameRate;
    uint16_t FrameCount;
    
  public:
    SWFRuntime()
    {
    }

    void ApplyTag()
    {
      return;
    }
  };
}