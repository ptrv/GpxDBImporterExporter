/*=======================================================
 Copyright (c) Peter Vasil, 2011
 =======================================================*/

#ifndef _PVLOGGER_H_
#define _PVLOGGER_H_

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# include <lmcons.h>
# define sprintf sprintf_s
# define USE_NEW_SECURE_TIME_FNS
#else
//# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
//# include <pwd.h>
#endif
#include <stdlib.h>
#include <sys/timeb.h>
#include <time.h>

#ifndef __GNUC__
# define __PRETTY_FUNCTION__ __FUNCTION__
#endif

#if defined __APPLE__
# define UInt32 uint32
#endif

#define PVL_DVAL			"DBG_VAL"
#define PVL_DSCOPE			"DBG_SCOPE"
#define PVL_VAL				"LOG_VAL"
#define PVL_SCOPE			"LOG_SCOPE"
#define PVL_DERROR			"DBG_ERROR"
#define PVL_ERROR			"LOG_ERROR"

class PVLogger {
private:
	PVLogger()
	{
	}
	~PVLogger()
	{
	}
	
public:
	static void outputError (const char* logType, const char* function, const String& message)
	{
		String tmpMsg;
		tmpMsg 
		<< logType 
		<< " ["
		<< getCurrenTimeString()
		<< "] : --> "
		<< String(function) 
		<< " \n" 
		<< message
		<< "\n";
		Logger::outputDebugString(tmpMsg);
	}
	static void logMessage (const char* logType, const char* function, const String& name, const String& message)
	{
		String tmpMsg;
		tmpMsg 
		<< logType 
		<< " ["
		<< getCurrenTimeString()
		<< "] : --> "
		<< String(function) 
		<< " \n"
		<< name 
		<< " : "
		<< message
		<< "\n";// << "<-------------------------";
		Logger::outputDebugString(tmpMsg);
	}
	static void logMessage (const char* logType, const char* function, const String& name, int message)
	{
		String tmpMsg;
		tmpMsg 
		<< logType 
		<< " ["
		<< getCurrenTimeString()
		<< "] : --> "
		<< String(function) 
		<< " \n"
		<< name 
		<< " : "
		<< message
		<< "\n";// << "<-------------------------";
		Logger::outputDebugString(tmpMsg);
	}
	static void logMessage (const char* logType, const char* function, const String& name, float message)
	{
		String tmpMsg;
		tmpMsg 
		<< logType 
		<< " ["
		<< getCurrenTimeString()
		<< "] : --> "
		<< String(function) 
		<< " \n"
		<< name 
		<< " : "
		<< message
		<< "\n";// << "<-------------------------";
		Logger::outputDebugString(tmpMsg);
	}
	static void logMessage (const char* logType, const char* function, const String& name, double message)
	{
		String tmpMsg;
		tmpMsg 
		<< logType 
		<< " ["
		<< getCurrenTimeString()
		<< "] : --> "
		<< String(function) 
		<< " \n"
		<< name 
		<< " : "
		<< message
		<< "\n";// << "<-------------------------";
		Logger::outputDebugString(tmpMsg);
	}
	static void logMessage (const char* logType, const char* function, const String& name, bool message)
	{
		String tmpMsg;		
		tmpMsg 
		<< logType 
		<< " ["
		<< getCurrenTimeString()
		<< "] --> "
		<< String(function) 
		<< " \n"
		<< name 
		<< " : "
		<< (message ? "true" : "false")
		<< "\n";// << "<-------------------------";
		Logger::outputDebugString(tmpMsg);
	}
	static void logMessage (const char* logType, const char* function)
	{
		String tmpMsg;		
		tmpMsg 
		<< logType 
		<< " ["
		<< getCurrenTimeString()
		<< "] --> "
		<< String(function) 
		<< " \n";
		Logger::outputDebugString(tmpMsg);
	}
private:
	/*
	 * Get current time in milliseconds with high resolution.
	 * Copied and modified from the implementation in Juce without high resultion.
	 * The high resolution implementation is missing there.
	 */
	static int64 currentTimeMillisHiRes()
	{
		static uint32 lastCounterResult = 0xffffffff;
		static int64 correction = 0;
		
		const uint32 now = (uint32)Time::getMillisecondCounterHiRes();
		
		// check the counter hasn't wrapped (also triggered the first time this function is called)
		if (now < lastCounterResult)
		{
			// double-check it's actually wrapped, in case multi-cpu machines have timers that drift a bit.
			if (lastCounterResult == 0xffffffff || now < lastCounterResult - 10)
			{
				// get the time once using normal library calls, and store the difference needed to
				// turn the millisecond counter into a real time.
#if JUCE_WIN32
				struct _timeb t;
#ifdef USE_NEW_SECURE_TIME_FNS
				_ftime_s (&t);
#else
				_ftime (&t);
#endif
				correction = (((int64) t.time) * 1000 + t.millitm) - now;
#else
				struct timeval tv;
				struct timezone tz;
				gettimeofday (&tv, &tz);
				correction = (((int64) tv.tv_sec) * 1000 + tv.tv_usec / 1000) - now;
#endif
			}
		}
		
		lastCounterResult = now;
		
		return correction + now;
	}
	
	static void getCurrentTime(int64 seconds, struct tm& currTime)
	{
		time_t now = (time_t)(seconds);
		
#if JUCE_WIN32
		localtime_s (&currTime, &now);
#else
		localtime_r (&now, &currTime);
#endif
	}
	static const String getCurrenTimeString()
	{
		int64 currTimeMillis = currentTimeMillisHiRes();
		struct tm currTime;
		getCurrentTime(currTimeMillis/1000,currTime);
		
		char buffer[20];
		sprintf(buffer, "%02d:%02d:%02d.%03d", currTime.tm_hour, currTime.tm_min, currTime.tm_sec, (int)(currTimeMillis%1000));
		return (String)buffer;
	}
	
};

// -----------------------------------------------------------------------------
// LOG Macros
// -----------------------------------------------------------------------------
#if defined (_DEBUG)

# define DBG_VAL(message)				PVLogger::logMessage(PVL_DVAL, __PRETTY_FUNCTION__, #message, message)

# define DBG_SCOPE()					PVLogger::logMessage(PVL_DSCOPE, __PRETTY_FUNCTION__)

# define DBG_ERROR(message)				PVLogger::outputError(PVL_DERROR, __PRETTY_FUNCTION__, message)

# define LOG_ERROR(message)				PVLogger::outputError(PVL_ERROR, __PRETTY_FUNCTION__, message)

# define LOG_VAL(message)				PVLogger::logMessage(PVL_VAL, __PRETTY_FUNCTION__, #message, message)


// -----------------------------------------------------------------------------
#else

# define DBG_VAL(message)

# define DBG_SCOPE()

# define DBG_ERROR(message)

# define LOG_VAL(message)				PVLogger::logMessage(PVL_VAL, __PRETTY_FUNCTION__, #message, message)

# define LOG_SCOPE()					PVLogger::logMessage(PVL_SCOPE, __PRETTY_FUNCTION__)

# define LOG_ERROR(message)				PVLogger::outputError(PVL_ERROR, __PRETTY_FUNCTION__, message)

#endif

#if defined __APPLE__
# undef UInt32
#endif

#if defined _WIN32
# undef sprintf
#endif

#endif // _PVLOGGER_H_