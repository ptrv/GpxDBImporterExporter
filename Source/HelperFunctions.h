/*==========================================================
 Copyright (c) Peter Vasil, 2011
 ==========================================================*/

#ifndef _HELPERFUNCTIONS_H_
#define _HELPERFUNCTIONS_H_

#include "Data.h"

class Helper
{
public:
    static bool isInCircle(const double centreX,
                    const double centreY,
                    const double radius,
                    const double lon,
                    const double lat)
    {
        double squareDistance = pow((centreX - lon), 2) + pow((centreY - lat), 2);
        return squareDistance < pow(radius, 2);
//	double squareDistance = (centreX - lon)*(centreX - lon) + (centreY - lat)*(centreY - lat);
//	double squareRadius = radius*radius;
//	return squareDistance < squareRadius;
    }

    static int findLocation(const Array<GpsLocation>& locations, const double lon, const double lat)
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

private:
    Helper();
    ~Helper();
};

#endif // _HELPERFUNCTIONS_H_
