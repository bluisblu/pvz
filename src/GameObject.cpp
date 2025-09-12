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
    this->mApp = (LawnApp *)Sexy::gSexyAppBase;
    this->mBoard = this->mApp->mBoard;
}

bool GameObject::BeginDraw(Sexy::Graphics *gfx)
{
    if (this->mVisible == false)
    {
        return false;
    }
    gfx->mTransX += this->mX;
    gfx->mTransY += this->mY;
    return true;
}

void GameObject::EndDraw(Sexy::Graphics *gfx)
{
    gfx->mTransX -= this->mX;
    gfx->mTransY -= this->mY;
}
