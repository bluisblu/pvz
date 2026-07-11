#include "GridItem.h"

GridItem::GridItem()
{
    Sexy::SexyAppBase *v2; // edx
    Board *v3;             // ecx

    // ew
    mApp = (LawnApp *)Sexy::gSexyAppBase;
    v2 = (Sexy::SexyAppBase *)mApp;
    v3 = *(Board **)&v2[1].mAdd8BitMaxTable[11];

    mPosX = 0.0;
    mPosY = 0.0;
    mBoard = v3;
    mGoalX = 0.0;
    mGoalY = 0.0;
    mGridItemType = GRIDITEM_NONE;
    mGridX = 0;
    mGridY = 0;
    mGridItemCounter = 0;
    mRenderOrder = 0;
    mDead = 0;
    mGridItemReanimID = REANIMATIONID_NULL;
    mGridItemParticleID = PARTICLESYSTEMID_NULL;
    mZombieType = ZOMBIE_INVALID;
    mSeedType = SEED_NONE;
    mScaryPotType = SCARYPOT_NONE;
    mHighlighted = 0;
    mTransparentCounter = 0;
    mSunCount = 0;
    mMotionTrailCount = 0;
}

void GridItem::UpdateRake()
{
    Reanimation *v3; // eax
    Zombie *aZombie;  // eax

    if (mGridItemState == GRIDITEM_STATE_RAKE_ATTRACTING || mGridItemState == GRIDITEM_STATE_RAKE_WAITING)
    {
        if (RakeFindZombie())
        {
            mApp->ReanimationGet(mGridItemReanimID)->mAnimRate = 20.0;

            mGridItemCounter = 200;
            mGridItemState = GRIDITEM_STATE_RAKE_TRIGGERED;
            mApp->PlayFoley(FOLEY_SWING);
        }
    }
    else if (mGridItemState == GRIDITEM_STATE_RAKE_TRIGGERED)
    {
        v3 = mApp->ReanimationGet(mGridItemReanimID);
        if (v3->ShouldTriggerTimedEvent(0.80000001))
        {
            aZombie = RakeFindZombie();
            if (aZombie)
            {
                aZombie->TakeDamage(1800, 0);
                mApp->PlayFoley(FOLEY_BONK);
            }
        }
        mGridItemCounter--;
        if (mGridItemCounter == 0)
        {
            GridItemDie();
        }
    }
}