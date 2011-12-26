/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file, created by The Introjucer 3.0.0
   Do not edit anything in this file!

*/

#include "BinaryData.h"


const char* BinaryData::getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + *resourceNameUTF8++;

    switch (hash)
    {
        case 0xb1f7f017:  numBytes = BinaryData::create_tables_sqlSize; return BinaryData::create_tables_sql;
        case 0xcc1fbf05:  numBytes = BinaryData::insert_predefineddata_sqlSize; return BinaryData::insert_predefineddata_sql;
        default: break;
    }

    numBytes = 0;
    return 0;
}


//================== create_tables.sql ==================
static const unsigned char temp_9a9efcd5[] =
"CREATE TABLE user (\n"
"\tuserid INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\n"
"\tname TEXT NOT NULL\n"
");\n"
"CREATE TABLE file (\n"
"\tfileid INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\n"
"\tfilename TEXT NOT NULL,\n"
"\tmd5hash TEXT NOT NULL\n"
");\n"
"CREATE TABLE gpsdata (\n"
"\tgpsdataid INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\n"
"\tlocation INTEGER UNSIGNED NOT NULL,\n"
"\tuser INTEGER UNSIGNED NOT NULL,\n"
"\tlatitude REAL NOT NULL,\n"
"\tlongitude REAL NOT NULL,\n"
"\ttime NUMERIC NOT NULL,\n"
"\televation REAL NOT NULL,\n"
"\tsegment INTEGER UNSIGNED NOT NULL,\n"
"\tfile INTEGER UNSIGNED NOT NULL,\n"
"\tFOREIGN KEY (user) REFERENCES user (userid),\n"
"\tFOREIGN KEY (location) REFERENCES location (locationid),\n"
"\tFOREIGN KEY (file) REFERENCES file (fileid),\n"
"\tUNIQUE (user, latitude, longitude, time)\n"
");\n"
"CREATE TABLE location (\n"
"\tlocationid INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\n"
"\tcity INTEGER UNSIGNED NOT NULL,\n"
"\tcountry INTEGER UNSIGNED NOT NULL,\n"
"\tlongitude REAL NOT NULL,\n"
"\tlatitude REAL NOT NULL,\n"
"\tradius REAL NOT NULL,\n"
"\tUNIQUE (city, country, longitude, latitude )\n"
");";

const char* BinaryData::create_tables_sql = (const char*) temp_9a9efcd5;

//================== insert_predefineddata.sql ==================
static const unsigned char temp_d6af8ec3[] =
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Unknown', 'Unknown', 0.0, 0.0, 0.0);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Berlin', 52.51, 13.37, 0.25);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'London', 51.5, -0.1, 0.25);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Luton', 51.85, -0.4, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Stansted', 51.885, 0.235, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Belgium', 'Kortrijk', 50.85, 3.25, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Arnside', 54.199, -2.832, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Kendal', 54.326069, -2.745048, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Burham', 51.32971, 0.48308, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Windermere', 54.3761, -2.9076, 0.04);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Nottingham', 52.95, -1.2, 0.15);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Belgium', 'Brussels', 50.846667, 4.3525, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Belgium', 'Leuven', 50.883333, 4.7, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Belgium', 'Ghent', 51.05, 3.733333, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Manchester', 53.466667, -2.233333, 0.15);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Switzerland', 'Zurich', 47.35, 8.55, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Bristol', 51.45, -2.6, 0.15);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Austria', 'Graz', 47.070278, 15.438889, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Austria', 'Vienna', 48.208333, 16.373056, 0.21);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Spain', 'Barcelona', 41.35, 2.15, 0.15);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Potsdam', 52.4, 13.06, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Luebben', 51.95, 13.9, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Hamburg', 53.583, 9.983, 0.15);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Kursdorf', 51.423889, 12.236389, 0.06);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Leipzig', 51.333333, 12.383333, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Brighton', 50.842941, -0.131312, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('England', 'Lewes', 50.875627, 0.017855, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Wittenberge', 53, 11.694, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Brandenburg', 52.412, 12.552, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Cologne', 50.9413, 6.9583, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Dusseldorf', 51.233333, 6.783333, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Essen', 51.450833, 7.013056, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Frankfurt(Oder)', 52.35, 14.55, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Calgary', 51.1, -114.1, 0.2);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Banff', 'Banff', 51.15, -115.55, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Schwedt', 53.05, 14.266667, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Luebeck', 53.869722, 10.686389, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Magdeburg', 52.133333, 11.616667, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Austria', 'Krems', 48.410833, 15.610278, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Czech Republic', 'Prague', 50.1, 14.4, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Cardiff', 51.485278, -3.186667, 0.15);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Newport(Pembrokeshire)', 52.01975, -4.83607, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Denmark', 'Copenhagen', 55.65, 12.6, 0.15);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Ludlow', 52.3681, -2.7176, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Newcastle upon Tyne', 54.974, -1.6132, 0.15);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Glasgow', 55.858, -4.259, 0.15);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Aberdeen', 57.15, -2.15, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Exeter', 50.7218, -3.533617, 0.15);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Plymouth', 50.371397, -4.142431, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('UK', 'Leeds', 53.799722, -1.549167, 0.15);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Germany', 'Schoenberg', 50.9, 12.45, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Japan', 'Tokyo', 35.65, 139.95, 0.45);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('USA', 'New York', 40.716667, -74, 0.25);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('USA', 'San Francisco', 37.7793, -122.4192, 0.25);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Spain', 'La Bisbal d Emporda', 41.96, 3.040556, 0.06);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Spain', 'Palamos', 41.85, 3.133333, 0.06);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Spain', 'Palafrugell', 41.919167, 3.165278, 0.06);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Spain', 'Fornells', 41.939, 3.214, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Spain', 'Begur', 41.95, 3.216667, 0.05);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Spain', 'Figueres', 42.266667, 2.965, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Spain', 'Cadaques', 42.283333, 3.283333, 0.1);\n"
"INSERT INTO location (country, city, latitude, longitude, radius) VALUES ('Finland', 'Kuopio', 62.8925, 27.678333, 0.06);\n";

const char* BinaryData::insert_predefineddata_sql = (const char*) temp_d6af8ec3;
