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
		const double lon, const double lat, const char boundingType) {
	int locationId = 0;
	for (unsigned int i = 0; i < locations.size(); ++i) {
		switch (boundingType) {
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
		const double lonBottomRight, const double latBottomRight)
{
	//checks to see if bounding box crosses 180 degrees
	  if(lonTopLeft > lonBottomRight)
	  {
	      if(lonTopLeft >= lon && lonBottomRight <= lon
	         && latTopLeft >= lat && latBottomRight <= lat)
	      {
	    	  return true;
	      }
	  }
	  else
	  {
	      if(lonTopLeft <= lon && lonBottomRight >= lon
	        && latTopLeft >= lat && latBottomRight <= lat)
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

void Helper::getPointsFromPolygonString(const String& polyStr,
		Array<Point<double> >& points)
{
	 StringArray tokens;
	 tokens.addTokens(polyStr, " ", "\"");
	 for (int i=0; i<tokens.size(); i++)
	 {
	    Point<double> point;
	    int commaIndex = tokens[i].indexOfChar(',');
	    double px = tokens[i].substring(0,commaIndex).getDoubleValue();
	    double py = tokens[i].substring(commaIndex+1).getDoubleValue();
	    point.addXY(px, py);
	    points.add(point);
	 }
}
String Helper::getPolygonStringFromPoints(const Array<Point<double> >& points)
{
	String polyStr = "";
	for (int j = 0; j < points.size(); ++j) {
		const Point<double>& p = points[j];
		polyStr << p.x << "," << p.y;
		if(j < points.size()-1)
		{
			polyStr << " ";
		}
	}
	return polyStr;
}



GpsMinMax Helper::getMinMaxForGpsLocations(const Array<GpsLocation>& locs)
{
	double minLon = std::numeric_limits<double>::max();
	double minLat = std::numeric_limits<double>::max();
	double maxLon = -std::numeric_limits<double>::max();
	double maxLat = -std::numeric_limits<double>::max();

	for (unsigned int i = 0; i < locs.size(); ++i) {
		for (unsigned int j = 0; j < locs[i].polygon.size(); ++j)
		{
			double x = locs[i].polygon[j].x;
			double y = locs[i].polygon[j].y;
			if (x < minLon) minLon = x;
			if (x > maxLon) maxLon = x;
			if (y < minLat) minLat = y;
			if (y > maxLat) maxLat = y;
		}
	}

	GpsMinMax gpsMinMax;
	gpsMinMax.minLat = minLat;
	gpsMinMax.minLon = minLon;
	gpsMinMax.maxLat = maxLat;
	gpsMinMax.maxLon = maxLon;

	return gpsMinMax;
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

	    Point<double> topLeft(13.1, 52.9);
	    Point<double> bottomRight(13.9, 52.1);
	    expect(Helper::isInBoundingBox(cX2, cY2, topLeft.x, topLeft.y,
	    		bottomRight.x, bottomRight.y));


	}
};

static HelperFunctionsTester helperFunctionsTester;

#endif

