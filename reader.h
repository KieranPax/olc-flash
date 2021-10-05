#pragma once

#define fixed8 float
#define fixed float

namespace Flash
{
  class FileReader
  {
  private:
    char bitCurrent;
    int bitOffset = 0;

  public:
    char *_buffer;
    int offset = 0;
    int buffer_size;
    char *buffer() { return _buffer; }

  public:
    FileReader(char **buffer_, int size)
    {
      _buffer = *buffer_;
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
      return _buffer + offset_(size);
    }

    uint32_t ReadU32()
    {
      return *(uint32_t *)(_buffer + offset_(4));
    }
    uint16_t ReadU16()
    {
      return *(uint16_t *)(_buffer + offset_(2));
    }
    uint8_t ReadU8()
    {
      return *(uint8_t *)(_buffer + offset_(1));
    }
    int32_t ReadS32()
    {
      return *(int32_t *)(_buffer + offset_(4));
    }
    int16_t ReadS16()
    {
      return *(int16_t *)(_buffer + offset_(2));
    }
    int8_t ReadS8()
    {
      return *(int8_t *)(_buffer + offset_(1));
    }
    fixed ReadFixed()
    {
      return (float)(ReadS32()) / 0x10000;
    }
    fixed8 ReadFixed8()
    {
      return (float)(ReadS16()) / 0x100;
    }
    float ReadFloat()
    {
      return *(float *)(_buffer + offset_(4));
    }
    double ReadDouble()
    {
      return *(double *)(_buffer + offset_(8));
    }
    uint32_t EncodedInt()
    {
      uint32_t val = 0;
      for (int i = 0; i < 5; i++)
      {
        val += _buffer[offset + i] << (7 * i);
        if (_buffer[offset + i] & 0x80 == 0)
        {
          offset += i + 1;
          return val;
        }
      }
      return 0;
    }

    void resetBits()
    {
      bitOffset = 0;
    }

    unsigned int bitsU(uint8_t size)
    {
      unsigned int out = 0;
      if (size == 0)
        return 0;
      if (size >= 32)
        throw std::range_error("Bit Width Exceeds Integer Limit");
      if (bitOffset == 0)
      {
        bitCurrent = ReadU8(); // 01111000
      }
      if (size + bitOffset > 8)
      {
        int firstByteSize = 8 - bitOffset;
        int lastByteSize = ((size - firstByteSize) & 0b111); // (size - first) % 8
        int middleByteCount = (size - firstByteSize - lastByteSize) >> 3;

        out = bitCurrent & ((1 << firstByteSize) - 1);
        for (; middleByteCount > 0; middleByteCount--)
        {
          out = (out << 8) + ReadU8();
        }
        bitCurrent = ReadU8();
        out = (out << lastByteSize) + (bitCurrent >> (8 - lastByteSize));
      }
      else
      {
        out = (bitCurrent >> (8 - bitOffset - size)) & ((1 << size) - 1);
      }
      bitOffset = (bitOffset + size) & 0b111;
      return out;
    }

    int bitsS(uint8_t size)
    {
      unsigned int base = bitsU(size);
      if (base & (1 << (size - 1)))
        return base - (1 << (size - 1));
      else
        return base;
    }

    char* now()
    {
      return _buffer + offset;
    }
  };
}