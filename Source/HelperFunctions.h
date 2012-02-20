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
                    const double lat);

    static bool isInCircle2(const double centreX,
                        const double centreY,
                        const double radius,
                        const double lon,
                        const double lat,
                        const char unit='K');

    static int findLocation(const Array<GpsLocation>& locations,
    		const double lon, const double lat);

private:
    Helper(){}
    ~Helper(){}
};

#endif // _HELPERFUNCTIONS_H_
