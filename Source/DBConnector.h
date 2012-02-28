/*==========================================================
 Copyright (c) Peter Vasil, 2011
 ==========================================================*/

#ifndef _DBCONNECTOR_
#define _DBCONNECTOR_

#include "includes.h"
#include "Data.h"

#include "sqlite3x.hpp"
using namespace sqlite3x;

class DBConnector
{
public:
	DBConnector(const String &database);
	~DBConnector();

	void setDatabase(const String &db);
	void setupDbConnection();
	void closeDbConnection();
    bool insertInitLocationData();
    bool insertInitLocationDataGML();
    bool insertLocationData(Array<GpsLocation>& locs);
    bool checkIfCityExists(const String& cityname);
	bool checkIfFileExists(const String& md5hash);
	bool checkIfFileNameExists(const String& filename);
	bool checkIfGpsDataExsist(const String& timedate, int user);
	bool checkIfUserExists(const String& username);
	bool insertUser(int userid, const String& username);
	bool getAvailableUsers(Array<String>& users);
	bool getLastId(int& lastRowId, const String& tableName);
	bool getLastSegmentId(int& segId, int user);
	bool createNewDb();
	bool getNameId(int& nameId, const String& name);
	bool getGpsLocations(Array<GpsLocation>& locations);
	bool insertFileName(int& fileid, const String& filename, const String& md5);
	bool insertGpsData(const GpsData& gpsData);
	void beginTransaction();
	bool commitTransaction();
	bool executeSqlScript(const File& sqlFile);
	bool executeSqlString(const String& sqlString);
	bool getGpsDataUnknownLocation(Array<GpsData>& gpsDataVec);
	bool updateGpsDataLocation(int gpsdataid, int location);
	bool getGpsDataForExport(Array<GpsData>& gpsDatas, GpsMinMax& gpsMinMax, const String& query);
	bool getCountTable(const String& tablename, int& count);
	bool getTableNames(StringArray& names);

private:
	String m_database;
	sqlite3_connection* m_dbconn;
	sqlite3_transaction* m_trans;
};

#endif // _DBCONNECTOR_
