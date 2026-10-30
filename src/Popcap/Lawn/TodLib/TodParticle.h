#ifndef __TODLIB_TODPARTICLE_H__
#define __TODLIB_TODPARTICLE_H__

#include "SexyAppFramework/Image.h"

enum EmitterType
{
    EMITTER_CIRCLE = 0,
    EMITTER_BOX,
    EMITTER_BOX_PATH,
    EMITTER_CIRCLE_PATH,
    EMITTER_CIRCLE_EVEN_SPACING,
};

enum TodCurves
{
    CURVE_CONSTANT = 0,
    CURVE_LINEAR,
    CURVE_EASE_IN,
    CURVE_EASE_OUT,
    CURVE_EASE_IN_OUT,
    CURVE_EASE_IN_OUT_WEAK,
    CURVE_FAST_IN_OUT,
    CURVE_FAST_IN_OUT_WEAK,
    CURVE_WEAK_FAST_IN_OUT,
    CURVE_BOUNCE,
    CURVE_BOUNCE_FAST_MIDDLE,
    CURVE_BOUNCE_SLOW_MIDDLE,
    CURVE_SIN_WAVE,
    CURVE_EASE_SIN_WAVE,
};

class FloatParameterTrackNode
{
  public:
    float mTime;             // 0x0
    float mLowValue;         // 0x4
    float mHighValue;        // 0x8
    TodCurves mCurveType;    // 0xC
    TodCurves mDistribution; // 0x10
};

class FloatParameterTrack
{
  public:
    FloatParameterTrackNode *mNodes; // 0x0
    int mCountNodes;                 // 0x4
};

enum ParticleFieldType
{
    FIELD_INVALID = 0,
    FIELD_FRICTION,
    FIELD_ACCELERATION,
    FIELD_ATTRACTOR,
    FIELD_MAX_VELOCITY,
    FIELD_VELOCITY,
    FIELD_POSITION,
    FIELD_SYSTEM_POSITION,
    FIELD_GROUND_CONSTRAINT,
    FIELD_SHAKE,
    FIELD_CIRCLE,
    FIELD_AWAY,
    PARTICLE_FIELD_COUNT,
};

class ParticleField
{
  public:
    ParticleField();
    ParticleFieldType mFieldType; // 0x0
    FloatParameterTrack mX;       // 0x4
    FloatParameterTrack mY;       // 0xC
};

class TodEmitterDefinition
{
  public:
    TodEmitterDefinition();
    ~TodEmitterDefinition();
    Sexy::Image *mImage;                     // 0x0
    int mImageCol;                           // 0x4
    int mImageRow;                           // 0x8
    int mImageFrames;                        // 0xC
    int mAnimated;                           // 0x10
    int mParticleFlags;                      // 0x14
    EmitterType mEmitterType;                // 0x18
    char *mName;                             // 0x1C
    char *mOnDuration;                       // 0x20
    FloatParameterTrack mSystemDuration;     // 0x24
    FloatParameterTrack mCrossFadeDuration;  // 0x2C
    FloatParameterTrack mSpawnRate;          // 0x34
    FloatParameterTrack mSpawnMinActive;     // 0x3C
    FloatParameterTrack mSpawnMaxActive;     // 0x44
    FloatParameterTrack mSpawnMaxLaunched;   // 0x4C
    FloatParameterTrack mEmitterRadius;      // 0x54
    FloatParameterTrack mEmitterOffsetX;     // 0x5C
    FloatParameterTrack mEmitterOffsetY;     // 0x64
    FloatParameterTrack mEmitterBoxX;        // 0x6C
    FloatParameterTrack mEmitterBoxY;        // 0x74
    FloatParameterTrack mEmitterSkewX;       // 0x7C
    FloatParameterTrack mEmitterSkewY;       // 0x84
    FloatParameterTrack mEmitterPath;        // 0x8C
    FloatParameterTrack mParticleDuration;   // 0x94
    FloatParameterTrack mLaunchSpeed;        // 0x9C
    FloatParameterTrack mLaunchAngle;        // 0xA4
    FloatParameterTrack mSystemRed;          // 0xAC
    FloatParameterTrack mSystemGreen;        // 0xB4
    FloatParameterTrack mSystemBlue;         // 0xBC
    FloatParameterTrack mSystemAlpha;        // 0xC4
    FloatParameterTrack mSystemBrightness;   // 0xCC
    ParticleField *mParticleFields;          // 0xD4
    int mParticleFieldCount;                 // 0xD8
    ParticleField *mSystemFields;            // 0xDC
    int mSystemFieldCount;                   // 0xE0
    FloatParameterTrack mParticleRed;        // 0xE4
    FloatParameterTrack mParticleGreen;      // 0xEC
    FloatParameterTrack mParticleBlue;       // 0xF4
    FloatParameterTrack mParticleAlpha;      // 0xFC
    FloatParameterTrack mParticleBrightness; // 0x104
    FloatParameterTrack mParticleSpinAngle;  // 0x10C
    FloatParameterTrack mParticleSpinSpeed;  // 0x114
    FloatParameterTrack mParticleScale;      // 0x11C
    FloatParameterTrack mParticleStretch;    // 0x124
    FloatParameterTrack mCollisionReflect;   // 0x12C
    FloatParameterTrack mCollisionSpin;      // 0x134
    FloatParameterTrack mClipTop;            // 0x13C
    FloatParameterTrack mClipBottom;         // 0x144
    FloatParameterTrack mClipLeft;           // 0x14C
    FloatParameterTrack mClipRight;          // 0x154
    FloatParameterTrack mAnimationRate;      // 0x15C
};

class TodParticleDefinition
{
  public:
    TodParticleDefinition();
    TodEmitterDefinition *mEmitterDefs; // 0x0
    int mEmitterDefCount;               // 0x4
};

#endif
