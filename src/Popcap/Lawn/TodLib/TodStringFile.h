#pragma once

#ifndef __TODLIB_TODSTRINGFILE_H__
#define __TODLIB_TODSTRINGFILE_H__

#include "SexyAppFramework/Color.h"
#include "SexyAppFramework/Font.h"

class TodStringListFormat;

extern const TodStringListFormat *gTodStringFormats;
int gTodStringFormatCount = 2;

class TodStringListFormat
{ /* Size=0x20 */
  public:
    /* 0x0000 */ const char *mFormatName;
    /* 0x0004 */ Sexy::Font **mNewFont;
    /* 0x0008 */ Sexy::Color mNewColor;
    /* 0x0018 */ int mLineSpacingOffset;
    /* 0x001c */ unsigned int mFormatFlags;

  public:
    TodStringListFormat();
};

#endif
