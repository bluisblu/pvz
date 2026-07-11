#pragma once

#include <cstdio>
#ifndef __TODLIB_ATTACHMENT_H__
#define __TODLIB_ATTACHMENT_H__

#include "SexyAppFramework/Color.h"
#include "SexyAppFramework/Graphics.h"
#include "SexyAppFramework/SexyMatrix.h"

#include "EffectSystem.h"
#include "Reanimator.h"

class Reanimation;

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
    EFFECT_PARTICLE   = 0x0000,
    EFFECT_TRAIL      = 0x0001,
    EFFECT_REANIM     = 0x0002,
    EFFECT_ATTACHMENT = 0x0003,
    EFFECT_OTHER      = 0x0004,
};
#endif

class AttachEffect
{ /* Size=0x30 */
    /* 0x0000 */ unsigned int mEffectID;
    /* 0x0004 */ EffectType mEffectType;
    /* 0x0008 */ Sexy::SexyTransform2D mOffset;
    /* 0x002c */ bool mDontDrawIfParentHidden;
    /* 0x002d */ bool mDontPropogateColor;
    AttachEffect();
};

class Attachment
{ /* Size=0x308 */
  public:
    /* 0x0000 */ AttachEffect mEffectArray[16];
    /* 0x0300 */ int mNumEffects;
    /* 0x0304 */ bool mDead;

  public:
    Attachment();
    ~Attachment();
    void Update();
    void SetPosition(const Sexy::SexyVector2 &);
    void SetMatrix(const Sexy::SexyTransform2D &);
    void OverrideColor(const Sexy::Color &);
    void OverrideScale(float);
    void Draw(Sexy::Graphics *, bool);
    void AttachmentDie();
    void Detach();
    void CrossFade(const char *);
    void PropogateColor(const Sexy::Color &, bool, const Sexy::Color &, bool, const Sexy::Color &);
    // void *__vecDelDtor(unsigned int);
};

class AttachmentHolder
{         /* Size=0x1c */
  public: /* DataArray<Attachment> */
    void *mAttachments;

  public:
    AttachmentHolder();
    ~AttachmentHolder();
    void InitializeHolder();
    void DisposeHolder();
    Attachment *AllocAttachment();
};

void AttachmentDie(AttachmentID &theAttachmentID);

AttachEffect *AttachReanim(AttachmentID &theAttachmentID, Reanimation *theReanimation,
                           float theOffsetX, float theOffsetY)
{
    return NULL;
}

#endif
