#pragma once

#include "runtime.h"
#include "reader.h"
#include "swftypes.h"

namespace Flash::Tags
{
  // char *tagTypeRef[] = {
  //     "End",
  //     "ShowFrame",
  //     "DefineShape",
  //     "",
  //     "PlaceObject",
  //     "RemoveObject",
  //     "DefineBits",
  //     "DefineButton",
  //     "JPEGTables",
  //     "SetBackgroundColor",
  //     "DefineFont",
  //     "DefineText",
  //     "DoAction",
  //     "DefineFontInfo",
  //     "DefineSound",
  //     "StartSound",
  //     "",
  //     "DefineButtonSound",
  //     "SoundStreamHead",
  //     "SoundStreamBlock",
  //     "DefineBitsLossless",
  //     "DefineBitsJPEG2",
  //     "DefineShape2",
  //     "DefineButtonCxform",
  //     "Protect",
  //     "",
  //     "PlaceObject2",
  //     "",
  //     "RemoveObject2",
  //     "",
  //     "",
  //     "",
  //     "DefineShape3",
  //     "DefineText2",
  //     "DefineButton2",
  //     "DefineBitsJPEG3",
  //     "DefineBitsLossless2",
  //     "DefineEditText",
  //     "",
  //     "DefineSprite",
  //     "",
  //     "",
  //     "",
  //     "FrameLabel",
  //     "",
  //     "SoundStreamHead2",
  //     "DefineMorphShape",
  //     "",
  //     "DefineFont2",
  //     "",
  //     "",
  //     "",
  //     "",
  //     "",
  //     "",
  //     "",
  //     "ExportAssets",
  //     "ImportAssets",
  //     "EnableDebugger",
  //     "DoInitAction",
  //     "DefineVideoStream",
  //     "VideoFrame",
  //     "DefineFontInfo2",
  //     "",
  //     "EnableDebugger2",
  //     "ScriptLimits",
  //     "SetTabIndex",
  //     "",
  //     "",
  //     "FileAttributes",
  //     "PlaceObject3",
  //     "ImportAssets2",
  //     "",
  //     "DefineFontAlignZones",
  //     "CSMTextSettings",
  //     "DefineFont3",
  //     "SymbolClass",
  //     "Metadata",
  //     "DefineScalingGrid",
  //     "",
  //     "",
  //     "",
  //     "DoABC",
  //     "DefineShape4",
  //     "DefineMorphShape2",
  //     "",
  //     "DefineSceneAndFrameLabelData",
  //     "DefineBinaryData",
  //     "DefineFontName",
  //     "StartSound2",
  //     "DefineBitsJPEG4",
  //     "DefineFont4",
  //     "",
  //     "EnableTelemetry" // 93
  // };

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
    int (*loadFunction)(FileReader *, SWFRuntime *, SWFTagHeader *);
  };

  // int loadTagEnd(FileReader *fs, SWFRuntime *context, SWFTagHeader tag)
  // {
  //   printf("End{ }\n");
  //   return -1;
  // }

  // int loadTagNull(FileReader *fs, SWFRuntime *context, SWFTagHeader tag)
  // {
  //   printf("Null{ }\n");
  //   fs->offset += tag.tagLength;
  //   return -1;
  // }

  int loadTagUnknown(FileReader *fs, SWFRuntime *context, SWFTagHeader *tag)
  {
    // if (tag->tagType <= 93)
    //   printf("Unknown{ %d %d %s }\n", tag->tagType, tag->tagLength, tagTypeRef[tag->tagType]);
    // else
      printf("YaGoose{ %d %d }\n", tag->tagType, tag->tagLength);
    fs->offset += tag->tagLength;
    return -1;
  }

  SWFTagType TagTypes[] = {
      // {0, loadTagEnd},
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