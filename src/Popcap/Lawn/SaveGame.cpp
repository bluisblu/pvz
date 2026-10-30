#include "SaveGame.h"

void SaveGameContext::SyncInt(int &theInt)
{
    if (mReading)
    {
        unsigned int bytesLeft = (mBuffer.mDataBitSize - mBuffer.mReadBitPos + 7) / 8;

        if (bytesLeft < 4)
        {
            mFailed = true;
        }

        if (mFailed)
        {
            theInt = 0;
        }
        else
        {
            theInt = mBuffer.ReadLong();
        }
    }
    else
    {
        mBuffer.WriteLong(theInt);
    }
}

SaveGameContext::~SaveGameContext()
{
}
