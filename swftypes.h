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

  struct Character
  {
    int id;
    int type;
    char *data;
    Character *next;

    Character(int _id, int _type, char *_data)
    {
      id = _id;
      type = _type;
      data = _data;
      next = nullptr;
    }

    void push(Character* node){
      if(next == nullptr) next =node;
      else next->push(node);
    }
  };

  enum ActionScriptMode{
    Disabled,
    ASclassic,
    AS3
  };

  struct Settings{
    ActionScriptMode ASMode;
  };
}