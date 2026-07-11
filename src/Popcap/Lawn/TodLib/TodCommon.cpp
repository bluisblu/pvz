#include "Precompile.h"
#include <cmath>
#include <cstdarg>
#include <stdio.h>

#include "TodCommon.h"

bool TodAppCloseRequest()
{
    return false;
}

int TodVsnprintf(char *theBuffer, int theSize, const char *theFormat, char *theArgList)
{
    TOD_FUNCTION_PROLOG

    int result = _vsnprintf(theBuffer, theSize, theFormat, theArgList);
    if (result == -1)
    {
        theBuffer[theSize - 1] = 0;
        return theSize - 1;
    }
    return result;

    TOD_FUNCTION_EPILOG
}

int TodSnprintf(char *theBuffer, int size, const char *theFormat, ...)
{
    va_list theArgList;

    va_start(theArgList, theFormat);
    return TodVsnprintf(theBuffer, size, theFormat, theArgList);
}

int TodPickFromArray(int const *theArray, int theCount)
{
    // TOD_ASSERT(theCount > 0);
    return 0;
}

float TodCurveBounce(float theTime)
{
    float theTimea = 1.0f - (theTime + theTime);
    float theTimeb = fabs(theTimea);
    return (float)(1.0 - theTimeb);
}
