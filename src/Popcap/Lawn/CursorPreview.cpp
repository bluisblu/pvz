#include "CursorPreview.h"
#include "Board.h"
#include "DataArray.h"
#include "LawnApp.h"
#include "Plant.h"
#include "ZenGarden.h"

float PlantDrawHeightOffset(class Board *theBoard, class Plant *thePlant, enum SeedType theSeedType,
                            int theCol, int theRow);

CursorPreview::CursorPreview() : GameObject()
{
    mX       = 0;
    mY       = 0;
    mWidth   = 80;
    mHeight  = 80;
    mGridX   = 0;
    mGridY   = 0;
    mVisible = false;
}

void CursorPreview::Update()
{
    if (mApp->mGameScene != 3)
    {
        mVisible = false;
        return;
    }
    if (!mApp->mWidgetManager->mMouseIn)
    {
        mVisible = false;
        return;
    }

    SeedType seedType = mBoard->GetSeedTypeInCursor();
    int mouseX        = mApp->mWidgetManager->mLastMouseX;
    int mouseY        = mApp->mWidgetManager->mLastMouseY;

    mGridX = mBoard->PlantingPixelToGridX(mouseX, mouseY, seedType);
    mGridY = mBoard->PlantingPixelToGridY(mouseX, mouseY, seedType);

    if (mGridX >= 0 && mGridX < 9 && mGridY >= 0 && mGridY < 6)
    {

        if (mBoard->IsPlantInCursor() && mBoard->CanPlantAt(mGridX, mGridY, seedType) == 0)
        {
            mX       = mBoard->GridToPixelX(mGridX, mGridY);
            mY       = mBoard->GridToPixelY(mGridX, mGridY);
            mVisible = true;
            return;
        }
        else if (mBoard->mCursorObject->mCursorType == 0x10 &&
                 mApp->mZenGarden->GetPottedPlantInWheelbarrow() != NULL &&
                 mBoard->CanPlantAt(mGridX, mGridY, seedType) == 0)
        {
            mX       = mBoard->GridToPixelX(mGridX, mGridY);
            mY       = mBoard->GridToPixelY(mGridX, mGridY);
            mVisible = true;
            return;
        }
    }

    mVisible = false;
}

void CursorPreview::Draw(Sexy::Graphics *g)
{
    SeedType seedType = mBoard->GetSeedTypeInCursor();

    if (seedType == SEED_NONE)
    {
        return;
    }

    g->SetColorizeImages(true);

    g->SetColor(Sexy::Color(255, 255, 255, 100));

    CursorType cursorType    = mBoard->mCursorObject->mCursorType;
    PottedPlant *pottedPlant = NULL;

    if (cursorType == CURSOR_TYPE_WHEEELBARROW || cursorType == CURSOR_TYPE_PLANT_FROM_WHEEL_BARROW)
    {
        pottedPlant = mApp->mZenGarden->GetPottedPlantInWheelbarrow();
    }
    else if (cursorType == CURSOR_TYPE_PLANT_FROM_GLOVE)
    {
        Plant *plant = mBoard->mPlants.DataArrayGet(mBoard->mCursorObject->mGlovePlantID);
        pottedPlant  = mApp->GetPottedPlantByIndex(plant->mPottedPlantIndex);
    }

    if (pottedPlant != NULL)
    {
        bool drawShadow           = true;
        BackgroundType background = mBoard->mBackground;

        if (background == BACKGROUND_MUSHROOM_GARDEN || background == BACKGROUND_ZOMBIQUARIUM)
        {
            drawShadow = false;
        }

        mApp->mZenGarden->DrawPottedPlant(g, 0.0f, 0.0f, pottedPlant, 1.0f, drawShadow);
    }
    else
    {
        float offsetX = 0.0f;
        float offsetY = 0.0f;

        if (mApp->IsIZombieLevel())
        {
            offsetY = PlantDrawHeightOffset(mBoard, NULL, seedType, mGridX, mGridY);
            if (seedType == 0x49)
            {
                offsetY -= 30.0f;
            }
            offsetY -= 78.0f;
            offsetX = -49.0f;
        }
        else
        {
            offsetY = PlantDrawHeightOffset(mBoard, NULL, seedType, mGridX, mGridY);
            offsetX = 0.0f;
        }

        CursorObject *plantData = mBoard->mCursorObject;
        Plant::DrawSeedType(g, plantData->mType, plantData->mImitaterType, VARIATION_NORMAL,
                            offsetX, offsetY);
    }

    if (mApp->mGameMode == GAMEMODE_CHALLENGE_COLUMN)
    {
        for (int i = 0; i < 6; ++i)
        {
            if (i != mGridY && mBoard->CanPlantAt(mGridX, i, seedType) == 0)
            {
                float heightOffset = PlantDrawHeightOffset(mBoard, NULL, seedType, mGridX, i);
                float finalY       = (float)(i - mGridY) * 85.0f + heightOffset;

                CursorObject *plantData = mBoard->mCursorObject;
                Plant::DrawSeedType(g, plantData->mType, plantData->mImitaterType, VARIATION_NORMAL,
                                    0.0f, finalY);
            }
        }
    }

    g->SetColorizeImages(false);
}
