#ifndef __TODLIB_TRAIL_H__
#define __TODLIB_TRAIL_H__

#include "TodParticle.h"

class TrailDefinition
{
  public:
    TrailDefinition();
    ~TrailDefinition();
    Sexy::Image *mImage;                  // 0x0
    int mMaxPoints;                       // 0x4
    float mMinPointDistance;              // 0x8
    int mTrailFlags;                      // 0xC
    FloatParameterTrack mTrailDuration;   // 0x10
    FloatParameterTrack mWidthOverLength; // 0x18
    FloatParameterTrack mWidthOverTime;   // 0x20
    FloatParameterTrack mAlphaOverLength; // 0x28
    FloatParameterTrack mAlphaOverTime;   // 0x30
};

#endif
