#ifndef __CURSORPREVIEW_H__
#define __CURSORPREVIEW_H__

#include "GameObject.h"

class CursorPreview : public GameObject
{   /* Size=0x2c */
    /* 0x0000: fields for GameObject */
  public:
    /* 0x0024 */ int mGridX;
    /* 0x0028 */ int mGridY;

  public:
    CursorPreview();

    void Update();
    void Draw(Sexy::Graphics *);
};

#endif
