#include "SexyAppFramework/Color.h"

#include "Reanimator.h"

ReanimatorTransform::ReanimatorTransform()
{
    mTransX = -10000.0;
    mTransY = -10000.0;
    mFont = 0x0;
    mSkewX = -10000.0;
    mImage = 0x0;
    mSkewY = -10000.0;
    mText = "";
    mScaleX = -10000.0;
    mScaleY = -10000.0;
    mFrame = -10000.0;
    mAlpha = -10000.0;
}

ReanimatorDefinition::ReanimatorDefinition()
{
    mFPS = 12.0;
    mTracks = 0x0;
    mTrackCount = 0;
    mReanimAtlas = 0x0;
}

ReanimatorTrackInstance::ReanimatorTrackInstance()
{
    mBlendTransform.mTransX = -10000.0;
    mBlendTransform.mTransY = -10000.0;
    mBlendTransform.mSkewX = -10000.0;
    mBlendTransform.mSkewY = -10000.0;
    mBlendTransform.mScaleX = -10000.0;
    mBlendTransform.mFont = 0x0;
    mBlendTransform.mScaleY = -10000.0;
    mBlendTransform.mImage = 0x0;
    mBlendTransform.mFrame = -10000.0;
    mBlendTransform.mText = "";
    mBlendTransform.mAlpha = -10000.0;
    mBlendCounter = 0;
    mShakeOverride = 0.0;
    Sexy::Color(mTrackColor);
    mBlendTime = 0;
    mShakeX = 0.0;
    mAttachmentID = ATTACHMENTID_NULL;
    mRenderGroup = 0;
    mShakeY = 0.0;
    mIgnoreClipRect = false;
    mImageOverride = 0x0;
    mTruncateDisappearingFrames = true;
    mTrackColor.mRed = Sexy::Color::White.mRed;
    mTrackColor.mGreen = Sexy::Color::White.mGreen;
    mTrackColor.mBlue = Sexy::Color::White.mBlue;
    mTrackColor.mAlpha = Sexy::Color::White.mAlpha;
}

Reanimation::Reanimation()
{
    Sexy::SexyTransform2D(mOverlayMatrix);
    Sexy::Color(mColorOverride);
    Sexy::Color(mExtraAdditiveColor);
    Sexy::Color(mExtraOverlayColor);
    mAnimTime = 0.0;
    mAnimRate = 12.0;
    mDefinition = 0x0;
    mLoopType = REANIM_PLAY_ONCE;
    mLastFrameTime = -1.0;
    mDead = false;
    mFrameStart = 0;
    mFrameCount = 0;
    mFrameBasePose = -1;
    mOverlayMatrix.LoadIdentity();
    this->mColorOverride.mRed = Sexy::Color::White.mRed;
    this->mColorOverride.mGreen = Sexy::Color::White.mGreen;
    this->mColorOverride.mBlue = Sexy::Color::White.mBlue;
    this->mColorOverride.mAlpha = Sexy::Color::White.mAlpha;
    this->mExtraAdditiveColor.mRed = Sexy::Color::White.mRed;
    this->mExtraAdditiveColor.mGreen = Sexy::Color::White.mGreen;
    this->mExtraAdditiveColor.mBlue = Sexy::Color::White.mBlue;
    this->mExtraAdditiveColor.mAlpha = Sexy::Color::White.mAlpha;
    mEnableExtraAdditiveDraw = false;
    this->mExtraOverlayColor.mRed = Sexy::Color::White.mRed;
    this->mExtraOverlayColor.mGreen = Sexy::Color::White.mGreen;
    mLoopCount = 0;
    mExtraOverlayColor.mBlue = Sexy::Color::White.mBlue;
    this->mExtraOverlayColor.mAlpha = Sexy::Color::White.mAlpha;
    mIsAttachment = false;
    mRenderOrder = 0;
    mReanimationHolder = 0x0;
    mTrackInstances = 0x0;
    mEnableExtraOverlayDraw = false;
    mFilterEffect = FILTER_EFFECT_NONE;
    mReanimationType = REANIM_NONE;
}

void Reanimation::AttachToAnotherReanimation(Reanimation *param_1, const char *param_2)
{
    int iVar1;

    if (param_1->mDefinition->mTrackCount != 0)
    {
        if (param_1->mFrameBasePose == -1)
        {
            param_1->mFrameBasePose = param_1->mFrameStart;
        }
        iVar1 = param_1->FindTrackIndex(param_2);
        AttachReanim(&param_1->mTrackInstances[iVar1].mAttachmentID, this, 0.0, 0.0);
    }
    return;
}