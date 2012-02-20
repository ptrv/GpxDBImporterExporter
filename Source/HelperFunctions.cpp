/*
 * HelperFunctions.cpp
 *
 *  Created on: Feb 20, 2012
 *      Author: peter
 */

#include "includes.h"
#include "HelperFunctions.h"


extern double distance(double lat1, double lon1, double lat2, double lon2, char unit);


bool Helper::isInCircle(const double centreX, const double centreY,
		const double radius, const double lon, const double lat)
{
    double squareDistance = pow((centreX - lon), 2) + pow((centreY - lat), 2);
    return squareDistance < pow(radius, 2);
}

bool Helper::isInCircle2(const double centreX, const double centreY,
		const double radius, const double lon, const double lat, const char unit)
{
	double dist = distance(centreY, centreX, lat, lon, unit);
	return dist < radius;
}

int Helper::findLocation(const Array<GpsLocation>& locations,
		const double lon, const double lat)
{
    int locationId = 0;
    for (unsigned int i = 0; i < locations.size(); ++i)
    {
        if(isInCircle(locations[i].longitude, locations[i].latitude, locations[i].radius, lon, lat))
        {
            locationId = locations[i].index;
            break;
        }
    }
    return locationId;
}


//==============================================================================
#if UNIT_TESTING

class HelperFunctionsTester  : public UnitTest
{
public:
	HelperFunctionsTester()  : UnitTest ("HelperFunctions") {}

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

	}
};

static HelperFunctionsTester helperFunctionsTester;

#endif

