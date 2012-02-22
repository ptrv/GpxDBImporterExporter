/*
 * HelperFunctions.cpp
 *
 *  Created on: Feb 20, 2012
 *      Author: peter
 */

#include "includes.h"
#include "HelperFunctions.h"

extern double distance(double lat1, double lon1, double lat2, double lon2,
		char unit);

int Helper::findLocation(const Array<GpsLocation>& locations,
		const double lon, const double lat, const char boundings) {
	int locationId = 0;
	for (unsigned int i = 0; i < locations.size(); ++i) {
		switch (boundings) {
			case 'U':
				if (isInCircle(locations[i].longitude, locations[i].latitude,
						locations[i].radius, lon, lat))
				{
					locationId = locations[i].index;
					break;
				}
				break;
			case 'C':
				if (isInCircle2(locations[i].longitude, locations[i].latitude,
						locations[i].radiusKm, lon, lat, 'K'))
				{
					locationId = locations[i].index;
					break;
				}
				break;
			case 'B':
				if(isInBoundingBox(lon, lat,
						locations[i].topLeft.getX(),
						locations[i].topLeft.getY(),
						locations[i].bottomRight.getX(),
						locations[i].bottomRight.getY()))
				{
					locationId = locations[i].index;
					break;
				}
				break;
			case 'P':
				if(isInPolygon(lon, lat, locations[i].polygon))
				{
					locationId = locations[i].index;
					break;
				}
				break;
			default:
				break;
		}
	}
	return locationId;
}

bool Helper::isInCircle(const double centreX, const double centreY,
		const double radius, const double lon, const double lat) {
	double squareDistance = pow((centreX - lon), 2) + pow((centreY - lat), 2);
	return squareDistance < pow(radius, 2);
}

bool Helper::isInCircle2(const double centreX, const double centreY,
		const double radius, const double lon, const double lat,
		const char unit) {
	double dist = distance(centreY, centreX, lat, lon, unit);
	return dist < radius;
}

bool Helper::isInBoundingBox(const double lon, const double lat,
		const double lonTopLeft, const double latTopLeft,
		const double lonBootonRight, const double latBootonRight)
{
	//checks to see if bounding box crosses 180 degrees
	  if(lonTopLeft > lonBootonRight)
	  {
	      if(lonTopLeft >= lon && lonBootonRight <= lon
	         && latTopLeft >= lat && latBootonRight <= lat)
	      {
	    	  return true;
	      }
	  }
	  else
	  {
	      if(lonTopLeft <= lon && lonBootonRight >= lon
	        && latTopLeft >= lat && latBootonRight <= lat)
	      {
	    	  return true;
	       }
	  }
	  return false;
}

bool Helper::isInPolygon(const double lon, const double lat,
		const Array< Point<double> >& points)
{
	int i;
	int j = points.size()-1;
	bool inPoly = false;

	for (i = 0; i<points.size(); i++)
	{
		if ((points[i].getX() < lon && points[j].getX() >= lon)
				|| (points[j].getX() < lon && points[i].getX() >= lon))
		{
			if (points[i].getY() + (lon - points[i].getX()) /
					(points[j].getX() - points[i].getX()) * (points[j].getY()
							- points[i].getY()) < lat)
			{
				inPoly=!inPoly;
			}
		}
		j=i;
	}
	return inPoly;
}



//==============================================================================
#if UNIT_TESTS

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

		beginTest ("isInBoundingBox");

		beginTest ("isInPolygon");

	}
};

static HelperFunctionsTester helperFunctionsTester;

#endif

