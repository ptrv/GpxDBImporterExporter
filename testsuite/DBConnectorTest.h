
#ifndef _DBCONNECTORTEST_H_
#define _DBCONNECTORTEST_H_

class DBConnectorTest : public UnitTest {
public:
	DBConnectorTest() : UnitTest("DBConnector") {}

	void runTest()
	{
		String userName = "John";

		String gpxMD5 = "24e0b307d905c2a2b6abc3945cdd8078";
		String gpxName = "test.gpx";
		String gpxPathRel = "../../../testsuite/" + gpxName;
		File gpxFile = File::getCurrentWorkingDirectory().getChildFile(gpxPathRel);
		String dbPath = File::getSpecialLocation(File::tempDirectory).getFullPathName();
		dbPath << "/test.db";
		File dbFile(dbPath);
		if(dbFile.existsAsFile())
			dbFile.deleteFile();

		DBConnector* db = new DBConnector(dbPath);
		db->setupDbConnection();

		beginTest("Create new database");

		expect(db->createNewDb(), "create new db");
		expect(db->insertInitLocationDataGML(), "Insert predefined data");

		beginTest("Insert user");

		int lastRowId = 0;
		int count = -1;
		expect(db->getCountTable("user", count));
		expectEquals(count, 0);
//		expect(! db->getLastId(lastRowId, "user"), "last row id should be false");
//		expectEquals(lastRowId, -1, "Last row id not -1");
//		++lastRowId;
		expect(db->insertUser(lastRowId, userName), "could not insert user");
		expect(db->getLastId(lastRowId, "user"), "last row id should be false");
		expectEquals(lastRowId, 0, "Last row id not 0");

		beginTest("Check if user exists");

		expect(db->checkIfUserExists(userName));

		beginTest("Insert gpx file");

		int fileId = 0;
		expect(db->insertFileName(fileId, gpxName, gpxMD5));

		beginTest("Check if city exists");

		expect(db->checkIfCityExists("Berlin"));
		expect(! db->checkIfCityExists("foobar"));

		beginTest("Check if file exists");

		expect(db->checkIfFileExists(gpxMD5));
		expect(! db->checkIfFileExists("foobar"));
		expect(db->checkIfFileNameExists(gpxName));

		beginTest("Insert GPS data");

		Array<GpsData> gpsDatas;

		GpsData gpsData0;
		gpsData0.setGpsData(0, 52.501140000, 13.435500000,
				String("2009-12-01T08:39:10Z"),36.000000, 1, 0,0, 2);
		gpsDatas.add(gpsData0);
		GpsData gpsData1;
		gpsData1.setGpsData(1, 52.501110000, 13.435620000,
				String("2009-12-01T08:39:13Z"), 36.000000, 1, 0,0, 2);
		gpsDatas.add(gpsData1);
		GpsData gpsData2;
		gpsData2.setGpsData(2, 52.501180000, 13.436070000,
				String("2009-12-01T08:39:31Z"), 36.000000, 1, 0,0, 2);
		gpsDatas.add(gpsData2);
		GpsData gpsData3;
		gpsData3.setGpsData(3, 52.497790000, 13.444170000,
				String("2009-12-01T08:50:42Z"),	36.000000, 2, 0,0, 2);
		gpsDatas.add(gpsData3);
		GpsData gpsData4;
		gpsData4.setGpsData(4, 52.497770000, 13.444160000,
				String("2009-12-01T08:50:45Z"),	36.000000, 2, 0,0, 2);
		gpsDatas.add(gpsData4);
		GpsData gpsData5;
		gpsData5.setGpsData(5, 52.497750000, 13.444170000,
				String("2009-12-01T08:50:48Z"),	36.000000, 2, 0,0, 2);
		gpsDatas.add(gpsData5);

		for (int j = 0; j < 6; ++j) {
			expect(db->insertGpsData(gpsDatas[j]));
		}

		beginTest("Check if GPS data exits");

		expect(db->checkIfGpsDataExsist("2009-12-01T08:50:45Z", 0));
		expect(! db->checkIfGpsDataExsist("2009-12-01T08:50:41Z", 0));


		db->closeDbConnection();
		delete db;

		if(dbFile.existsAsFile())
			dbFile.deleteFile();
	}
};

static DBConnectorTest dbConnectorTest;



#endif // _DBCONNECTORTEST_H_
