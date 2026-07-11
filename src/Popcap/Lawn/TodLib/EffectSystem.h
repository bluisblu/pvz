#ifndef __EFFECTSYSTEM_H__
#define __EFFECTSYSTEM_H__

#include "TodLib/Attachment.h"
#include "TodLib/Reanimator.h"
#include "TodLib/TodParticle.h"
#include "TodLib/Trail.h"

class EffectSystem
{ /* Size=0x10 */
  /* 0x0000 */ public:
    /* TodParticleHolder * */ void *mParticleHolder;
    /* 0x0004 */
    /* TrailHolder * */ void *mTrailHolder;
    /* 0x0008 */
    class ReanimationHolder *mReanimationHolder;
    /* 0x000c */
    class AttachmentHolder *mAttachmentHolder;

  public:
    EffectSystem();
    ~EffectSystem();
    void EffectSystemInitialize();
    void EffectSystemDispose();
    void EffectSystemFreeAll();
    void ProcessDeleteQueue();
    void Update();
};

EffectSystem *gEffectSystem;

#endif
