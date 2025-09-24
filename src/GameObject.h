#pragma once

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "SexyAppFramework/Graphics.h"

class Board;
class LawnApp;

#ifndef E_REANIM_LOOP_TYPE
#define E_REANIM_LOOP_TYPE
enum ReanimLoopType : int
{
    REANIM_LOOP = 0x0000,
    REANIM_LOOP_FULL_LAST_FRAME = 0x0001,
    REANIM_PLAY_ONCE = 0x0002,
    REANIM_PLAY_ONCE_AND_HOLD = 0x0003,
    REANIM_PLAY_ONCE_FULL_LAST_FRAME = 0x0004,
    REANIM_PLAY_ONCE_FULL_LAST_FRAME_AND_HOLD = 0x0005,
};
#endif

#ifndef E_GAME_OBJECT_TYPE
#define E_GAME_OBJECT_TYPE
enum GameObjectType : int
{
    OBJECT_TYPE_NONE = 0x0000,
    OBJECT_TYPE_PLANT = 0x0001,
    OBJECT_TYPE_PROJECTILE = 0x0002,
    OBJECT_TYPE_COIN = 0x0003,
    OBJECT_TYPE_SEEDPACKET = 0x0004,
    OBJECT_TYPE_SHOVEL = 0x0005,
    OBJECT_TYPE_WATERING_CAN = 0x0006,
    OBJECT_TYPE_FERTILIZER = 0x0007,
    OBJECT_TYPE_BUG_SPRAY = 0x0008,
    OBJECT_TYPE_PHONOGRAPH = 0x0009,
    OBJECT_TYPE_CHOCOLATE = 0x000a,
    OBJECT_TYPE_GLOVE = 0x000b,
    OBJECT_TYPE_MONEY_SIGN = 0x000c,
    OBJECT_TYPE_WHEELBARROW = 0x000d,
    OBJECT_TYPE_TREE_FOOD = 0x000e,
    OBJECT_TYPE_NEXT_GARDEN = 0x000f,
    OBJECT_TYPE_MENU_BUTTON = 0x0010,
    OBJECT_TYPE_STORE_BUTTON = 0x0011,
    OBJECT_TYPE_SLOT_MACHINE_HANDLE = 0x0012,
    OBJECT_TYPE_SCARY_POT = 0x0013,
    OBJECT_TYPE_STINKY = 0x0014,
    OBJECT_TYPE_TREE_OF_WISDOM = 0x0015,
};
#endif

class HitResult
{ /* Size=0x8 */
  /* 0x0000 */ public:
    void *mObject;
  /* 0x0004 */ public:
    GameObjectType mObjectType;
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