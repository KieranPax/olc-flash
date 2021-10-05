#pragma once

#include "runtime.h"
#include "reader.h"
#include "swftypes.h"

namespace Flash::Tags
{
  char *tagTypeRef = "End\0ShowFrame\0DefineShape\0\0PlaceObject\0RemoveObject\0DefineBits\0DefineButton\0JPEGTables\0SetBackgroundColor\0DefineFont\0DefineText\0DoAction\0DefineFontInfo\0DefineSound\0StartSound\0\0DefineButtonSound\0SoundStreamHead\0SoundStreamBlock\0DefineBitsLossless\0DefineBitsJPEG2\0DefineShape2\0DefineButtonCxform\0Protect\0\0PlaceObject2\0\0RemoveObject2\0\0\0\0DefineShape3\0DefineText2\0DefineButton2\0DefineBitsJPEG3\0DefineBitsLossless2\0DefineEditText\0\0DefineSprite\0\0\0\0FrameLabel\0\0SoundStreamHead2\0DefineMorphShape\0\0DefineFont2\0\0\0\0\0\0\0\0ExportAssets\0ImportAssets\0EnableDebugger\0DoInitAction\0DefineVideoStream\0VideoFrame\0DefineFontInfo2\0\0EnableDebugger2\0ScriptLimits\0SetTabIndex\0\0\0FileAttributes\0PlaceObject3\0ImportAssets2\0\0DefineFontAlignZones\0CSMTextSettings\0DefineFont3\0SymbolClass\0Metadata\0DefineScalingGrid\0\0\0\0DoABC\0DefineShape4\0DefineMorphShape2\0\0DefineSceneAndFrameLabelData\0DefineBinaryData\0DefineFontName\0StartSound2\0DefineBitsJPEG4\0DefineFont4\0\0EnableTelemetry";
  short tagTypeRefIndices[] = {0, 4, 14, 26, 27, 39, 52, 63, 76, 87, 106, 117, 128, 137, 152, 164, 175, 176, 194, 210, 227, 246, 262, 275, 294, 302, 303, 316, 317, 331, 332, 333, 334, 347, 359, 373, 389, 409, 424, 425, 438, 439, 440, 441, 452, 453, 470, 487, 488, 500, 501, 502, 503, 504, 505, 506, 507, 520, 533, 548, 561, 579, 590, 606, 607, 623, 636, 648, 649, 650, 665, 678, 692, 693, 714, 730, 742, 754, 763, 781, 782, 783, 784, 790, 803, 821, 822, 851, 868, 883, 895, 911, 923, 924};

  struct SWFTagHeader
  {
    char *tagStart;
    unsigned int tagType;
    unsigned int tagLength;
  };
  // 0001000101 000100
  // 0100010000 010001
  // 01000100 00010001

  struct SWFTagType
  {
    int tagType;
    void (*loadFunction)(FileReader *, SWFRuntime *, SWFTagHeader *);
  };

  void loadTagEnd(FileReader *fs, SWFRuntime *context, SWFTagHeader *tag)
  {
    printf("End{ }\n");
    context->stop();
  }

  void loadTagShowFrame(FileReader *fs, SWFRuntime *context, SWFTagHeader *tag)
  {
    printf("ShowFrame{ }\n");
    context->frame();
  }

  void loadTagDefine(FileReader *fs, SWFRuntime *context, SWFTagHeader *tag)
  {
    Character *v = new Character(fs->ReadU16(), tag->tagType, tag->tagStart + 2);
    // printf("%s{ %d }\n",tagTypeRef + tagTypeRefIndices[tag->tagType], v->id);
    context->addCharacter(v);
    fs->offset += tag->tagLength - 2;
  }

  void loadTagRemove(FileReader *fs, SWFRuntime *context, SWFTagHeader *tag)
  {
    Character *v = new Character(fs->ReadU16(), tag->tagType, tag->tagStart + 2);
    // printf("%s{ %d }\n",tagTypeRef + tagTypeRefIndices[tag->tagType], v->id);
    context->addCharacter(v);
    fs->offset += tag->tagLength - 2;
  }

  void loadTagUnknown(FileReader *fs, SWFRuntime *context, SWFTagHeader *tag)
  {
    if(tag->tagType <= 93)
      printf("Unknown{ %d %d %s }\n", tag->tagType, tag->tagLength, tagTypeRef + tagTypeRefIndices[tag->tagType]);
    fs->offset += tag->tagLength;
  }

  SWFTagType TagTypes[] = {
      {0, loadTagEnd},
      {1, loadTagShowFrame},
      {2, loadTagDefine},
      {84, loadTagDefine},
      {83, loadTagDefine},
      {39, loadTagDefine},
      {6, loadTagDefine},
      {22, loadTagDefine},
      // {255, loadTagNull},
      {-1, loadTagUnknown},
  };

  SWFTagType getTagType(unsigned int type)
  {
    for (int i = 0;; i++)
    {
      if (TagTypes[i].tagType == -1)
        return TagTypes[i];
      if (TagTypes[i].tagType == type)
        return TagTypes[i];
    }
  }
}