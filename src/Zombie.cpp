#include "TodLib/Attachment.h"
#include "TodLib/Reanimator.h"

#include "Zombie.h"

void Zombie::SetupDoorArms(Reanimation *aReanim, bool theShow)
{
    int aArmGroup = RENDER_GROUP_NORMAL;
    int aDoorGroup = RENDER_GROUP_HIDDEN;
    if (theShow)
    {
        // Assembly says aArmGroup = ebx (aDoorGroup) instead of -1
        // probably a compiler flag issue
        aArmGroup = RENDER_GROUP_HIDDEN;
        aDoorGroup = RENDER_GROUP_NORMAL;
    }

    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_hand", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_lower", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_upper", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("anim_innerarm", aArmGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_screendoor", aDoorGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_innerarm_screendoor", aDoorGroup);
    aReanim->AssignRenderGroupToPrefix("Zombie_innerarm_screendoor_hand", aDoorGroup);
}

void Zombie::SetupReanimLayers(Reanimation *aReanim, ZombieType theZombieType)
{
    aReanim->AssignRenderGroupToPrefix("anim_cone", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("anim_bucket", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("anim_screendoor", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_flag", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_duckytube", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("anim_tongue", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_mustache", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_hand", RENDER_GROUP_NORMAL);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_lower", RENDER_GROUP_NORMAL);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_upper", RENDER_GROUP_NORMAL);
    aReanim->AssignRenderGroupToPrefix("anim_innerarm", RENDER_GROUP_NORMAL);
    aReanim->AssignRenderGroupToPrefix("Zombie_outerarm_screendoor", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_innerarm_screendoor", RENDER_GROUP_HIDDEN);
    aReanim->AssignRenderGroupToPrefix("Zombie_innerarm_screendoor_hand", RENDER_GROUP_HIDDEN);

    // Yes, if-else matches better than a switch statement here
    if (theZombieType == ZOMBIE_TRAFFIC_CONE)
    {
        aReanim->AssignRenderGroupToPrefix("anim_cone", RENDER_GROUP_NORMAL);
        aReanim->AssignRenderGroupToPrefix("anim_hair", RENDER_GROUP_HIDDEN);
    }
    else if (theZombieType == ZOMBIE_PAIL)
    {
        aReanim->AssignRenderGroupToPrefix("anim_bucket", RENDER_GROUP_NORMAL);
        aReanim->AssignRenderGroupToPrefix("anim_hair", RENDER_GROUP_HIDDEN);
    }
    else if (theZombieType == ZOMBIE_DOOR)
    {
        Zombie::SetupDoorArms(aReanim, 1);
    }
    else if (theZombieType == ZOMBIE_NEWSPAPER)
    {
        aReanim->AssignRenderGroupToPrefix("Zombie_paper_paper", RENDER_GROUP_HIDDEN);
    }
    else if (theZombieType == ZOMBIE_FLAG)
    {
        aReanim->AssignRenderGroupToPrefix("anim_innerarm", RENDER_GROUP_HIDDEN);
        aReanim->AssignRenderGroupToTrack("Zombie_flaghand", RENDER_GROUP_NORMAL);
        aReanim->AssignRenderGroupToTrack("Zombie_innerarm_screendoor", RENDER_GROUP_NORMAL);
        aReanim->AssignRenderGroupToTrack("Zombie_flag", RENDER_GROUP_NORMAL);
    }
    else if (theZombieType == ZOMBIE_DUCKY_TUBE)
    {
        aReanim->AssignRenderGroupToPrefix("Zombie_duckytube", RENDER_GROUP_NORMAL);
    }
}

/*
#   17176 | S_GPROC32 [size = 68] `Zombie::ReanimIgnoreClipRect`
#   17244 | S_FRAMEPROC [size = 32]
#   17276 | S_REGISTER [size = 16] `this`
#   17292 | S_BPREL32 [size = 28] `theTrackName`
#   17320 | S_BPREL32 [size = 32] `theIgnoreClipRect`
#   17352 | S_BPREL32 [size = 16] `i`
#   17368 | S_END [size = 4]
*/

void Zombie::ReanimIgnoreClipRect(const char *theTrackName, bool theIgnoreClipRect)
{
    Reanimation *v3;                   // eax
    Reanimation *v4;                   // edi
    int v5;                            // ebx
    ReanimatorDefinition *mDefinition; // eax
    int v7;                            // ebp
    ReanimatorTrackInstance *v8;       // esi
    int v9;                            // [esp+4h] [ebp-4h]

    v3 = mApp->ReanimationTryToGet(mBodyReanimID);
    v4 = v3;
    v5 = 0;
    if (v3)
    {
        mDefinition = v3->mDefinition;
        v9 = 0;
        if (mDefinition->mTrackCount > 0)
        {
            v7 = 0;
            do
            {
                v8 = &v4->mTrackInstances[v5];
                if (!_stricmp(mDefinition->mTracks[v7].mName, theTrackName))
                    v8->mIgnoreClipRect = theIgnoreClipRect;
                mDefinition = v4->mDefinition;
                ++v7;
                ++v5;
                ++v9;
            } while (v9 < mDefinition->mTrackCount);
        }
    }
}

bool Zombie::IsBouncingPogo()
{
    if (mZombiePhase >= PHASE_POGO_BOUNCING && mZombiePhase <= PHASE_POGO_FORWARD_BOUNCE_7)
        return true;

    return false;
}

Plant *Zombie::FindCatapultTarget()
{
    Plant *aTarget = NULL;

    Plant *aPlant = NULL;
    while (mBoard->IteratePlants(aPlant))
    {
        if (mRow == aPlant->mRow && mX >= aPlant->mX + 100 && !aPlant->NotOnGround() && !aPlant->IsSpiky())
        {
            if (aTarget == NULL || aPlant->mPlantCol < aTarget->mPlantCol)
            {
                aTarget =
                    mBoard->GetTopPlantAt(aPlant->mPlantCol, aPlant->mRow, PlantPriority::TOPPLANT_CATAPULT_ORDER);
            }
        }
    }

    return aTarget;
}

// Extra IteratePlants call for some reason
bool Zombie::IsTanglekelpTarget()
{
    for (Plant *thePlant = NULL; mBoard->IteratePlants(thePlant);)
    {
        if (thePlant->mState == STATE_TANGLEKELP_GRABBING)
        {
            ZombieID ID = mBoard->ZombieGetID(this);
            if (thePlant->mTargetZombieID == ID)
                return true;
        }
    }
    return false;
}

bool Zombie::NeedsMoreBackupDancers()
{
    for (int i = 0; i < 4; i++)
    {
        if (!mBoard->ZombieTryToGet(mFollowerZombieID[i]))
        {
            bool HaveZombieType;
            if (i == 0)
                HaveZombieType = mBoard->RowCanHaveZombieType(mRow - 1, ZOMBIE_BACKUP_DANCER);
            else if (i == 1)
                HaveZombieType = mBoard->RowCanHaveZombieType(mRow + 1, ZOMBIE_BACKUP_DANCER);
            else
                return true;

            if (HaveZombieType)
                return true;
        }
    }

    return false;
}

void Zombie::UpdateZombieHighGround()
{
    if (mZombieType == ZOMBIE_POGO)
        return;

    if (mZombieHeight == HEIGHT_UP_TO_HIGH_GROUND)
    {
        mAltitude++;
        if (mAltitude >= 30)
        {
            mAltitude = 30;
            mZombieHeight = HEIGHT_ZOMBIE_NORMAL;
        }
    }
    else if (mZombieHeight == HEIGHT_DOWN_OFF_HIGH_GROUND)
    {
        mAltitude--;
        if (mAltitude <= 0.0f)
        {
            mAltitude = 0.0f;
            mZombieHeight = HEIGHT_ZOMBIE_NORMAL;
            mOnHighGround = false;
        }
    }
}

void Zombie::UpdateClimbingLadder()
{
    float aDistOffGround = mAltitude;
    if (mOnHighGround)
    {
        aDistOffGround -= 30;
    }
    int aLadderOriginX = mBoard->PixelToGridXKeepOnBoard(mX + 5 + aDistOffGround * 0.5f, mY);
    if (mBoard->GetLadderAt(aLadderOriginX, mRow) == NULL)
    {
        mZombieHeight = ZombieHeight::HEIGHT_FALLING;
        return;
    }

    mAltitude += 0.8f;
    if (mVelX < 0.5f)
    {
        mPosX -= 0.5f;
    }

    float aTargetHeight = 90.0f;
    if (mOnHighGround)
    {
        aTargetHeight += 30;
    }
    if (mAltitude >= aTargetHeight)
    {
        mZombieHeight = ZombieHeight::HEIGHT_FALLING;
    }
}

bool Zombie::HasYuckyFaceImage()
{
    if (mBoard->mFutureMode)
        return false;

    if (mZombieType == ZOMBIE_NORMAL || mZombieType == ZOMBIE_TRAFFIC_CONE || mZombieType == ZOMBIE_PAIL ||
        mZombieType == ZOMBIE_FLAG || mZombieType == ZOMBIE_DOOR || mZombieType == ZOMBIE_DUCKY_TUBE ||
        mZombieType == ZOMBIE_DANCER || mZombieType == ZOMBIE_BACKUP_DANCER || mZombieType == ZOMBIE_NEWSPAPER ||
        mZombieType == ZOMBIE_POLEVAULTER)
    {
        return true;
    }

    return false;
}

bool Zombie::IsWalkingBackwards()
{
    if (mMindControlled)
        return true;

    if (mZombieHeight == HEIGHT_ZOMBIQUARIUM)
    {
        if (mVelZ < 1.5707964f || mVelZ > 4.712389f)
            return true;
    }

    if (mZombieType == ZOMBIE_DIGGER)
    {
        if (mZombiePhase == PHASE_DIGGER_RISING || mZombiePhase == PHASE_DIGGER_STUNNED ||
            mZombiePhase == PHASE_DIGGER_WALKING)
        {
            return true;
        }
        else if (mZombiePhase == PHASE_ZOMBIE_DYING || mZombiePhase == PHASE_ZOMBIE_BURNED ||
                 mZombiePhase == PHASE_ZOMBIE_MOWERED)
        {
            return mHasObject;
        }

        return false;
    }

    return mZombieType == ZOMBIE_YETI && !mHasObject;
}

int Zombie::GetHelmDamageIndex()
{
    if (mHelmHealth < mHelmMaxHealth / 3)
    {
        return 2;
    }

    if (mHelmHealth < mHelmMaxHealth * 2 / 3)
    {
        return 1;
    }

    return 0;
}

int Zombie::GetBodyDamageIndex()
{
    if (mZombieType == ZombieType::ZOMBIE_BOSS)
    {
        if (mBodyHealth < mBodyMaxHealth / 2)
        {
            return 2;
        }

        if (mBodyHealth < mBodyMaxHealth * 4 / 5)
        {
            return 1;
        }

        return 0;
    }
    else
    {
        if (mBodyHealth < mBodyMaxHealth / 3)
        {
            return 2;
        }

        if (mBodyHealth < mBodyMaxHealth * 2 / 3)
        {
            return 1;
        }

        return 0;
    }
}

int Zombie::GetShieldDamageIndex()
{
    if (mShieldHealth < mShieldMaxHealth / 3)
    {
        return 2;
    }

    if (mShieldHealth < mShieldMaxHealth * 2 / 3)
    {
        return 1;
    }

    return 0;
}

void Zombie::SquishAllInSquare(int theX, int theY, ZombieAttackType theAttackType)
{
    Plant *thePlant = NULL;

    while (mBoard->IteratePlants(thePlant))
    {
        if (theY == thePlant->mRow && theX == thePlant->mPlantCol)
        {
            if (!(theAttackType == ATTACKTYPE_DRIVE_OVER && thePlant->IsSpiky()))
            {
                if (thePlant->mSeedType != SEED_SPIKEROCK)
                {
                    mBoard->mPlantsEaten++;
                    thePlant->Squish();
                }
            }
        }
    }
}

bool Zombie::IsImmobilizied()
{
    if (mIceTrapCounter > 0 || mButteredCounter > 0)
    {
        return true;
    };

    return false;
}

bool Zombie::IsMovingAtChilledSpeed()
{
    ZombieID *i;

    if (mChilledCounter > 0)
        return true;

    if (mZombieType == ZOMBIE_DANCER)
    {
        if (mChilledCounter > 0)
            return true;
    }
    else if (mZombieType == ZOMBIE_BACKUP_DANCER)
    {
        Zombie *related = mBoard->ZombieTryToGet(mRelatedZombieID);
        if (!related)
            return false;
        if (related->mChilledCounter > 0)
            return true;

        int count = 0;
        for (i = related->mFollowerZombieID; count < 4; ++i, ++count)
        {
            Zombie *follower = mBoard->ZombieTryToGet(*i);
            if (follower && follower->mChilledCounter > 0)
                return true;
        }
        return false;
    }
    else
    {
        return false;
    }

    return true;
}

void Zombie::ApplyAnimRate(float theAnimRate)
{
    if (Reanimation *aReanim = mApp->ReanimationTryToGet(mBodyReanimID))
    {
        aReanim->mAnimRate = theAnimRate;
        if (IsMovingAtChilledSpeed())
            aReanim->mAnimRate *= 0.5f;
    }
}

void Zombie::CheckForHighGround()
{
    if (mZombieHeight != HEIGHT_ZOMBIE_NORMAL || mZombieType == ZOMBIE_BUNGEE)
        return;

    bool aIsHighGround = IsOnHighGround();
    if (!mOnHighGround && aIsHighGround)
    {
        mZombieHeight = HEIGHT_UP_TO_HIGH_GROUND;
        mOnHighGround = true;
    }
    else if (mOnHighGround && !aIsHighGround)
    {
        mZombieHeight = HEIGHT_DOWN_OFF_HIGH_GROUND;
    }
}

Reanimation *Zombie::AddAttachedReanim(int thePosX, int thePosY, ReanimationType theReanimType)
{
    Reanimation *v6;  // eax
    Reanimation *v7;  // edi
    float theX;       // [esp+0h] [ebp-18h]
    float theY;       // [esp+4h] [ebp-14h]
    float theOffsetX; // [esp+8h] [ebp-10h]
    float theOffsetY; // [esp+Ch] [ebp-Ch]

    if (this->mDead)
        return NULL;

    theY = (float)(thePosY + this->mY);
    theX = (float)(thePosX + this->mX);
    
    v6 = mApp->AddReanimation(theX, theY, 0, theReanimType);
    v7 = v6;
    if (v6)
    {
        theOffsetY = (float)thePosY;
        theOffsetX = (float)thePosX;
        AttachReanim(this->mAttachmentID, v6, theOffsetX, theOffsetY);
    }
    return v7;
}