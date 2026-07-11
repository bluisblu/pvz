#pragma once

#ifndef __TODLIB_REANIMATLAS_H__
#define __TODLIB_REANIMATLAS_H__

#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/MemoryImage.h"

#include "TodLib/Reanimator.h"

class ReanimatorDefinition;

class ReanimAtlasImage
{ /* Size=0x14 */
  public:
    /* 0x0000 */ int mX;
    /* 0x0004 */ int mY;
    /* 0x0008 */ int mWidth;
    /* 0x000c */ int mHeight;
    /* 0x0010 */ Sexy::Image *mOriginalImage;

  public:
    ReanimAtlasImage();
};

class ReanimAtlas
{ /* Size=0x508 */
  public:
    /* 0x0000 */ ReanimAtlasImage mImageArray[64];
    /* 0x0500 */ int mImageCount;
    /* 0x0504 */ Sexy::MemoryImage *mMemoryImage;

  public:
    ReanimAtlas();
    void ReanimAtlasCreate(ReanimatorDefinition *);
    void ReanimAtlasDispose();
    void AddImage(Sexy::Image *);
    int FindImage(Sexy::Image *);
    bool ImageFits(int, const Sexy::TRect<int> &, int);
    bool ImageFindPlaceOnSide(ReanimAtlasImage *, int, int, bool);
    bool ImageFindPlace(ReanimAtlasImage *, int, int);
    bool PlaceAtlasImage(ReanimAtlasImage *, int, int);
    int PickAtlasWidth();
    void ArrangeImages(int &, int &);
    ReanimAtlasImage *GetEncodedReanimAtlas(Sexy::Image *);
};

#endif
