#include <iostream>
#include <fstream>
#include "flash.h"

#define CONSOLE_ONLY

#ifdef CONSOLE_ONLY

int main(int argc, char *argv[])
{
  std::cout << std::endl;

  if (argc <= 1)
    throw std::runtime_error("No file path given as argument");

  const char *filename = argv[1];
  printf("Opening file : %s\n", filename);

  std::ifstream file(filename);
  if (!file.is_open())
    throw std::runtime_error("File not able to be read");
  file.seekg(0, std::ios::beg);
  Flash::SWFFile swffile(&file);

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
