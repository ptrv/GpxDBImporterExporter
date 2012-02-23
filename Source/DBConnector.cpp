/*==========================================================
 Copyright (c) Peter Vasil, 2011
 ==========================================================*/

#include "DBConnector.h"
#include "includes.h"
#include "GMLParser.h"

#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

#include "sqlite3x.hpp"
using namespace sqlite3x;

// --------------------------------------------------------------------------------------
#define CATCHDBERRORS																	\
	catch(exception &ex)																\
	{																					\
		String msg = "Database error: ";												\
		DBG((msg << ex.what()).toUTF8().getAddress());							\
	}																					\
// --------------------------------------------------------------------------------------
#define CATCHDBERRORSQ(query)															\
	catch(exception &ex)																\
	{																					\
		String msg = "Database error: ";												\
		msg << ex.what() << " \nquery: " << query;										\
		DBG(msg.toUTF8().getAddress());											\
	}																					\
// --------------------------------------------------------------------------------------


DBConnector::DBConnector(const String &database)
:
m_database(database),
m_dbconn(NULL),
m_trans(NULL)
{
}

DBConnector::~DBConnector()
{
	delete m_dbconn;
	delete m_trans;
}

void DBConnector::setDatabase(const String &db)
{
	m_database = db;
}

void DBConnector::setupDbConnection()
{
	try {
		m_dbconn = new sqlite3_connection(m_database.toUTF8().getAddress());
	}
	CATCHDBERRORS
}

void DBConnector::closeDbConnection()
{
	try {
		m_dbconn->close();
		m_dbconn = NULL;
	}
	CATCHDBERRORS
}
const String GpsData::getInsertList() const
{
	String names = "gpsdataid";
	String values;
	values << "'" << gpsdataid << "'";
	names += ",latitude";
	values <<  ",'" << latitude << "'";
	names += ",longitude";
	values << ",'" << longitude << "'";
	names += ",elevation";
	values << ",'" << elevation << "'";
	names += ",time";
	values << ",'" << time << "'";
	names += ",segment";
	values << ",'" << segment << "'";
	names += ",user";
	values << ",'" << user << "'";
	names += ",file";
	values << ",'" << file << "'";
	names += ",location";
	values << ",'" << location << "'";

	String res = "(";
	res += names;
	res += ") VALUES (";
	res += values;
	res += ");";
	return res;
}
	bool DBConnector::createNewDb()
{
	bool result = false;
	String createTableFile(BinaryData::create_tables_sql);
	Array<String> tmpSqlQueries;
	String tmpStr = "";

	for (int i = 0; i < createTableFile.length(); ++i) {
		if (createTableFile[i] != ';')
		{
			tmpStr += createTableFile[i];
		}
		else
		{
			tmpSqlQueries.add(tmpStr);
			tmpStr = "";
		}
	}

	try {
		sqlite3_transaction trans(*m_dbconn);
		{
			for (unsigned int i = 0; i < tmpSqlQueries.size(); ++i) {
				sqlite3_command cmd(*m_dbconn, std::string(tmpSqlQueries[i].toUTF8().getAddress()));
				cmd.executenonquery();
				//m_dbconn->executenonquery(tmpSqlQueries[i].toUTF8().getAddress());
			}
		}
		trans.commit();
		result = true;
    }
    CATCHDBERRORS;
	return result;
}

bool DBConnector::insertLocationData()
{
    bool result = false;
    String locationsStr((CharPointer_UTF8(BinaryData::locations_csv)));
    Array<String> tmpLocations;
    String tmpStr = "";
    for (int i = 0; i < locationsStr.length(); ++i) {
        if (locationsStr[i] != '\n')
        {
            tmpStr << locationsStr[i];
        }
        else
        {
            tmpLocations.add(tmpStr);
            tmpStr = "";
        }
    }
    try{
        sqlite3_transaction trans(*m_dbconn);
        {

            for (unsigned int i = 1; i < tmpLocations.size(); ++i) {
                String query = "INSERT INTO 'location' ";
                query << "(locationid,city,country,longitude,latitude,radius)VALUES(";
                query << tmpLocations[i];
                query << ");";
                sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
                cmd.executenonquery();
            }

        }
        trans.commit();
        result = true;
    }
    CATCHDBERRORS
    return result;

}

bool DBConnector::insertLocationDataGML()
{
    bool result = false;

    String gmlFile = CharPointer_UTF8(BinaryData::citydefs_gml);
    Array<GpsLocation> locs = GMLParser::parse(gmlFile);

    Array<String> tmpLocations;
    String tmpStr = "";
    tmpLocations.add("1,'Unknown','Unknown','0.0,0.0 0.0,0.0 0.0,0.0 0.0,0.0 0.0,0.0'");
    for (int i = 0; i < locs.size(); ++i) {
    	tmpStr << locs[i].index+1 << ",\"" << locs[i].city << "\",";
    	tmpStr << "\"" << locs[i].country << "\",\"";
    	for (int j = 0; j < locs[i].polygon.size(); ++j) {
    		const Point<double>& p = locs[i].polygon[j];
    		tmpStr << p.x << "," << p.y;
    		if(j < locs[i].polygon.size()-1)
    		{
    			tmpStr << " ";
    		}
		}
    	tmpStr << "\"";
    	tmpLocations.add(tmpStr);
    	tmpStr = "";
    }
    try{
        sqlite3_transaction trans(*m_dbconn);
        {

            for (unsigned int i = 0; i < tmpLocations.size(); ++i) {
                String query = "INSERT INTO 'location' ";
                query << "(locationid,city,country,polygon)VALUES(";
                query << tmpLocations[i];
                query << ");";
                sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
                cmd.executenonquery();
            }

        }
        trans.commit();
        result = true;
    }
    CATCHDBERRORS
    return result;

}

bool DBConnector::checkIfUserExists(const String& username)
{
	bool result = false;
	try{
		sqlite3_transaction trans(*m_dbconn);
		{
			String query;
			query << "select userid from user where name = '" << username << "';";
			sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
			sqlite3_reader reader = cmd.executereader();
			while (reader.read()) {
				result = true;
				break;
			}
		}
		trans.commit();
	}
	CATCHDBERRORS
    return result;

}
bool DBConnector::insertUser(int userid, const String& username)
{
	bool result = false;
	try {
		sqlite3_transaction trans(*m_dbconn);
		{
			String query = String::empty;
			query << "INSERT INTO user (userid, name) VALUES (" << userid << ",'" << username << "');";
			sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
			cmd.executenonquery();
		}
		trans.commit();
		result = true;
	}
	CATCHDBERRORS
    return result;

}
bool DBConnector::getAvailableUsers(Array<String>& users)
{
	bool result = false;
	users.clear();
	try {
		sqlite3_transaction trans(*m_dbconn);
		{
			String query = "Select name from user;";
			sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
			sqlite3_reader reader = cmd.executereader();
			while (reader.read()) {
				users.add(String((reader.getstring(0)).c_str()));
			}
		}
		trans.commit();
		result = true;
	}
	CATCHDBERRORS
	return result;

}
bool DBConnector::getLastId(int& lastRowId, const String& tableName)
{
	bool result = false;
	lastRowId = -1;
	try {
		sqlite3_transaction trans(*m_dbconn);
		{
			String query;
			query << "Select seq from sqlite_sequence where name = '" << tableName << "';";
			sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
			//sqlite3_reader reader = cmd.executereader();
			//lastRowId = reader.getint(0);
			lastRowId = cmd.executeint();
		}
		trans.commit();
		result = true;
	}
	CATCHDBERRORS
	return result;
}

bool DBConnector::getLastSegmentId(int& segId, int user)
{
	bool result = false;
	try{
		sqlite3_transaction trans(*m_dbconn);
		{
			String query;
			query << "SELECT segment FROM gpsdata WHERE user = " << user << " ORDER BY segment DESC LIMIT 1";
			sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
			segId = cmd.executeint();
		}
		trans.commit();
		result = true;
	}
	CATCHDBERRORS
	return result;
}
bool DBConnector::getNameId(int& nameId, const String& name)
{
	bool result = false;
	try{
		sqlite3_transaction trans(*m_dbconn);
		{
			String query;
			query << "select userid from user where name = '" << name << "';";
			sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
			nameId = cmd.executeint();
		}
		trans.commit();
		result = true;
	}
	CATCHDBERRORS
	return result;
}

bool DBConnector::getGpsLocations(Array<GpsLocation>& locations)
{
	bool result = false;
	try{
		sqlite3_transaction trans(*m_dbconn);
		{
			String query;
			query << "select * from location;";
			sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
			sqlite3_reader reader = cmd.executereader();
			locations.clear();
			while (reader.read()) {
				GpsLocation location;
				location.index = reader.getint(0);
				location.city = String(CharPointer_UTF8(reader.getstring(1).data()));
//                DBG(location.city);
				location.country = String(CharPointer_UTF8(reader.getstring(2).data()));
				location.longitude = reader.getdouble(3);
				location.latitude = reader.getdouble(4);
				location.radius = reader.getdouble(5);
				locations.add(location);
//				DBG_VAL(location.index);
//				DBG_VAL(location.city);
//				DBG_VAL(location.country);
//				DBG_VAL(location.longitude );
//				DBG_VAL(location.latitude);
//				DBG_VAL(location.radius);
			}
		}
		trans.commit();
		result = true;
	}
	CATCHDBERRORS
	return result;
}
bool DBConnector::checkIfFileExists(const String& md5hash)
{
	bool result = false;
	try{
		sqlite3_transaction trans(*m_dbconn);
		{
			String query;
			query << "select fileid from file where md5hash = '" << md5hash << "';";
			sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
			sqlite3_reader reader = cmd.executereader();
			while (reader.read()) {
				result = true;
				break;
			}
		}
		trans.commit();
	}
	CATCHDBERRORS
	return result;

}
bool DBConnector::checkIfFileNameExists(const String& filename)
{
	bool result = false;
	try{
		sqlite3_transaction trans(*m_dbconn);
		{
			String query;
			query << "select fileid from file where filename = '" << filename << "';";
			sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
			sqlite3_reader reader = cmd.executereader();
			while (reader.read()) {
				result = true;
				break;
			}
		}
		trans.commit();
	}
	CATCHDBERRORS
	return result;

}
bool DBConnector::insertFileName(int& fileid, const String& filename, const String& md5)
{
	bool result = false;
	try{
		sqlite3_transaction trans(*m_dbconn);
		{
			String query;
			query << "INSERT INTO file (fileid, filename, md5hash) VALUES (" << fileid << ",'" << filename << "','" << md5 << "');";
			sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
			cmd.executenonquery();
		}
		trans.commit();
		result = true;
	}
	CATCHDBERRORS
	return result;
}

bool DBConnector::checkIfGpsDataExsist(const String& timedate, int user)
{
	bool result = false;
	try{
		{
			String query;
			query << "SELECT time FROM gpsdata WHERE time = '" << timedate << "' AND user = " << user << ";";
			sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
			sqlite3_reader reader = cmd.executereader();
			while (reader.read()) {
				result = true;
				break;
			}
		}
	}
	CATCHDBERRORS
	return result;
}
void DBConnector::insertGpsData(const GpsData& gpsData)
{
	String query;
	try{

		query << "INSERT INTO gpsdata " << gpsData.getInsertList();// <<  ")";
		sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
		cmd.executenonquery();
	}
	CATCHDBERRORSQ(query)
	//DBG_VAL(query);
}

void DBConnector::beginTransaction()
{
	try{
		m_trans = new sqlite3_transaction(*m_dbconn);
	}
	CATCHDBERRORS
}

bool DBConnector::commitTransaction()
{
	bool result = false;
	try {
		m_trans->commit();
		result = true;
		m_trans = NULL;
	}
	CATCHDBERRORS
	return result;

}
bool DBConnector::executeSqlScript(const File& sqlFile)
{
	bool result = false;
	String sqlScriptString = sqlFile.loadFileAsString();
	//DBG_VAL(sqlScriptString);
	Array<String> tmpSqlQueries;
	String tmpStr = "";

	for (int i = 0; i < sqlScriptString.length(); ++i) {
		if (sqlScriptString[i] != ';')
		{
			tmpStr += sqlScriptString[i];
		}
		else
		{
			tmpSqlQueries.add(tmpStr);
			tmpStr = "";
		}
	}

	
//		sqlite3_transaction trans(*m_dbconn);
//		{

        for (unsigned int i = 0; i < tmpSqlQueries.size(); ++i) {
			try {
			sqlite3_command cmd(*m_dbconn, std::string(tmpSqlQueries[i].toUTF8().getAddress()));
			//DBG_VAL(tmpSqlQueries[i]);
			cmd.executenonquery();
			}
			CATCHDBERRORS
			result = true;
		}
//		}
//		trans.commit();
		//result = true;
//    }
    

	return result;
}

bool DBConnector::getGpsDataUnknownLocation(Array<GpsData>& gpsDataVec)
{
    bool result = false;
    gpsDataVec.clear();
    try
    {
        sqlite3_transaction trans(*m_dbconn);
        {
            String query = "SELECT gpsdataid, latitude, longitude, time, elevation, segment, user, file, location ";
            query += "FROM gpsdata WHERE location = 1;";
            sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
            sqlite3_reader reader = cmd.executereader();
            while (reader.read()) {
                GpsData gpsData;
                String timestamp = reader.getstring(3).c_str();
                gpsData.setGpsData(reader.getint(0),
                                   reader.getdouble(1),
                                   reader.getdouble(2),
                                   timestamp,
                                   reader.getdouble(4),
                                   reader.getint(5),
                                   reader.getint(6),
                                   reader.getint(7),
                                   reader.getint(8));

                gpsDataVec.add(gpsData);
            }
        }
        trans.commit();
        result = true;
    }
    CATCHDBERRORS
    return result;
}

bool DBConnector::updateGpsDataLocation(int gpsdataid, int location)
{
    bool result = false;

    try
    {
        sqlite3_transaction trans(*m_dbconn);
        {
            String query = "UPDATE gpsdata SET location = '";
            query << location;
            query << "' ";
            query << "WHERE gpsdataid = '";
            query << gpsdataid;
            query << "';";
            sqlite3_command cmd(*m_dbconn, std::string(query.toUTF8().getAddress()));
            cmd.executenonquery();
        }
        trans.commit();
        result = true;
    }
    CATCHDBERRORS
    return result;
}

bool DBConnector::getGpsDataForExport(Array<GpsData>& gpsDatas, GpsMinMax& gpsMinMax, const String& query)
{
	bool res = false;
	String basicQuery = "SELECT a.gpsdataid AS gpsdataid, a.latitude AS latitude, \
						  a.longitude AS longitude, a.time AS time, a.elevation AS elevation, \
						  a.segment AS segment, a.user AS user, a.file AS file, \
						  c.city AS city, b.name AS name \
						  FROM gpsdata AS a \
						  JOIN user AS b ON (a.user = b.userid) \
                          JOIN location AS c ON (a.location = c.locationid) ";
	String queryStr = basicQuery;
	queryStr.append(query, query.length() + 10);
	queryStr.append(" ORDER BY datetime(time);", 30);
    DBG(queryStr);
    
	try {
		sqlite3_command cmd(*m_dbconn, queryStr.toUTF8().getAddress());
		sqlite3_reader reader=cmd.executereader();
		
		while (reader.read())
		{
			GpsData gpsData;
			String trkTime = reader.getstring(3).c_str();
			gpsData.setGpsData(reader.getint(0), 
							   reader.getdouble(1), 
							   reader.getdouble(2), 
							   trkTime, 
							   reader.getdouble(4), 
							   reader.getint(5), 
							   reader.getint(6), 
							   reader.getint(7), 
							   reader.getint(8));
			gpsDatas.add(gpsData);
		}
		
		// -----------------------------------------------------------------------------
		// min max
		// -----------------------------------------------------------------------------
		int posS = queryStr.indexOf("FROM");
		int posE = queryStr.indexOf(" ORDER");
		
		String queryMinMax = "SELECT min(a.longitude), max(a.longitude), min(a.latitude), max(a.latitude) ";
		queryMinMax += queryStr.substring(posS, posE);
		
		//DBG_VAL(queryMinMax);
		
		sqlite3_command cmd2(*m_dbconn, std::string(queryMinMax.toUTF8().getAddress()));
		sqlite3_reader readerMinMax=cmd2.executereader();
		
		while(readerMinMax.read())
		{
			gpsMinMax.minLon = readerMinMax.getdouble(0);
			gpsMinMax.maxLon = readerMinMax.getdouble(1);
			gpsMinMax.minLat = readerMinMax.getdouble(2);
			gpsMinMax.maxLat = readerMinMax.getdouble(3);			
		}

		res = true;
	}
	CATCHDBERRORS
	return res;
}
