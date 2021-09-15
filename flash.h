#pragma once

#include <fstream>
#include <iostream>
#include "runtime.h"

namespace Flash
{
  class FileReader
  {
  private:
    char *buffer;

  public:
    int offset;
    int buffer_size;

  public:
    FileReader(char **_buffer, int size)
    {
      buffer = *_buffer;
      buffer_size = size;
    }

    int offset_(int size)
    {
      int out = offset;
      offset += size;
      return out;
    }

    char *ReadRaw(int size)
    {
      return buffer + offset_(size);
    }

    uint32_t *ReadU32()
    {
      return (uint32_t *)(buffer + offset_(4));
    }
    uint16_t *ReadU16()
    {
      return (uint16_t *)(buffer + offset_(2));
    }
    uint8_t *ReadU8()
    {
      return (uint8_t *)(buffer + offset_(1));
    }
    int32_t *ReadS32()
    {
      return (int32_t *)(buffer + offset_(4));
    }
    int16_t *ReadS16()
    {
      return (int16_t *)(buffer + offset_(2));
    }
    int8_t *ReadS8()
    {
      return (int8_t *)(buffer + offset_(1));
    }
  };

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
      printf("SWF File Version : %i\n", version);

      fstream->read((char *)&uncompressed_size, 4);

      printf("Uncompressed Size : %i\n", uncompressed_size);
      if (uncompressed_size > 20000000)
        throw std::runtime_error("File Exceeds Size Limit");

      data_buffer = new char[uncompressed_size];

      switch (t[0])
      {
      case 'F':
        printf("File Compression : None\n");
        fstream->read(data_buffer, uncompressed_size);
        break;
      default:
        throw std::runtime_error("Unknown / Unimplemented File Compression Method");
        break;
      }

      fs = new FileReader(&data_buffer, uncompressed_size);
    }

  private:
    char *data_buffer;
    FileReader *fs;
    uint8_t version;
    uint32_t uncompressed_size;
  };
}
