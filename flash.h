#pragma once

#include <fstream>
#include <iostream>
#include "reader.h"
#include "runtime.h"
#include "tags.h"

void etst_func(int i)
{
  printf("Function %d\n", i);
}

namespace Flash
{
  class SWFFile
  {
  public:
    SWFFile(std::ifstream *fstream)
    {
      char *t = new char[4];
      fstream->read(t, 4);

      if (t[1] != 'W' || t[2] != 'S')
        throw std::runtime_error("Not SWF File");

      version = t[3];
      printf("SWF File Version    : %i\n", version);

      fstream->read((char *)&uncompressed_size, 4);
      uncompressed_size = 40000;

      printf("Uncompressed Size   : %i\n", uncompressed_size);
      if (uncompressed_size > 20000000)
        throw std::runtime_error("File Exceeds 20MB Size Limit");

      data_buffer = new char[uncompressed_size];

      switch (t[0])
      {
      case 'F':
        printf("File Compression    : None\n");
        fstream->read(data_buffer, uncompressed_size);
        break;
      default:
        throw std::runtime_error("Unknown / Unimplemented File Compression Method");
        break;
      }

      fstream->close();

      fs = new FileReader(&data_buffer, uncompressed_size);

      context = new SWFRuntime();

      context->FrameSize = SWFRect::fromReader(fs);
      printf("Screen Rect         : ");
      context->FrameSize.DebugPrint();
      context->FrameRate = fs->ReadFixed8();
      printf("\nFrame Rate          : %.2f\n", context->FrameRate);
      context->FrameCount = fs->ReadU16();
      printf("Frame Count         : %d\n", context->FrameCount);
    }

    Tags::SWFTagHeader nextTag()
    {
      uint32_t tagCode = fs->ReadU16();
      Tags::SWFTagHeader header{fs->now(), tagCode >> 6, tagCode & 0x3f};
      if (header.tagLength == 0x3f)
      {
        header.tagLength = fs->ReadU32();
      }

      Tags::SWFTagType tagTypeData = Tags::getTagType(header.tagType);
      tagTypeData.loadFunction(fs, context, &header);
      return header;
    }

  private:
    char *data_buffer;
    FileReader *fs;

  public:
    uint8_t version;
    uint32_t uncompressed_size;
    SWFRuntime *context;
  };
}
