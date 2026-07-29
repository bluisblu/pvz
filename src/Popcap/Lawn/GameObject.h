#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "SexyAppFramework/Graphics.h"

#include "Enums.h"

class Board;
class LawnApp;

class HitResult
{ /* Size=0x8 */
  public:
    /* 0x0000 */ void *mObject;
    /* 0x0004 */ GameObjectType mObjectType;
};

class GameObject
{ /* Size=0x24 */
  public:
    /* 0x0000 */ LawnApp *mApp;
    /* 0x0004 */ Board *mBoard;
    /* 0x0008 */ int mX;
    /* 0x000c */ int mY;
    /* 0x0010 */ int mWidth;
    /* 0x0014 */ int mHeight;
    /* 0x0018 */ bool mVisible;
    // char pad_0x19[3];
    /* 0x001c */ int mRow;
    /* 0x0020 */ int mRenderOrder;

  public:
    GameObject();
    bool BeginDraw(Sexy::Graphics *);
    void EndDraw(Sexy::Graphics *);
    void MakeParentGraphicsFrame(Sexy::Graphics *); // missing in object
};

#endif // __GAMEOBJECT_H__
