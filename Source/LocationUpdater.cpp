/*==========================================================
 Copyright (c) Peter Vasil, 2011
 ==========================================================*/

#include "LocationUpdater.h"
#include "DBConnector.h"
#include "HelperFunctions.h"

LocationUpdater::LocationUpdater(const String& dbPath)
:
ThreadWithProgressWindow("Busy...", true, false),
m_dbPath(dbPath),
m_status(String::empty)
{
    //ctor
}

LocationUpdater::~LocationUpdater()
{
    //dtor
}

const String& LocationUpdater::getStatus() const
{
	return m_status;
}

void LocationUpdater::run()
{
    DBConnector* dbCon = new DBConnector(m_dbPath);
    dbCon->setupDbConnection();

    Array<GpsData> gpsDataVec;
    Array<GpsLocation> gpsLocationVec;

    dbCon->getGpsDataUnknownLocation(gpsDataVec);
    dbCon->getGpsLocations(gpsLocationVec);

    setProgress(0.0);
	int k = 0;
    for(unsigned int i = 0; i < gpsDataVec.size(); ++i)
    {
        int res = Helper::findLocation(gpsLocationVec,
                               gpsDataVec[i].getLongitude(),
                               gpsDataVec[i].getLatitude());

        if (res != 0)
        {
            dbCon->updateGpsDataLocation(gpsDataVec[i].getGpsDataId(), res);
			++k;
        }
        setProgress((double)i / gpsDataVec.size());
    }
    dbCon->closeDbConnection();
	m_status = "Updated locations! Changed ";
	m_status << k;
	m_status << " GpsData entries.";
}
