#pragma once

#ifndef __ATTACHMENT_H__
#define __ATTACHMENT_H__

#include "SexyAppFramework/Color.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/SexyMatrix.h"

#include "Reanimator.h"

#ifndef E_ATTACHMENT_ID
#define E_ATTACHMENT_ID
enum AttachmentID : int
{
    ATTACHMENTID_NULL = 0x0000,
};
#endif

#ifndef E_EFFECT_TYPE
#define E_EFFECT_TYPE
enum EffectType : int
{
    EFFECT_PARTICLE = 0x0000,
    EFFECT_TRAIL = 0x0001,
    EFFECT_REANIM = 0x0002,
    EFFECT_ATTACHMENT = 0x0003,
    EFFECT_OTHER = 0x0004,
};
#endif

class AttachEffect
{ /* Size=0x30 */
  /* 0x0000 */ public:
    unsigned int mEffectID;
  /* 0x0004 */ public:
    EffectType mEffectType;
  /* 0x0008 */ public:
    Sexy::SexyTransform2D mOffset;
  /* 0x002c */ public:
    bool mDontDrawIfParentHidden;
  /* 0x002d */ public:
    bool mDontPropogateColor;

  public:
    AttachEffect();
};

class Attachment
{ /* Size=0x308 */
  /* 0x0000 */ public:
    AttachEffect mEffectArray[16];
  /* 0x0300 */ public:
    int mNumEffects;
  /* 0x0304 */ public:
    bool mDead;

  public:
    Attachment();

  public:
    ~Attachment();

  public:
    void Update();

  public:
    void SetPosition(const Sexy::SexyVector2 &);

  public:
    void SetMatrix(const Sexy::SexyTransform2D &);

  public:
    void OverrideColor(const Sexy::Color &);

  public:
    void OverrideScale(float);

  public:
    void Draw(Sexy::Graphics *, bool);

  public:
    void AttachmentDie();

  public:
    void Detach();

  public:
    void CrossFade(const char *);

  public:
    void PropogateColor(const Sexy::Color &, bool, const Sexy::Color &, bool, const Sexy::Color &);

  public:
    // void *__vecDelDtor(unsigned int);
};

#endif