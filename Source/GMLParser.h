/*
 * GMLParser.h
 *
 *  Created on: Feb 23, 2012
 *      Author: Peter Vasil
 */

#ifndef GMLPARSER_H_
#define GMLPARSER_H_

#include "Data.h"

class GMLParser {
private:
	GMLParser(){}
	~GMLParser(){}
public:
	static Array<GpsLocation> parse(const String& gmlFile);
};

#endif /* GMLPARSER_H_ */
