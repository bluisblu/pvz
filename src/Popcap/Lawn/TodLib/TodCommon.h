#ifndef __TODLIB_TODCOMMON_H__
#define __TODLIB_TODCOMMON_H__

int TodVsnprintf(char *theBuffer, int theSize, const char *theFormat, char *theArgList);
int TodSnprintf(char *theBuffer, int theSize, const char *theFormat, ...);

#endif
