#include <iostream>

#define CONSOLE_ONLY

#ifdef CONSOLE_ONLY

int main(int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
    std::cout << argv[i] << std::endl;
  return 0;
}

#else

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

namespace Flash
{
  class Player : public olc::PixelGameEngine
  {
  public:
    Player()
    {
      sAppName = "Flash Player";
    }

  public:
    bool OnUserCreate() override
    {
      return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
      Clear(olc::BLACK);
      return true;
    }
  };
};

int main()
{
  Flash::Player app;
  if (app.Construct(256, 240, 4, 4))
    app.Start();
  return 0;
}

#endif
