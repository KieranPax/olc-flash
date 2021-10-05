#pragma once

#include "reader.h"
#include <string>

namespace Flash
{
  struct SWFRect
  {
    int xmin;
    int xmax;
    int ymin;
    int ymax;

    static SWFRect fromReader(FileReader *fs)
    {
      fs->resetBits();
      int prec = fs->bitsU(5);
      SWFRect rect{fs->bitsS(prec), fs->bitsS(prec), fs->bitsS(prec), fs->bitsS(prec)};
      fs->resetBits();
      return rect;
    }

    void DebugPrint()
    {
      printf("Rect{%i %i %i %i}", xmin, xmax, ymin, ymax);
    }
  };
}