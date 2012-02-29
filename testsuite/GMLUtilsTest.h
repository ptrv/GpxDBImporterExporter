
#ifndef _GMLUTILSTEST_H_
#define _GMLUTILSTEST_H_

class GMLParserTester : public UnitTest {
public:
	GMLParserTester() : UnitTest("GMLParser") {}

	bool isEqualWithEpsilon(double actual, double expected, double epsilon)
	{
		if(actual > expected-epsilon && actual < expected+epsilon)
			return true;
		else
			return false;
	}

	void runTest()
	{
	    String gmlFile = CharPointer_UTF8(BinaryData::citydefs_gml);
	    Array<GpsLocation> locs = GMLUtils::parse(gmlFile);

	    beginTest("parse");

	    String testCity = "Berlin";
	    String testCountry = "DE";
	    Array<Point<double> > points;
	    points.add(Point<double>(13.101559835297458,52.37048433239088));
	    points.add(Point<double>(13.101559835297458,52.657235386769905));
	    points.add(Point<double>(13.700291048547339,52.657235386769905));
	    points.add(Point<double>(13.700291048547339,52.37048433239088));
	    points.add(Point<double>(13.101559835297458,52.37048433239088));
	    expectEquals(locs[0].city, testCity);
	    expectEquals(locs[0].country, testCountry);
	    expectEquals(locs[0].polygon[0].x, points[0].x);
	    expectEquals(locs[0].polygon[0].y, points[0].y);
	    expectEquals(locs[0].polygon[1].x, points[1].x);
	    expectEquals(locs[0].polygon[1].y, points[1].y);
	    expectEquals(locs[0].polygon[2].x, points[2].x);
	    expectEquals(locs[0].polygon[2].y, points[2].y);
	    expectEquals(locs[0].polygon[3].x, points[3].x);
	    expectEquals(locs[0].polygon[3].y, points[3].y);
	    expectEquals(locs[0].polygon[4].x, points[4].x);
	    expectEquals(locs[0].polygon[4].y, points[4].y);

	    beginTest("write");

	    File testFile(File::getSpecialLocation(File::tempDirectory).getChildFile("testFile.gml"));
        
        if(testFile.existsAsFile())
            testFile.deleteFile();
        
        bool writeOk = GMLUtils::write(locs, testFile.getFullPathName());

	    expect(writeOk, "Could not write file");

	    
	    String testFileAsString = testFile.loadFileAsString();
	    Array<GpsLocation> locs2 = GMLUtils::parse(testFileAsString);

	    const bool sizeBothLocsEquals = (locs.size() == locs2.size());
	    expect(sizeBothLocsEquals, "size of actual and expected differs");

	    if(! sizeBothLocsEquals)
	    	return;

	    double epsilon = 0.0000000000001;
	    for (int i = 0; i < locs.size(); ++i) {
            String msg = "Location " + String(i) + ": ";
		    expectEquals(locs[i].city, locs2[i].city, (msg+"city"));
		    expectEquals(locs[i].country, locs2[i].country, (msg+"country"));
            msg << locs[i].city << ": ";
		    expect(isEqualWithEpsilon(locs[i].polygon[0].x, locs2[i].polygon[0].x,epsilon), (msg+"polygon 0 x"));
		    expect(isEqualWithEpsilon(locs[i].polygon[0].y, locs2[i].polygon[0].y,epsilon), (msg+"polygon 0 y"));
		    expect(isEqualWithEpsilon(locs[i].polygon[1].x, locs2[i].polygon[1].x,epsilon), (msg+"polygon 1 x"));
		    expect(isEqualWithEpsilon(locs[i].polygon[1].y, locs2[i].polygon[1].y,epsilon), (msg+"polygon 1 y"));
		    expect(isEqualWithEpsilon(locs[i].polygon[2].x, locs2[i].polygon[2].x,epsilon), (msg+"polygon 2 x"));
		    expect(isEqualWithEpsilon(locs[i].polygon[2].y, locs2[i].polygon[2].y,epsilon), (msg+"polygon 2 y"));
		    expect(isEqualWithEpsilon(locs[i].polygon[3].x, locs2[i].polygon[3].x,epsilon), (msg+"polygon 3 x"));
		    expect(isEqualWithEpsilon(locs[i].polygon[3].y, locs2[i].polygon[3].y,epsilon), (msg+"polygon 3 y"));
		    expect(isEqualWithEpsilon(locs[i].polygon[4].x, locs2[i].polygon[4].x,epsilon), (msg+"polygon 4 x"));
		    expect(isEqualWithEpsilon(locs[i].polygon[4].y, locs2[i].polygon[4].y,epsilon), (msg+"polygon 4 y"));
	    }

        if(testFile.existsAsFile())
            testFile.deleteFile();
	}
};

static GMLParserTester gmlParserTester;

#endif
