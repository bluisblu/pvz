#include "Reanimator.h"
#include "SexyAppFramework/Common.h"

#include "Challenge.h"
#include "LawnApp.h"
#include "Plant.h"

Plant::Plant()
{
    mPlantRect[0] = 0;       // mX
    mPlantRect[1] = 0;       // mY
    mPlantRect[2] = 0;       // mWidth
    mPlantRect[3] = 0;       // mHeight
    mPlantAttackRect[0] = 0; // mX
    mPlantAttackRect[1] = 0; // mY
    mPlantAttackRect[2] = 0; // mWidth
    mPlantAttackRect[3] = 0; // mHeight
}

int Plant::GetDamageRangeFlags(PlantWeapon thePlantWeapon)
{
    SeedType s = mSeedType;
    if (s == SEED_CACTUS)
    {
        return (thePlantWeapon != WEAPON_SECONDARY) + 1;
    }
    if ((((s == SEED_CHERRYBOMB) || (s == SEED_JALAPENO)) || (s == SEED_COBCANNON)) || (s == SEED_DOOMSHROOM))
    {
        return 0x7f;
    }
    if (((s == SEED_MELONPULT) || (s == SEED_CABBAGEPULT)) || ((s == SEED_KERNELPULT || (s == SEED_WINTERMELON))))
    {
        return 0xd;
    }
    if (s == SEED_POTATOMINE)
    {
        return 0x4d;
    }
    if (s == SEED_SQUASH)
    {
        return 0x1d;
    }
    if (((s == SEED_PUFFSHROOM) || (s == SEED_SEASHROOM)) ||
        ((s == SEED_FUMESHROOM || ((s == SEED_GLOOMSHROOM || (s == SEED_CHOMPER))))))
    {
        return 9;
    }
    if (s == SEED_CATTAIL)
    {
        return 0xb;
    }
    if (s == SEED_TANGLEKELP)
    {
        return 5;
    }
    if (s == SEED_GIANT_WALLNUT)
    {
        return 0x11;
    }

    return 1;
}

bool Plant::IsOnHighGround()
{
    if (mBoard == NULL)
    {
        return false;
    }

    if (mBoard->mGridSquareType[mPlantCol][mRow] == GRIDSQUARE_HIGH_GROUND)
        return true;

    return false;
}

bool Plant::MakesSun()
{
    SeedType s = mSeedType;
    if ((s == SEED_SUNFLOWER) || (s == SEED_TWINSUNFLOWER) || (s == SEED_SUNSHROOM))
    {
        return true;
    }
    return false;
}

void Plant::PlayBodyReanim(const char *theTrackName, ReanimLoopType theLoopType, int theBlendTime, float theAnimRate)
{
    Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);

    if (theBlendTime > 0)
        aBodyReanim->StartBlend(theBlendTime);
    if (theAnimRate > 0.0f)
        aBodyReanim->mAnimRate = theAnimRate;

    aBodyReanim->mLoopType = theLoopType;
    aBodyReanim->mLoopCount = 0;
    aBodyReanim->SetFramesForLayer(theTrackName);
}

void Plant::UpdateDoomShroom()
{
    if (mIsAsleep || mState == PlantState::STATE_DOINGSPECIAL)
        return;

    mState = PlantState::STATE_DOINGSPECIAL;
    mDoSpecialCountdown = 100;

    Reanimation *aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    // TOD_ASSERT(aBodyReanim);

    aBodyReanim->SetFramesForLayer("anim_explode");
    aBodyReanim->mAnimRate = 23.0f;
    aBodyReanim->mLoopType = ReanimLoopType::REANIM_PLAY_ONCE_AND_HOLD;
    aBodyReanim->SetShakeOverride("DoomShroom_head1", 1.0f);
    aBodyReanim->SetShakeOverride("DoomShroom_head2", 2.0f);
    aBodyReanim->SetShakeOverride("DoomShroom_head3", 2.0f);
    mApp->PlayFoley(FoleyType::FOLEY_REVERSE_EXPLOSION);
}

void Plant::UpdateIceShroom()
{
    if ((mIsAsleep == false) && (mState != STATE_DOINGSPECIAL))
    {
        mState = STATE_DOINGSPECIAL;
        mDoSpecialCountdown = 100;
    }
}

void Plant::UpdateFlowerPot()
{
    if ((mState == STATE_FLOWERPOT_INVULNERABLE) && (mStateCountdown == 0))
    {
        mState = STATE_NOTREADY;
    }
}

void Plant::UpdateLilypad()
{
    if ((mState == STATE_LILYPAD_INVULNERABLE) && (mStateCountdown == 0))
    {
        mState = STATE_NOTREADY;
    }
    return;
}

MagnetItem *Plant::GetFreeMagnetItem()
{
    if (mSeedType == SeedType::SEED_GOLD_MAGNET)
    {
        for (int i = 0; i < MAX_MAGNET_ITEMS; i++)
        {
            if (mMagnetItems[i].mItemType == MagnetItemType::MAGNET_ITEM_NONE)
            {
                return &mMagnetItems[i];
            }
        }

        return NULL;
    }

    return &mMagnetItems[0];
}

bool Plant::IsAGoldMagnetAboutToSuck()
{
    for (Plant *aPlant = NULL; mBoard->IteratePlants(aPlant);)
    {
        if (aPlant->mState == STATE_MAGNETSHROOM_SUCKING)
        {
            Reanimation *aBodyReanim = mApp->ReanimationGet(aPlant->mBodyReanimID);
            if (aBodyReanim->mAnimTime < 0.5f)
            {
                return true;
            }
        }
    }

    return false;
}

void Plant::RemoveEffects()
{
    mApp->RemoveParticle(mParticleID);
    mApp->RemoveReanimation(mBodyReanimID);
    mApp->RemoveReanimation(mHeadReanimID);
    mApp->RemoveReanimation(mHeadReanimID2);
    mApp->RemoveReanimation(mHeadReanimID3);
    mApp->RemoveReanimation(mLightReanimID);
    mApp->RemoveReanimation(mBlinkReanimID);
    mApp->RemoveReanimation(mSleepingReanimID);
}

bool Plant::IsUpgradableTo(SeedType aUpdatedType)
{
    if (aUpdatedType == SEED_GATLINGPEA && mSeedType == SEED_REPEATER)
    {
        return true;
    }
    else if (aUpdatedType == SEED_WINTERMELON && mSeedType == SEED_MELONPULT)
    {
        return true;
    }
    else if (aUpdatedType == SEED_TWINSUNFLOWER && mSeedType == SEED_SUNFLOWER)
    {
        return true;
    }
    else if (aUpdatedType == SEED_SPIKEROCK && mSeedType == SEED_SPIKEWEED)
    {
        return true;
    }
    else if (aUpdatedType == SEED_COBCANNON && mSeedType == SEED_KERNELPULT &&
             mBoard->IsValidCobCannonSpot(mPlantCol, mRow))
    {
        return true;
    }
    else if (aUpdatedType == SEED_GOLD_MAGNET && mSeedType == SEED_MAGNETSHROOM)
    {
        return true;
    }
    else if (aUpdatedType == SEED_GLOOMSHROOM && mSeedType == SEED_FUMESHROOM)
    {
        return true;
    }
    else if (aUpdatedType == SEED_CATTAIL && mSeedType == SEED_LILYPAD)
    {
        Plant *topPlant = mBoard->GetTopPlantAt(mPlantCol, mRow, TOPPLANT_ONLY_NORMAL_POSITION);
        if (topPlant == 0x0 || topPlant->mSeedType != SEED_CATTAIL)
        {
            return true;
        }
    }

    return false;
}

bool Plant::NotOnGround()
{
    if (mSeedType == SEED_SQUASH)
    {
        if (mState == STATE_SQUASH_RISING || mState == STATE_SQUASH_FALLING || mState == STATE_SQUASH_DONE_FALLING)
        {
            return true;
        }
    }

    if (mSquished)
        return true;

    if (mIsOnBungee)
        return true;

    if (mDead)
        return true;

    return false;
}

void Plant::EndBlink()
{
    if (mBlinkReanimID != REANIMATIONID_NULL)
    {
        mApp->RemoveReanimation(mBlinkReanimID);
        mBlinkReanimID = REANIMATIONID_NULL;

        Reanimation *aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
        if (aBodyReanim)
        {
            aBodyReanim->AssignRenderGroupToPrefix("anim_eye", RENDER_GROUP_NORMAL);
        }
    }
}

void Plant::GetPeaHeadOffset(int &theOffsetX, int &theOffsetY)
{
    Reanimation *aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);

    int aTrackIndex = 0;
    if (aBodyReanim->TrackExists("anim_stem"))
    {
        aTrackIndex = aBodyReanim->FindTrackIndex("anim_stem");
    }
    else if (aBodyReanim->TrackExists("anim_idle"))
    {
        aTrackIndex = aBodyReanim->FindTrackIndex("anim_idle");
    }

    ReanimatorTransform aTransform;
    aBodyReanim->GetCurrentTransform(aTrackIndex, &aTransform);
    theOffsetX = aTransform.mTransX; // * aBodyReanim->mOverlayMatrix.m00;
    theOffsetY = aTransform.mTransY; // * aBodyReanim->mOverlayMatrix.m11;
}

void Plant::BurnRow(int theRow)
{
    int aDamageRangeFlags = GetDamageRangeFlags(PlantWeapon::WEAPON_PRIMARY);

    Zombie *aZombie = NULL;
    while (mBoard->IterateZombies(aZombie))
    {
        if ((aZombie->mZombieType == ZombieType::ZOMBIE_BOSS || aZombie->mRow == theRow) &&
            aZombie->EffectedByDamage(aDamageRangeFlags))
        {
            aZombie->RemoveColdEffects();
            aZombie->ApplyBurn();
        }
    }

    /*GridItem* aGridItem = NULL;
    while (mBoard->IterateGridItems(aGridItem))
    {
        if (aGridItem->mGridY == theRow && aGridItem->mGridItemType == GridItemType::GRIDITEM_LADDER)
        {
            aGridItem->GridItemDie();
        }
    }*/

    Zombie *aBossZombie = NULL;
    while (mBoard->IterateZombies(aBossZombie))
    {
        if (aBossZombie->mZombieType == ZOMBIE_BOSS && aBossZombie->mFireballRow == theRow)
        {
            // 注：原版中将 Zombie::BossDestroyIceballInRow(int) 函数改为了
            // Zombie::BossDestroyIceball()，冰球是否位于目标行的判断则移动至此处进行
            aBossZombie->BossDestroyIceballInRow(theRow);
        }
    }
}

int Plant::GetCost(SeedType theSeedType, SeedType theImitaterType)
{
    if (gLawnApp->mGameMode == GAMEMODE_CHALLENGE_BEGHOULED ||
        gLawnApp->mGameMode == GAMEMODE_CHALLENGE_BEGHOULED_TWIST)
    {
        if (theSeedType == SEED_REPEATER)
            return 1000;
        if (theSeedType == SEED_FUMESHROOM)
            return 500;
        if (theSeedType == SEED_TALLNUT)
            return 250;
        if (theSeedType == SEED_BEGHOULED_BUTTON_SHUFFLE)
            return 100;
        if (theSeedType == SEED_BEGHOULED_BUTTON_CRATER)
            return 200;
    }

    switch (theSeedType)
    {
    case SEED_SLOT_MACHINE_SUN:
    case SEED_SLOT_MACHINE_DIAMOND:
        return 0;
    case SEED_ZOMBIQUARIUM_TROPHY:
        return 1000;
    case SEED_ZOMBIE_NORMAL:
        return 50;
    case SEED_ZOMBIE_TRAFFIC_CONE:
    case SEED_ZOMBIE_POLEVAULTER:
        return 75;
    case SEED_ZOMBIE_DANCER:
        return 350;
    case SEED_ZOMBIE_PAIL:
    case SEED_ZOMBIE_DIGGER:
    case SEED_ZOMBIE_BUNGEE:
        return 125;
    case SEED_ZOMBIE_LADDER:
    case SEED_ZOMBIE_BALLOON:
        return 150;
    case SEED_ZOMBIQUARIUM_SNORKLE:
    case SEED_ZOMBIE_SCREEN_DOOR:
        return 100;
    case SEED_ZOMBIE_FOOTBALL:
    case SEED_ZOMBONI:
        return 175;
    case SEED_ZOMBIE_POGO:
        return 200;
    case SEED_ZOMBIE_GARGANTUAR:
        return 300;
    case SEED_ZOMBIE_IMP:
        return 50;
    default:
        if (theSeedType == SEED_IMITATER && theImitaterType != SEED_NONE)
        {
            return GetPlantDefinition(theImitaterType).mSeedCost;
        }
        else
        {
            return GetPlantDefinition(theSeedType).mSeedCost;
        }
    }
}

int Plant::GetRefreshTime(SeedType theSeedType, SeedType theImitaterType)
{
    bool bVar1 = Challenge::IsZombieSeedType(theSeedType);
    if (bVar1)
    {
        return 0;
    }
    if ((theSeedType == SEED_IMITATER) && (theImitaterType != SEED_NONE))
    {
        return GetPlantDefinition(theImitaterType).mRefreshTime;
    }
    return GetPlantDefinition(theSeedType).mRefreshTime;
}

bool Plant::IsNocturnal(SeedType theSeedtype)
{
    if (theSeedtype == SEED_PUFFSHROOM || theSeedtype == SEED_SEASHROOM || theSeedtype == SEED_SUNSHROOM ||
        theSeedtype == SEED_FUMESHROOM || theSeedtype == SEED_HYPNOSHROOM || theSeedtype == SEED_DOOMSHROOM ||
        theSeedtype == SEED_ICESHROOM || theSeedtype == SEED_MAGNETSHROOM || theSeedtype == SEED_SCAREDYSHROOM ||
        theSeedtype == SEED_GLOOMSHROOM)
        return true;

    return false;
}

bool Plant::IsAquatic(SeedType theSeedtype)
{
    if (theSeedtype == SEED_LILYPAD || theSeedtype == SEED_TANGLEKELP || theSeedtype == SEED_SEASHROOM ||
        theSeedtype == SEED_CATTAIL)
        return true;
    return false;
}

bool Plant::IsFlying(SeedType theSeedtype)
{
    if (theSeedtype == SEED_INSTANT_COFFEE)
        return true;
    return false;
}

bool Plant::IsSpiky()
{
    if (mSeedType == SEED_SPIKEWEED || mSeedType == SEED_SPIKEROCK)
        return true;
    return false;
}

bool Plant::IsUpgrade(SeedType theSeedtype)
{
    if (theSeedtype == SEED_GATLINGPEA || theSeedtype == SEED_WINTERMELON || theSeedtype == SEED_TWINSUNFLOWER ||
        theSeedtype == SEED_SPIKEROCK || theSeedtype == SEED_COBCANNON || theSeedtype == SEED_GOLD_MAGNET ||
        theSeedtype == SEED_GLOOMSHROOM || theSeedtype == SEED_CATTAIL)
        return true;
    return false;
}

void Plant::PlayIdleAnim(float theRate)
{
    Reanimation *aBodyReanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (aBodyReanim)
    {
        Reanimation *aTrackAnim = mApp->ReanimationGet(mBodyReanimID);
        aTrackAnim->StartBlend(20);
        if (theRate > 0.0)
            aTrackAnim->mAnimRate = theRate;
        aTrackAnim->mLoopType = REANIM_LOOP;
        aTrackAnim->mLoopCount = 0;
        aTrackAnim->SetFramesForLayer("anim_idle");
        if (mApp->IsIZombieLevel())
        {
            aBodyReanim->mAnimRate = 0.0f;
        }
    }
}

int Plant::CalcRenderOrder()
{
    int anOrder = PLANT_ORDER_NORMAL;
    RenderLayer aLayer = RENDER_LAYER_PLANT;
    SeedType seedType = mSeedType;

    if (seedType == SEED_IMITATER && mImitaterType != SEED_NONE)
    {
        seedType = mImitaterType;
    }

    if (mApp->IsWallnutBowlingLevel())
    {
        aLayer = RENDER_LAYER_PROJECTILE;
    }
    else if (seedType == SEED_PUMPKINSHELL)
    {
        anOrder = PLANT_ORDER_PUMPKIN;
    }
    else if (seedType == SEED_INSTANT_COFFEE)
    {
        anOrder = PLANT_ORDER_FLYER;
    }
    else if (seedType == SEED_FLOWERPOT ||
             (seedType == SEED_LILYPAD && mApp->mGameMode != GAMEMODE_CHALLENGE_ZEN_GARDEN))
    {
        anOrder = PLANT_ORDER_LILYPAD;
    }

    return Board::MakeRenderOrder(aLayer, mRow, anOrder * 5 - mX + 800);
}

float RandRangeFloat(float theMin, float theMax);

void Plant::SetSleeping(bool theIsAsleep)
{
    if (mIsAsleep == theIsAsleep)
        return;

    if ((mSeedType == SEED_SQUASH) &&
        (mState == STATE_SQUASH_RISING || mState == STATE_SQUASH_FALLING || mState == STATE_SQUASH_DONE_FALLING))
        return;

    if (mSquished || mIsOnBungee || mDead)
        return;

    mIsAsleep = theIsAsleep;

    Reanimation *reanim = NULL;
    float aAnimTime, aPosX, aPosY;

    if (theIsAsleep)
    {
        aPosX = mX + 50.0f;
        aPosY = mY + 40.0f;

        if (mSeedType == SEED_FUMESHROOM)
        {
            aPosX += 12.0f;
        }
        else if (mSeedType == SEED_SCAREDYSHROOM)
        {
            aPosY -= 20.0f;
        }
        else if (mSeedType == SEED_GLOOMSHROOM)
        {
            aPosY -= 12.0f;
        }

        reanim = mApp->AddReanimation(aPosX, aPosY, mRenderOrder + 2, REANIM_SLEEPING);
        reanim->mLoopType = REANIM_LOOP;
        reanim->mAnimRate = RandRangeFloat(6.0f, 8.0f);
        reanim->mAnimTime = RandRangeFloat(0.0f, 0.9f);
        mSleepingReanimID = mApp->ReanimationGetID(reanim);
    }
    else
    {
        mApp->RemoveReanimation(mSleepingReanimID);
        mSleepingReanimID = REANIMATIONID_NULL;
    }

    reanim = mApp->ReanimationTryToGet(mBodyReanimID);
    if (!reanim)
        return;

    if (theIsAsleep)
    {
        if (!IsInPlay() && mSeedType == SEED_SUNSHROOM)
        {
            reanim->SetFramesForLayer("anim_bigsleep");
            EndBlink();
            return;
        }

        if (reanim->TrackExists("anim_sleep"))
        {
            aAnimTime = reanim->mAnimTime;
            reanim->StartBlend(0x14);
            reanim->SetFramesForLayer("anim_sleep");
            reanim->mAnimTime = aAnimTime;
        }
        else
        {
            reanim->mAnimRate = 1.0f;
        }

        EndBlink();
        return;
    }

    if (IsInPlay() || mSeedType != SEED_SUNSHROOM)
    {
        if (reanim->TrackExists("anim_idle"))
        {
            aAnimTime = reanim->mAnimTime;
            reanim->StartBlend(0x14);
            reanim->SetFramesForLayer("anim_idle");
            reanim->mAnimTime = aAnimTime;
        }
    }
    else
    {
        reanim->SetFramesForLayer("anim_bigidle");
    }

    if (reanim->mAnimRate < 2.0f && IsInPlay())
    {
        reanim->mAnimRate = RandRangeFloat(10.0f, 15.0f);
    }
}

void Plant::LaunchStarFruit()
{

    if (FindStarFruitTarget())
    {
        // PlayBodyReanim() (inlined)
        Reanimation *aBodyReanim = mApp->ReanimationGet(mBodyReanimID);
        aBodyReanim->StartBlend(20);
        aBodyReanim->mAnimRate = 28.0;
        aBodyReanim->mLoopType = REANIM_PLAY_ONCE_AND_HOLD;
        aBodyReanim->mLoopCount = 0;
        aBodyReanim->SetFramesForLayer("anim_shoot");
        //
        mShootingCounter = 40;
    }
}

bool Plant::IsPartOfUpgradableTo(SeedType aUpdatedType)
{
    if (aUpdatedType == SEED_COBCANNON && mSeedType == SEED_KERNELPULT)
    {
        if (!mBoard->IsValidCobCannonSpot(mPlantCol, mRow))
        {
            if (!mBoard->IsValidCobCannonSpot(mPlantCol - 1, mRow))
            {
                return false;
            }
        }
        return true;
    }

    return IsUpgradableTo(aUpdatedType);
}

void Plant::Animate()
{
    SeedType s;
    int iVar2;
    int iVar3;
    float fVar4;

    if (((mSeedType == SEED_CHERRYBOMB) || (mSeedType == SEED_JALAPENO)) &&
        (mApp->mGameMode != GAMEMODE_CHALLENGE_ZEN_GARDEN))
    {
        mShakeOffsetX = Sexy::Rand(2.0f) - 1.0f;
        mShakeOffsetY = Sexy::Rand(2.0f) - 1.0f;
    }
    if (mRecentlyEatenCountdown > 0)
    {
        mRecentlyEatenCountdown = mRecentlyEatenCountdown + -1;
    }
    if (mEatenFlashCountdown > 0)
    {
        mEatenFlashCountdown = mEatenFlashCountdown + -1;
    }
    if (mBeghouledFlashCountdown > 0)
    {
        mBeghouledFlashCountdown = mBeghouledFlashCountdown + -1;
    }
    if (mSquished != false)
    {
        mFrame = 0;
        return;
    }
    s = mSeedType;
    if ((s == SEED_WALLNUT) || (s == SEED_TALLNUT))
    {
        AnimateNuts();
    }
    else if (s == SEED_GARLIC)
    {
        AnimateGarlic();
    }
    else if (s == SEED_PUMPKINSHELL)
    {
        AnimatePumpkin();
    }
    UpdateBlink();
    iVar3 = mAnimCounter;
    if (mAnimPing != false)
    {
        iVar2 = mFrameLength;
        if (iVar3 < mNumFrames * iVar2 + -1)
        {
            mAnimCounter = iVar3 + 1;
            mFrame = (iVar3 + 1) / iVar2;
            return;
        }
        mAnimCounter = iVar3 - iVar2;
        mAnimPing = false;
        mFrame = (iVar3 - iVar2) / mFrameLength;
        return;
    }
    if (iVar3 > 0)
    {
        mAnimCounter = iVar3 + -1;
        mFrame = (iVar3 + -1) / mFrameLength;
        return;
    }
    iVar3 = mFrameLength + iVar3;
    mAnimPing = true;
    mAnimCounter = iVar3;
    mFrame = iVar3 / mFrameLength;
    return;
}

void Plant::Die()
{
    Board *pBVar1;
    // code *pcVar2;
    BOOL BVar3;
    Zombie *this_00;
    int this_01;
    Plant *pPVar4;
    Plant *pPVar5;
    Reanimation *pRVar6;
    ZenGarden *this_02;
    ZenGarden *this_03;
    ZenGarden *this_04;
    float fVar7;

    if (mIsOnBoard != false)
    {

        if (mBoard == NULL)
        {
            /*TodAssertFailed("mBoard", ".\\Plant.cpp", 0xe76, "");
            BVar3 = IsDebuggerPresent();
            if (BVar3 != 0)
            {
                pcVar2 = swi(3);
                (*pcVar2)();
                return;
            }*/
            this_02->ZenGardenStart();
            return;
        }
        if ((mSeedType == SEED_TANGLEKELP) && (this_00 = mBoard->ZombieTryToGet(mTargetZombieID), this_00 != NULL))
        {
            this_00->DieWithLoot();
        }
    }
    mDead = true;
    RemoveEffects();
    if (mSeedType != SEED_INSTANT_COFFEE)
    {
        if (mIsOnBoard == false)
        {
            return;
        }

        if (mBoard == NULL)
        {
            /* TodAssertFailed("mBoard", ".\\Plant.cpp", 0xe76, "");
            BVar3 = IsDebuggerPresent();
            if (BVar3 != 0)
            {
                pcVar2 = swi(3);
                (*pcVar2)();
                return;
            }*/
            this_03->ZenGardenStart();
            return;
        }
        this_01 = mBoard->GetLadderAt(mPlantCol, mRow);
        if (this_01 != NULL)
        {
            // this_01->GridItemDie();
        }
    }
    if (mIsOnBoard != false)
    {

        if (mBoard == NULL)
        {
            /* TodAssertFailed("mBoard", ".\\Plant.cpp", 0xe76, "");
            BVar3 = IsDebuggerPresent();
            if (BVar3 != 0)
            {
                pcVar2 = swi(3);
                (*pcVar2)();
                return;
            }*/
            this_04->ZenGardenStart();
            return;
        }
        pPVar4 = mBoard->GetTopPlantAt(mPlantCol, mRow, TOPPLANT_BUNGEE_ORDER);
        pPVar5 = mBoard->GetFlowerPotAt(mPlantCol, mRow);
        if ((pPVar5 != 0x0) && (pPVar4 == pPVar5))
        {
            pRVar6 = mApp->ReanimationGet(pPVar5->mBodyReanimID);
            fVar7 = RandRangeFloat(10.0, 15.0);
            pRVar6->mAnimRate = fVar7;
        }
    }
    return;
}

void Plant::KillAllPlantsNearDoom()
{
    Plant *aPlant = NULL;

    while (mBoard->IteratePlants(aPlant))
    {
        // x - y == 0 is equivalent to x == y, but for some reason
        // the comparison on the right is a sub instruction, not a cmp
        if (aPlant->mRow == mRow && (aPlant->mPlantCol - mPlantCol) == 0)

        {
            aPlant->Die();
        }
    }
}

void Plant::UpdateAbilities()
{
    if (IsInPlay())
    {
        if (mState == STATE_DOINGSPECIAL || mSquished)
        {
            --mDisappearCountdown;
            if (mDisappearCountdown < 0)
            {
                Die();
                return;
            }
        }
        if (mWakeUpCounter > 0)
        {
            --mWakeUpCounter;
            if (mWakeUpCounter == 60)
            {
                mApp->PlayFoley(FOLEY_WAKEUP);
            }
            if (mWakeUpCounter == 0)
            {
                SetSleeping(false);
            }
        }
        if (!mIsAsleep && !mIsOnBungee && !mSquished)
        {
            UpdateShooting();
            if (0 < mStateCountdown)
            {
                mStateCountdown = mStateCountdown + -1;
            }
            if (mApp->IsWallnutBowlingLevel())
            {
                UpdateBowling();
                return;
            }
            if (mSeedType == SEED_SQUASH)
            {
                UpdateSquash();
            }
            else if (mSeedType == SEED_DOOMSHROOM)
            {
                UpdateDoomShroom();
            }
            else if (mSeedType == SEED_ICESHROOM)
            {
                UpdateIceShroom();
            }
            else if (mSeedType == SEED_CHOMPER)
            {
                UpdateChomper();
            }
            else if (mSeedType == SEED_BLOVER)
            {
                UpdateBlover();
            }
            else if (mSeedType == SEED_FLOWERPOT)
            {
                UpdateFlowerPot();
            }
            else if (mSeedType == SEED_LILYPAD)
            {
                UpdateLilypad();
            }
            else if (mSeedType == SEED_IMITATER)
            {
                UpdateImitater();
            }
            else if (mSeedType == SEED_INSTANT_COFFEE)
            {
                UpdateCoffeeBean();
            }
            else if (mSeedType == SEED_UMBRELLA)
            {
                UpdateUmbrella();
            }
            else if (mSeedType == SEED_COBCANNON)
            {
                UpdateCobCannon();
            }
            else if (mSeedType == SEED_CACTUS)
            {
                UpdateCactus();
            }
            else if (mSeedType == SEED_MAGNETSHROOM)
            {
                UpdateMagnetShroom();
            }
            else if (mSeedType == SEED_GOLD_MAGNET)
            {
                UpdateGoldMagnetShroom();
            }
            else if (mSeedType == SEED_SUNSHROOM)
            {
                UpdateSunShroom();
            }
            else if (MakesSun() || mSeedType == SEED_MARIGOLD)
            {
                UpdateProductionPlant();
            }
            else if (mSeedType == SEED_GRAVEBUSTER)
            {
                UpdateGraveBuster();
            }
            else if (mSeedType == SEED_TORCHWOOD)
            {
                UpdateTorchwood();
            }
            else if (mSeedType == SEED_POTATOMINE)
            {
                UpdatePotato();
            }
            else if (mSeedType == SEED_SPIKEWEED || mSeedType == SEED_SPIKEROCK)
            {
                UpdateSpikeweed();
            }
            else if (mSeedType == SEED_TANGLEKELP)
            {
                UpdateTanglekelp();
            }
            else if (mSeedType == SEED_SCAREDYSHROOM)
            {
                UpdateScaredyShroom();
            }
            if (mSubclass == SEED_SUNFLOWER)
            {
                UpdateShooter();
            }
            if (mDoSpecialCountdown > 0)
            {
                if (--mDoSpecialCountdown == 0)
                {
                    DoSpecial();
                    return;
                }
            }
        }
    }
    return;
}
