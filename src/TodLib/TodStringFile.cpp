#include "TodStringFile.h"

#include "../SexyAppFramework/Common.h"
#include "../SexyAppFramework/Insets.h"

void TodStringListSetColors(TodStringListFormat *theFormats, int theCount)
{
    gTodStringFormats = theFormats;
    gTodStringFormatCount = theCount;
}

void TodWriteStringSetFormat(const char *theFormat, TodStringListFormat *theCurrentFormat)
{
    for (int i = 0; i < gTodStringFormatCount; ++i)
    {
        const TodStringListFormat &candidate = gTodStringFormats[i];

        if (strncmp(theFormat, candidate.mFormatName, strlen(candidate.mFormatName)) == 0)
        {
            if (candidate.mNewFont)
                theCurrentFormat->mNewFont = candidate.mNewFont;

            if (candidate.mNewColor != Sexy::Color(0, 0, 0, 0))
                theCurrentFormat->mNewColor = candidate.mNewColor;

            theCurrentFormat->mLineSpacingOffset = candidate.mLineSpacingOffset;
            theCurrentFormat->mFormatFlags = candidate.mFormatFlags;

            return;
        }
    }
}
