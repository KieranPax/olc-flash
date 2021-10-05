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
    Character *dictionary = nullptr;
    int running = 0;
    Settings settings;

  public:
    SWFRuntime()
    {
    }

    void addCharacter(Character *v)
    {
      if (dictionary == nullptr)
        dictionary = v;
      else
        dictionary->push(v);
    }

    Character *dictionaryGet(int id)
    {
      Character *curr = dictionary;
      while (curr != nullptr)
      {
        if (curr->id == id)
          return curr;
        else
          curr = curr->next;
      }
      return nullptr;
    }

    void stop()
    {
      running = -1;
    }

    void frame()
    {
      return;
    }
  };
}