#include "LawnDialog.h"

LawnDialog::~LawnDialog()
{
    if (mReanimation)
        delete mReanimation;

    if (mLawnYesButton)
        delete mLawnYesButton;

    if (mLawnNoButton)
        delete mLawnNoButton;
}

int LawnDialog::GetLeft()
{
    return mBackgroundInsets.mLeft + mContentInsets.mLeft;
}

int LawnDialog::GetWidth()
{
    return mWidth - mContentInsets.mRight - mContentInsets.mLeft - mBackgroundInsets.mRight - mBackgroundInsets.mLeft;
}

int LawnDialog::GetTop()
{
    return mContentInsets.mTop + mBackgroundInsets.mTop + 99;
}

void LawnDialog::SetButtonDelay(int theDelay)
{
    mButtonDelay = theDelay;
    if (mLawnYesButton)
        mLawnYesButton->SetDisabled(true);
    if (mLawnNoButton)
        mLawnNoButton->SetDisabled(true);
}

void LawnDialog::Update()
{
    Sexy::Dialog::Update();
    if (mUpdateCnt == mButtonDelay)
    {
        if (mLawnYesButton)
            mLawnYesButton->SetDisabled(false);
        if (mLawnNoButton)
            mLawnNoButton->SetDisabled(false);
    }
}

void LawnDialog::KeyDown(Sexy::KeyCode theKey)
{
    if (theKey == Sexy::KEYCODE_SPACE || theKey == Sexy::KEYCODE_RETURN || theKey == Sexy::KEYCODE_F10 ||
        theKey == (Sexy::KEYCODE_KANJI | 0x40))
    {
        Sexy::Dialog::ButtonDepress(1000);
    }
    else if (theKey == Sexy::KEYCODE_ESCAPE || theKey == Sexy::KEYCODE_DECIMAL ||
             theKey == (Sexy::KEYCODE_CLEAR | Sexy::KEYCODE_RBUTTON | 0x40))
    {
        if (mLawnNoButton)
            Sexy::Dialog::ButtonDepress(1001);
    }
}
