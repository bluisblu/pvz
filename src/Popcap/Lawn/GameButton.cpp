#include "GameButton.h"

void GameButton::SetFont(Sexy::Font *theFont)
{
    if (mFont)
        delete mFont;

    mFont = theFont->Duplicate();
}

void GameButton::DrawButtonImage(Sexy::Graphics *g, Sexy::Image *theImage, const Sexy::TRect<int> *theRect, int x,
                                 int y)
{
    if (theRect->mWidth != 0)
        g->DrawImage(mButtonImage, x + mButtonOffsetX, y + mButtonOffsetY, *theRect);

    else
        g->DrawImage(theImage, x + mButtonOffsetX, y + mButtonOffsetY);
}

void GameButton::SetDisabled(bool isDisabled)
{
    mDisabled = isDisabled;
}

bool GameButton::IsMouseOver()
{
    if (mIsOver && !mDisabled && !mBtnNoDraw)
    {
        return true;
    }
    return false;
}

void GameButton::Update()
{
    LawnApp *app = mApp;
    Sexy::WidgetManager *wm = app->mWidgetManager;

    // Mouse coordinates relative to parent
    int mouseX = wm->mLastMouseX;
    int mouseY = wm->mLastMouseY;
    if (mParentWidget)
    {
        mouseX -= mParentWidget->mX;
        mouseY -= mParentWidget->mY;
    }

    // Update hover state
    mIsOver = mouseX >= mX && mouseX < mX + mWidth && mouseY >= mY && mouseY < mY + mHeight;

    // Update down state
    mIsDown = (wm->mDownButtons & 5) != 0;

    // Disable if a dialog is open and focus is elsewhere
    Sexy::Widget *focus = wm->mFocusWidget;
    if ((!focus || focus != mParentWidget) && app->GetDialogCount() > 0)
    {
        mIsDown = false;
        mIsOver = false;
    }

    if (!mIsDown)
    {
        if (mIsOver)
        {
            // jump to fade-in block
        }
        else if (mOverAlpha > 0.0f)
        {
            if (mOverAlphaSpeed > 0.0f)
            {
                mOverAlpha -= mOverAlphaSpeed;
                if (mOverAlpha < 0.0f)
                    mOverAlpha = 0.0f;
                return;
            }
            mOverAlpha = 0.0f;
            return;
        }
    }

    if (!mIsOver)
        return;

    // Fade-in block
    if (mOverAlphaFadeInSpeed > 0.0f && mOverAlpha < 1.0f)
    {
        if (mOverAlphaFadeInSpeed <= 0.0f)
        {
            mOverAlpha = 1.0f;
            return;
        }
        mOverAlpha += mOverAlphaFadeInSpeed;
        if (mOverAlpha > 1.0f)
            mOverAlpha = 1.0f;
    }
}

void GameButton::Resize(int theX, int theY, int theWidth, int theHeight)
{
    mX = theX;
    mY = theY;
    mWidth = theWidth;
    mHeight = theHeight;
}
