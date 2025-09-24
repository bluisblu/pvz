#include "Coin.h"

const double PI = 3.141592741012573;

bool Coin::IsMoney()
{
    if (mType == COIN_SILVER || mType == COIN_GOLD || mType == COIN_DIAMOND)
        return true;

    return false;
}

bool Coin::IsSun()
{
    if (mType == COIN_SUN || mType == COIN_SMALLSUN || mType == COIN_LARGESUN)
        return true;

    return false;
}

bool Coin::IsPresentWithAdvice()
{
    if (mType == COIN_PRESENT_MINIGAMES || mType == COIN_PRESENT_PUZZLE_MODE)
        return true;

    return false;
}

SeedType Coin::GetFinalSeedPacketType()
{
    if (mApp->IsFirstTimeAdventureMode() && mBoard && mBoard->mLevel <= 50)
    {
        return mApp->GetAwardSeedForLevel(mBoard->mLevel);
    }

    return SEED_NONE;
}

int Coin::GetSunValue()
{
    if (mType == COIN_SUN)
        return 25;
    if (mType == COIN_SMALLSUN)
        return 15;
    if (mType == COIN_LARGESUN)
        return 50;

    return 0;
}

int Coin::GetCoinValue(CoinType theCoinType)
{
    if (theCoinType == COIN_SILVER)
        return 1;
    if (theCoinType == COIN_GOLD)
        return 5;
    if (theCoinType == COIN_DIAMOND)
        return 100;

    return 0;
}

void Coin::PlayCollectSound()
{
    if (mType == COIN_USABLE_SEED_PACKET)
    {
        mApp->PlaySample(Sexy::SOUND_SEEDLIFT);
        return;
    }

    if (mType == COIN_SILVER || mType == COIN_GOLD)
    {
        mApp->PlayFoley(FoleyType::FOLEY_COIN);
        return;
    }

    if (mType == COIN_DIAMOND)
    {
        mApp->PlaySample(Sexy::SOUND_DIAMOND);
        return;
    }

    if (IsSun())
    {
        mApp->PlayFoley(FoleyType::FOLEY_SUN);
        return;
    }

    if (mType == COIN_CHOCOLATE || mType == COIN_PRESENT_PLANT || IsPresentWithAdvice() ||
        mType == COIN_AWARD_PRESENT || mType == COIN_AWARD_CHOCOLATE)
    {
        mApp->PlayFoley(FoleyType::FOLEY_PRIZE);
        return;
    }

    if (IsSun())
    {
        mApp->PlayFoley(FoleyType::FOLEY_SUN);
    }
}

bool Coin::MouseHitTest(int theX, int theY, HitResult *theHitResult)
{
    int aOffsetY = 0;
    if (mType == COIN_PRESENT_PLANT || mType == COIN_AWARD_PRESENT || IsPresentWithAdvice())
    {
        aOffsetY = -20;
    }

    int aExtraClickSize = 0;
    int aExtraClickHeight = 0;
    if (mApp->IsWhackAZombieLevel())
    {
        aExtraClickHeight = 30;
        aExtraClickSize = 15;
    }
    if (mType == COIN_SUN)
    {
        aExtraClickSize = 15;
    }

    bool aCanHitCoin = true;
    if (mDead || mIsBeingCollected)
    {
        aCanHitCoin = false;
    }
    if (mType == COIN_USABLE_SEED_PACKET && mBoard)
    {
        if (mBoard->mCursorObject->mCursorType != CURSOR_TYPE_NORMAL && !mApp->IsWhackAZombieLevel())
        {
            aCanHitCoin = false;
        }
    }

    if (aCanHitCoin && theX >= mPosX - aExtraClickSize && theX < mPosX + mWidth + aExtraClickSize &&
        theY >= mPosY + aOffsetY - aExtraClickSize &&
        theY < mPosY + mHeight + aOffsetY + aExtraClickSize + aExtraClickHeight)
    {
        theHitResult->mObject = this;
        theHitResult->mObjectType = OBJECT_TYPE_COIN;
        return true;
    }

    theHitResult->mObject = NULL;
    theHitResult->mObjectType = OBJECT_TYPE_NONE;
    return false;
}

bool Coin::IsLevelAward()
{
    if (mType == COIN_FINAL_SEED_PACKET || mType == COIN_TROPHY || mType == COIN_AWARD_SILVER_SUNFLOWER ||
        mType == COIN_AWARD_GOLD_SUNFLOWER || mType == COIN_SHOVEL || mType == COIN_CARKEYS || mType == COIN_ALMANAC ||
        mType == COIN_VASE || mType == COIN_WATERING_CAN || mType == COIN_TACO || mType == COIN_NOTE ||
        mType == COIN_AWARD_MONEY_BAG || mType == COIN_AWARD_BAG_DIAMOND || mType == COIN_AWARD_PRESENT ||
        mType == COIN_AWARD_CHOCOLATE)
        return true;

    return false;
}

bool Coin::CoinGetsBouncyArrow()
{
    if (IsLevelAward())
        return true;

    if (mType == COIN_SILVER || mType == COIN_GOLD)
    {
        if (mApp->IsFirstTimeAdventureMode() && mBoard && mBoard->mLevel == 11 && !mBoard->mDroppedFirstCoin)
        {
            return true;
        }
    }

    if (IsPresentWithAdvice())
        return true;

    return false;
}

int Coin::GetDisappearTime()
{
    int aTime = 750;

    if (mType == COIN_DIAMOND || mType == COIN_PRESENT_PLANT || mType == COIN_CHOCOLATE || mHasBouncyArrow)
    {
        aTime = 1500;
    }

    if ((mApp->IsScaryPotterLevel() || mApp->IsSlotMachineLevel()) && mType == COIN_USABLE_SEED_PACKET)
    {
        aTime = 1500;
    }

    if (mApp->mGameMode == GAMEMODE_CHALLENGE_ZEN_GARDEN)
    {
        aTime = 6000;
    }

    return aTime;
}

void Coin::DroppedUsableSeed()
{
    mIsBeingCollected = false;

    if (mTimesDropped == 0)
    {
        mDisappearCounter = min(mDisappearCounter, 1200);
    }

    mTimesDropped++;
}

void Coin::FanOutCoins(CoinType theCoinType, int theNumCoins)
{
    // TOD_ASSERT(mBoard);

    for (int i = 0; i < theNumCoins; i++)
    {
        float aAngle = PI / 2 + PI * (i + 1) / (theNumCoins + 1);
        float aPosX = mPosX + 20.0f;
        float aPosY = mPosY;
        Coin *aCoin = mBoard->AddCoin((int)aPosX, (int)aPosY, theCoinType, COIN_MOTION_FROM_PRESENT);
        aCoin->mVelX = 5.0f * sin(aAngle);
        aCoin->mVelY = 5.0f * cos(aAngle);
    }
}

void Coin::UpdateFade()
{
    if (mApp->IsEndlessIZombie(mApp->mGameMode) || mApp->IsEndlessScaryPotter(mApp->mGameMode) || mType == COIN_NOTE ||
        !IsLevelAward())
    {
        mFadeCount--;
        if (mFadeCount == 0)
        {
            Die();
        }
    }
}

void Coin::MouseDown(int x, int y, int theClickCount)
{
    if (mBoard == NULL || mBoard->mPaused || mApp->mGameScene != SCENE_PLAYING || mDead)
    {
        return;
    }

    if (theClickCount >= 0 && !mIsBeingCollected)
    {
        PlayCollectSound();
        Collect();

        if (mApp->IsFirstTimeAdventureMode() && mBoard->mLevel == 1)
        {
            mBoard->DisplayAdvice(_S("[ADVICE_CLICKED_ON_SUN]"), MESSAGE_STYLE_TUTORIAL_LEVEL1_STAY,
                                  ADVICE_CLICKED_ON_SUN);
        }
    }
}

void Coin::TryAutoCollectAfterLevelAward()
{
    // IsMoney(), IsSun(), and IsPresentWithAdvice seem to get inlined
    // into here but this is the best match so far
    if ((mType == COIN_SILVER || mType == COIN_GOLD || mType == COIN_DIAMOND) &&
            this->mCoinMotion != COIN_MOTION_FROM_PRESENT ||
        mType == COIN_SUN || mType == COIN_SMALLSUN || mType == COIN_LARGESUN || mType == COIN_PRESENT_PLANT ||
        mType == COIN_CHOCOLATE || mType == COIN_PRESENT_MINIGAMES || mType == COIN_PRESENT_PUZZLE_MODE)
    {
        this->PlayCollectSound();
        this->Collect();
    }
}