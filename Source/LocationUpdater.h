/*==========================================================
 Copyright (c) Peter Vasil, 2011
 ==========================================================*/

#ifndef LOCATIONUPDATER_H
#define LOCATIONUPDATER_H

#include "includes.h"


class LocationUpdater : public ThreadWithProgressWindow
{
public:
    LocationUpdater(const String& dbPath, const char boundingsType);
    ~LocationUpdater();

    void run();
	const String& getStatus() const;
private:
	String m_dbPath;
	String m_status;
	char m_boundingsType;
};

#endif // LOCATIONUPDATER_H
