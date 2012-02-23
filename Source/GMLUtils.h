/*
 * GMLUtils.h
 *
 *  Created on: Feb 23, 2012
 *      Author: Peter Vasil
 */

#ifndef GMLUTILS_H_
#define GMLUTILS_H_

#include "Data.h"

class GMLUtils {
private:
	GMLUtils(){}
	~GMLUtils(){}
public:
	static Array<GpsLocation> parse(const String& gmlFile);
	static bool write(const Array<GpsLocation>& locs,
			const String& filePathToWrite);
};

#endif /* GMLPARSER_H_ */
