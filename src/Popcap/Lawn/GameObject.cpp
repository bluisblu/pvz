#include "SexyAppFramework/SexyAppBase.h"

#include "Board.h"
#include "GameObject.h"

GameObject::GameObject()
{
    mX = 0;
    mY = 0;
    mWidth = 0;
    mHeight = 0;
    mVisible = true;
    mRow = -1;
    mRenderOrder = 400000;
    mApp = (LawnApp *)Sexy::gSexyAppBase;
    mBoard = mApp->mBoard;
}

bool GameObject::BeginDraw(Sexy::Graphics *gfx)
{
    if (mVisible == false)
    {
        return false;
    }
    gfx->mTransX += mX;
    gfx->mTransY += mY;
    return true;
}

void GameObject::EndDraw(Sexy::Graphics *gfx)
{
    gfx->mTransX -= mX;
    gfx->mTransY -= mY;
}
