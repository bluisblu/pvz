#ifndef __SAVEGAME_H__
#define __SAVEGAME_H__

#include "TodLib/Reanimator.h"
#include "TodLib/TodParticle.h"
#include "TodLib/Trail.h"

#include "SexyAppFramework/Buffer.h"
#include "SexyAppFramework/Image.h"

class SaveGameContext
{
  public:
    Sexy::Buffer mBuffer; // 0x0
    bool mFailed;         // 0x20
    bool mReading;        // 0x21
    int ByteLeftToRead();
    void SyncBytes(void *, int);
    void SyncInt(int &);
    void SyncUint(unsigned int &);
    void SyncReanimationDef(ReanimatorDefinition *&);
    void SyncParticleDef(TodParticleDefinition *&);
    void SyncTrailDef(TrailDefinition *&);
    void SyncImage(Sexy::Image *&);
    ~SaveGameContext();
};

#endif
