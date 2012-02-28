
#ifndef _HELPERFUNCTIONSTEST_H_
#define _HELPERFUNCTIONSTEST_H_

class HelperFunctionsTester : public UnitTest
{
public:
	HelperFunctionsTester() : UnitTest ("HelperFunctions") {}

	void runTest()
	{
		double cY = 52.5137;

		double cX = 13.474;
		double radius = 6;
		double cY2 = 52.535;
		double cX2 = 13.407;

		beginTest ("isInCircle");

		expect(Helper::isInCircle(cX, cY, 0.09,cX2, cY2));

		beginTest ("isInCircle2");

		expect(Helper::isInCircle2(cX, cY, 6.0,cX2, cY2, 'K'));
		expect(Helper::isInCircle2(cX, cY, 6.0,cX2, cY2, 'M'));
		expect(Helper::isInCircle2(cX, cY, 6.0,cX2, cY2, 'N'));

//		beginTest ("isInBoundingBox");

		beginTest ("isInPolygon");

	    Array<Point<double> > points;
	    points.add(Point<double>(13.101559835297458,52.37048433239088));
	    points.add(Point<double>(13.101559835297458,52.657235386769905));
	    points.add(Point<double>(13.700291048547339,52.657235386769905));
	    points.add(Point<double>(13.700291048547339,52.37048433239088));
	    points.add(Point<double>(13.101559835297458,52.37048433239088));

	    expect(Helper::isInPolygon(cX2, cY2, points));

	    beginTest("IsInBoundingBox");

	    Point<double> bottomLeft(13.1, 52.1);
	    Point<double> topRight(13.9, 52.9);
	    expect(Helper::isInBoundingBox(cX2, cY2, bottomLeft.x, bottomLeft.y,
	    		topRight.x, topRight.y));
	    expect(! Helper::isInBoundingBox(cX2, cY2, bottomLeft.x, bottomLeft.y,
	    		topRight.x-0.7, topRight.y-0.7));


	}
};

static HelperFunctionsTester helperFunctionsTester;


#endif // _HELPERFUNCTIONSTEST_H_
