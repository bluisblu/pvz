#ifndef __REANIMATLAS_H__
#define __REANIMATLAS_H__

#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/MemoryImage.h"

#include "Reanimator.h"

class ReanimatorDefinition;

class ReanimAtlasImage
{ /* Size=0x14 */
  /* 0x0000 */ public:
    int mX;
  /* 0x0004 */ public:
    int mY;
  /* 0x0008 */ public:
    int mWidth;
  /* 0x000c */ public:
    int mHeight;
  /* 0x0010 */ public:
    Sexy::Image *mOriginalImage;

  public:
    ReanimAtlasImage();
};

class ReanimAtlas
{ /* Size=0x508 */
  /* 0x0000 */ public:
    ReanimAtlasImage mImageArray[64];
  /* 0x0500 */ public:
    int mImageCount;
  /* 0x0504 */ public:
    Sexy::MemoryImage *mMemoryImage;

  public:
    ReanimAtlas();

  public:
    void ReanimAtlasCreate(ReanimatorDefinition *);

  public:
    void ReanimAtlasDispose();

  public:
    void AddImage(Sexy::Image *);

  public:
    int FindImage(Sexy::Image *);

  public:
    bool ImageFits(int, const Sexy::TRect<int> &, int);

  public:
    bool ImageFindPlaceOnSide(ReanimAtlasImage *, int, int, bool);

  public:
    bool ImageFindPlace(ReanimAtlasImage *, int, int);

  public:
    bool PlaceAtlasImage(ReanimAtlasImage *, int, int);

  public:
    int PickAtlasWidth();

  public:
    void ArrangeImages(int &, int &);

  public:
    ReanimAtlasImage *GetEncodedReanimAtlas(Sexy::Image *);
};

#endif