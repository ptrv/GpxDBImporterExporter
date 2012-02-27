
#ifndef _DBCONNECTORTEST_H_
#define _DBCONNECTORTEST_H_

class DBConnectorTest : public UnitTest {
public:
	DBConnectorTest() : UnitTest("DBConnector") {}

	void runTest()
	{
		String dbPathRelative = "../../../data/testdata/test.db";
		String dbPath = File::getCurrentWorkingDirectory().getChildFile(dbPathRelative).getFullPathName();
		DBConnector* db = new DBConnector(dbPath);
		db->setupDbConnection();

		beginTest("Check if city exists");

		expect(db->checkIfCityExists("Berlin"));
		expect(! db->checkIfCityExists("foobar"));

		beginTest("Check if file exists");

//		expect(db->checkIfFileExists(""));
		expect(! db->checkIfFileExists("foobar"));

		db->closeDbConnection();
		delete db;
	}
};

static DBConnectorTest dbConnectorTest;

#endif // _DBCONNECTORTEST_H_
