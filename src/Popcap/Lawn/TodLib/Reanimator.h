#ifndef __TODLIB_REANIMATOR_H__
#define __TODLIB_REANIMATOR_H__

#include <list>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "SexyAppFramework/Font.h"
#include "SexyAppFramework/Image.h"
#include "SexyAppFramework/MemoryImage.h"
#include "SexyAppFramework/SexyMatrix.h"
#include "TodLib/Attachment.h"
#include "TodLib/ReanimAtlas.h"

#include "Enums.h"

class AttachEffect;
class ReanimAtlas;

class ReanimatorTransform
{ /* Size=0x2c */
  public:
    /* 0x0000 */ float mTransX;
    /* 0x0004 */ float mTransY;
    /* 0x0008 */ float mSkewX;
    /* 0x000c */ float mSkewY;
    /* 0x0010 */ float mScaleX;
    /* 0x0014 */ float mScaleY;
    /* 0x0018 */ float mFrame;
    /* 0x001c */ float mAlpha;
    /* 0x0020 */ Sexy::Image *mImage;
    /* 0x0024 */ Sexy::Font *mFont;
    /* 0x0028 */ char *mText;

  public:
    ReanimatorTransform();
};

class ReanimatorTrack
{ /* Size=0xc */
  public:
    /* 0x0000 */ char *mName;
    /* 0x0004 */ ReanimatorTransform *mTransforms;
    /* 0x0008 */ int mTransformCount;

  public:
    ReanimatorTrack();
};

class ReanimatorTrackInstance
{ /* Size=0x60 */
  public:
    /* 0x0000 */ int mBlendCounter;
    /* 0x0004 */ int mBlendTime;
    /* 0x0008 */ ReanimatorTransform mBlendTransform;
    /* 0x0034 */ float mShakeOverride;
    /* 0x0038 */ float mShakeX;
    /* 0x003c */ float mShakeY;
    /* 0x0040 */ AttachmentID mAttachmentID;
    /* 0x0044 */ Sexy::Image *mImageOverride;
    /* 0x0048 */ int mRenderGroup;
    /* 0x004c */ Sexy::Color mTrackColor;
    /* 0x005c */ bool mIgnoreClipRect;
    /* 0x005d */ bool mTruncateDisappearingFrames;

  public:
    ReanimatorTrackInstance();
};

class ReanimatorDefinition
{ /* Size=0x10 */
  public:
    /* 0x0000 */ ReanimatorTrack *mTracks;
    /* 0x0004 */ int mTrackCount;
    /* 0x0008 */ float mFPS;
    /* 0x000c */ ReanimAtlas *mReanimAtlas;

  public:
    ReanimatorDefinition();
};

class ReanimationHolder;

class Reanimation
{ /* Size=0x9c */
  public:
    /* 0x0000 */ ReanimationType mReanimationType;
    /* 0x0004 */ float mAnimTime;
    /* 0x0008 */ float mAnimRate;
    /* 0x000c */ ReanimatorDefinition *mDefinition;
    /* 0x0010 */ ReanimLoopType mLoopType;
    /* 0x0014 */ bool mDead;
    /* 0x0018 */ int mFrameStart;
    /* 0x001c */ int mFrameCount;
    /* 0x0020 */ int mFrameBasePose;
    /* 0x0024 */ Sexy::SexyTransform2D mOverlayMatrix;
    /* 0x0048 */ Sexy::Color mColorOverride;
    /* 0x0058 */ ReanimatorTrackInstance *mTrackInstances;
    /* 0x005c */ int mLoopCount;
    /* 0x0060 */ ReanimationHolder *mReanimationHolder;
    /* 0x0064 */ bool mIsAttachment;
    /* 0x0068 */ int mRenderOrder;
    /* 0x006c */ Sexy::Color mExtraAdditiveColor;
    /* 0x007c */ bool mEnableExtraAdditiveDraw;
    /* 0x0080 */ Sexy::Color mExtraOverlayColor;
    /* 0x0090 */ bool mEnableExtraOverlayDraw;
    /* 0x0094 */ float mLastFrameTime;
    /* 0x0098 */ FilterEffect mFilterEffect;

  public:
    Reanimation();
    ~Reanimation();
    void ReanimationInitialize(float, float, ReanimatorDefinition *);
    void ReanimationInitializeType(float, float, ReanimationType);
    void ReanimationDie();
    void Update();
    void Draw(Sexy::Graphics *);
    void DrawRenderGroup(Sexy::Graphics *, int);
    bool DrawTrack(Sexy::Graphics *, int, int, /*TodTriangleGroup * */ void *);
    void GetCurrentTransform(int, ReanimatorTransform *);
    void GetTransformAtTime(int, ReanimatorTransform *, /*ReanimatorFrameTime * */ void *);
    void GetFrameTime(/*ReanimatorFrameTime * */ void *);
    int FindTrackIndex(const char *);
    void AttachToAnotherReanimation(Reanimation *, const char *);
    void GetAttachmentOverlayMatrix(int, Sexy::SexyTransform2D &);
    void SetFramesForLayer(const char *);
    bool TrackExists(const char *);
    void StartBlend(int);
    void SetShakeOverride(const char *, float);
    void SetPosition(float, float);
    void OverrideScale(float, float);
    float GetTrackVelocity(const char *);
    void SetImageOverride(const char *, Sexy::Image *);
    Sexy::Image *GetImageOverride(const char *);
    void ShowOnlyTrack(const char *);
    void GetTrackMatrix(int, Sexy::SexyTransform2D &);
    void AssignRenderGroupToTrack(const char *, int);
    void AssignRenderGroupToPrefix(const char *, int);
    void PropogateColorToAttachments();
    bool ShouldTriggerTimedEvent(float);
    void TodTriangleGroupDraw(Sexy::Graphics *, /*TodTriangleGroup * */ void *);
    Sexy::Image *GetCurrentTrackImage(const char *);
    /*AttachEffect * */ void *AttachParticleToTrack(const char *, /*TodParticleSystem * */ void *,
                                                    float, float);
    void GetTrackBasePoseMatrix(int, Sexy::SexyTransform2D &);
    bool IsTrackShowing(const char *);
    void SetTruncateDisappearingFrames(const char *, bool);
    void PlayReanim(const char *, ReanimLoopType, int, float);
    void ReanimationDelete();
    ReanimatorTrackInstance *GetTrackInstanceByName(const char *);
    void GetFramesForLayer(const char *, int &, int &);
    void UpdateAttacherTrack(int);
    void AttacherSynchWalkSpeed(int, Reanimation *, const /*AttacherInfo & */ void *);
    bool IsAnimPlaying(const char *);
    void SetBasePoseFromAnim(const char *);
    void ReanimBltMatrix(Sexy::Graphics *, Sexy::Image *, const Sexy::SexyMatrix3 &,
                         const Sexy::TRect<int> &, const Sexy::Color &, int,
                         const Sexy::TRect<int> &);
    // void *__vecDelDtor(unsigned int);
    static void MatrixFromTransform(ReanimatorTransform &, Sexy::SexyMatrix3 &);
    static void ParseAttacherTrack(const ReanimatorTransform &, /*AttacherInfo & */ void *);
};

class ReanimationHolder
{ /* Size=0x1c */
  public:
    /* 0x0000 */ // DataArray<Reanimation> mReanimations;
    char mReanimations[0x1c];

  public:
    ReanimationHolder();
    ~ReanimationHolder();
    void InitializeHolder();
    void DisposeHolder();
    Reanimation *AllocReanimation(float, float, int, ReanimationType);
};

void ReanimatorEnsureDefinitionLoaded(ReanimationType theReanimType, bool theIsPreloading);

#endif
