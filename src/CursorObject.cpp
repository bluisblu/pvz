#include "GameObject.h"
#include "SexyAppFramework/SexyAppBase.h"

#include "CursorObject.h"
#include "LawnApp.h"
#include "Reanimator.h"
#include "ZenGarden.h"

CursorObject::CursorObject()
{
    Reanimation *reanim;
    ReanimationID reanim_id;

    mType = SEED_NONE;
    mImitaterType = SEED_NONE;
    mSeedBankIndex = -1;
    mX = 0;
    mY = 0;
    mCursorType = CURSOR_TYPE_NORMAL;
    mCoinID = COINID_NULL;
    mDuplicatorPlantID = PLANTID_NULL;
    mCobCannonPlantID = PLANTID_NULL;
    mGlovePlantID = PLANTID_NULL;
    mReanimCursorID = REANIMATIONID_NULL;
    if (mApp->IsWhackAZombieLevel())
    {
        ReanimatorEnsureDefinitionLoaded(REANIM_HAMMER, true);
        reanim = mApp->AddReanimation(-25.0f, 16.0f, 0, REANIM_HAMMER);
        reanim->mIsAttachment = true;
        reanim->PlayReanim("anim_whack_zombie", REANIM_PLAY_ONCE_AND_HOLD, 0, 24.0f);
        reanim->mAnimTime = 1.0;
        reanim_id = mApp->ReanimationGetID(reanim);
        mReanimCursorID = reanim_id;
    }
    mWidth = 80;
    mHeight = 80;
}

void CursorObject::Update()
{
    if (mApp->mGameScene != GameScenes::SCENE_PLAYING && !mBoard->mCutScene->IsInShovelTutorial())
    {
        mVisible = false;
        return;
    }

    if (!mApp->mWidgetManager->mMouseIn)
    {
        mVisible = false;
        return;
    }

    Reanimation *aCursorReanim = mApp->ReanimationTryToGet(mReanimCursorID);
    if (aCursorReanim)
    {
        aCursorReanim->Update();
    }

    mVisible = true;
    mX = mApp->mWidgetManager->mLastMouseX - 25;
    mY = mApp->mWidgetManager->mLastMouseY - 35;
}

void CursorObject::Draw(Sexy::Graphics *g)
{
    CursorType CVar1;
    int iVar2;
    Board *this_00;
    bool bVar3;
    PottedPlant *pPVar4;
    Plant *pPVar5;
    Reanimation *this_01;
    float local_c;
    HitResult local_8;

    CVar1 = this->mCursorType;
    if (CVar1 == CURSOR_TYPE_SHOVEL)
    {
        g->DrawImageCel(Sexy::IMAGE_SHOVEL, 10, -0x1e, 1);
        return;
    }
    if (CVar1 == CURSOR_TYPE_WATERING_CAN)
    {
        if (mApp->mPlayerInfo->mPurchases[0x34] == 0)
        {
            g->DrawImage(Sexy::IMAGE_WATERINGCAN, -3, 0xc);
            return;
        }
        g->DrawImage(Sexy::IMAGE_ZEN_GOLDTOOLRETICLE, -0x2a, -0x1c);
        g->DrawImage(Sexy::IMAGE_WATERINGCANGOLD, -3, 0xc);
        return;
    }
    if (CVar1 == CURSOR_TYPE_FERTILIZER)
    {
        g->DrawImage(Sexy::IMAGE_FERTILIZER, -0xf, 0);
        return;
    }
    if (CVar1 == CURSOR_TYPE_BUG_SPRAY)
    {
        g->DrawImage(Sexy::IMAGE_BUG_SPRAY, -9, -1);
        return;
    }
    if (CVar1 == CURSOR_TYPE_PHONOGRAPH)
    {
        g->DrawImage(Sexy::IMAGE_PHONOGRAPH, -0x11, 10);
        return;
    }
    if (CVar1 == CURSOR_TYPE_CHOCOLATE)
    {
        g->DrawImage(Sexy::IMAGE_CHOCOLATE, -2, -8);
        return;
    }
    if (CVar1 == CURSOR_TYPE_GLOVE)
    {
        g->DrawImage(Sexy::IMAGE_ZEN_GARDENGLOVE, -0x11, 0xf);
        return;
    }
    if (CVar1 != CURSOR_TYPE_MONEY_SIGN)
    {
        if (CVar1 == CURSOR_TYPE_TREE_FOOD)
        {
            g->DrawImage(Sexy::IMAGE_TREEFOOD, -0xf, 0);
            return;
        }
        if (CVar1 == CURSOR_TYPE_WHEEELBARROW)
        {
            pPVar4 = mApp->mZenGarden->GetPottedPlantInWheelbarrow();
            if (pPVar4 == 0x0)
            {
                g->DrawImage(Sexy::IMAGE_ZEN_WHEELBARROW, -0x14, -0x1e);
                return;
            }
            g->DrawImage(Sexy::IMAGE_ZEN_WHEELBARROW, -0x14, -0x17);
            if (pPVar4->mPlantAge == PLANTAGE_SMALL)
            {
                mApp->mZenGarden->DrawPottedPlant(g, 10.0, -35.0, pPVar4, 0.6, true);
                return;
            }
            if (pPVar4->mPlantAge != PLANTAGE_MEDIUM)
            {
                mApp->mZenGarden->DrawPottedPlant(g, 21.0, -15.0, pPVar4, 0.4, true);
                return;
            }
            mApp->mZenGarden->DrawPottedPlant(g, 15.0, -25.0, pPVar4, 0.5, true);
            return;
        }
        /*if (CVar1 == CURSOR_TYPE_PLANT_FROM_GLOVE)
        {
            pPVar5 = mBoard->mPlants->DataArrayGet(this->mGlovePlantID);
            pPVar4 = mApp->GetPottedPlantByIndex(pPVar5->mPottedPlantIndex);
        }*/
        else
        {
            if (CVar1 != CURSOR_TYPE_PLANT_FROM_WHEEL_BARROW)
            {
                /*if (((CVar1 == CURSOR_TYPE_PLANT_FROM_BANK) || (CVar1 == CURSOR_TYPE_PLANT_FROM_USABLE_COIN)) ||
                    (CVar1 == CURSOR_TYPE_PLANT_FROM_DUPLICATOR))
                {
                    local_8.mObject = (HitResult *)0xc1200000;
                    local_c = PlantDrawHeightOffset(mBoard, 0x0, this->mType, -1, -1);
                    local_c = local_c - 10.0;
                    bVar3 = Plant::IsFlying(this->mType);
                    if ((bVar3) || (this->mType == SEED_GRAVEBUSTER))
                    {
                        local_c = local_c + 30.0;
                    }
                    local_c = local_c - 15.0;
                    bVar3 = mApp->IsIZombieLevel();
                    if (bVar3)
                    {
                        local_8.mObject = (HitResult *)0xc2820000;
                        local_c = local_c - 70.0;
                    }
                    Plant::DrawSeedType(g, this->mType, this->mImitaterType, VARIATION_NORMAL, local_8.mObject,
                                        local_c);
                    return;
                }*/
                if (CVar1 == CURSOR_TYPE_HAMMER)
                {

                    mApp->ReanimationGet(this->mReanimCursorID)->Draw(g);
                    return;
                }
                if (CVar1 != CURSOR_TYPE_COBCANNON_TARGET)
                {
                    return;
                }
                // mBoard->MouseHitTest(mBoard->mPrevMouseX, mBoard->mPrevMouseY, &local_8);
                if (local_8.mObjectType != OBJECT_TYPE_NONE)
                {
                    return;
                }
                g->DrawImageCel(Sexy::IMAGE_COBCANNON_TARGET, -0xb, 7, 0);
                return;
            }
            pPVar4 = mApp->mZenGarden->GetPottedPlantInWheelbarrow();
        }
        iVar2 = mBoard->mBackground;
        if ((iVar2 != 6) && (iVar2 != 8))
        {
            mApp->mZenGarden->DrawPottedPlant(g, -22.0, -38.0, pPVar4, 1.0, true);
            return;
        }
        mApp->mZenGarden->DrawPottedPlant(g, -10.0, -10.0, pPVar4, 1.0, false);
        return;
    }
    g->DrawImage(Sexy::IMAGE_ZEN_MONEYSIGN, -0x11, -10);
    return;
}

void CursorObject::Die()
{
}