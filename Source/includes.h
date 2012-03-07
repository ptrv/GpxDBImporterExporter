/*==========================================================
 Copyright (c) Peter Vasil, 2011
 ==========================================================*/

#ifndef _DBIMPORTERHEADERS_
#define _DBIMPORTERHEADERS_

#define RC_COMPANY_STR "Peter Vasil, 2012"

#ifdef _WIN32
# include <windows.h>
#endif

#include "../JuceLibraryCode/JuceHeader.h"

#ifdef GIT_REV
#define BUILD_NUM GIT_REV
#else
#define BUILD_NUM "unknown"
#endif

#endif // _DBIMPORTERHEADERS_
