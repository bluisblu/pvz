#pragma once

#ifndef __TODLIB_TODSTRINGFILE_H__
#define __TODLIB_TODSTRINGFILE_H__

#include "../SexyAppFramework/Color.h"
#include "../SexyAppFramework/Font.h"

class TodStringListFormat;

extern const TodStringListFormat* gTodStringFormats;
int gTodStringFormatCount = 2;

class TodStringListFormat { /* Size=0x20 */
  /* 0x0000 */ public: const char* mFormatName;
  /* 0x0004 */ public: Sexy::Font** mNewFont;
  /* 0x0008 */ public: Sexy::Color mNewColor;
  /* 0x0018 */ public: int mLineSpacingOffset;
  /* 0x001c */ public: unsigned int mFormatFlags;

  public: TodStringListFormat();
};

#endif
