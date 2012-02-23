/*
 * GMLParser.cpp
 *
 *  Created on: Feb 23, 2012
 *      Author: peter
 */
#include "includes.h"
#include "GMLParser.h"

Array<GpsLocation> GMLParser::parse(const String& gmlFile)
{
	Array<GpsLocation> gpsLocVec;
	XmlDocument xmlDoc(gmlFile);
	XmlElement* xmlRoot = xmlDoc.getDocumentElement();

	 if (xmlRoot == nullptr)
	 {
		 String error = xmlDoc.getLastParseError();
	 }
	 else
	 {
		 int index = 0;
		 forEachXmlChildElementWithTagName(*xmlRoot, featureMember, "gml:featureMember")
		 {
			 ++index;
			 GpsLocation loc;
			 loc.index = index;

			 XmlElement* citydefs = featureMember->getChildByName("ogr:citydefs");
			 XmlElement* geometryProperty = citydefs->getChildByName("ogr:geometryProperty");
			 XmlElement* polygon = geometryProperty->getChildByName("gml:Polygon");
			 XmlElement* outerBoundaryIs = polygon->getChildByName("gml:outerBoundaryIs");
			 XmlElement* linearRing = outerBoundaryIs->getChildByName("gml:LinearRing");
			 XmlElement* coordinates = linearRing->getChildByName("gml:coordinates");


			 String coordsStr = coordinates->getAllSubText();
			 StringArray tokens;
			 tokens.addTokens(coordsStr, " ", "\"");
			 for (int i=0; i<tokens.size(); i++)
			 {
			    Point<double> point;
			    int commaIndex = tokens[i].indexOfChar(',');
			    double py = tokens[i].substring(0,commaIndex).getDoubleValue();
			    double px = tokens[i].substring(commaIndex+1).getDoubleValue();
			    point.addXY(px, py);
			    loc.polygon.add(point);
			 }
			 XmlElement* city = citydefs->getChildByName("ogr:city");
			 loc.city = city->getAllSubText();

			 XmlElement* country = citydefs->getChildByName("ogr:country");
			 loc.country = country->getAllSubText();
			 gpsLocVec.add(loc);
		 }
	 }
	 delete xmlRoot;
	return gpsLocVec;
}


//==============================================================================
#if UNIT_TESTS

class GMLParserTester : public UnitTest {
public:
	GMLParserTester() : UnitTest("GMLParser") {}

	void runTest()
	{
	    String gmlFile = CharPointer_UTF8(BinaryData::citydefs_gml);
	    Array<GpsLocation> locs = GMLParser::parse(gmlFile);

	    beginTest("parse");

	    String testCity = "Berlin";
	    String testCountry = "DE";
	    Array<Point<double> > points;
	    points.add(Point<double>(52.37048433239088,13.101559835297458));
	    points.add(Point<double>(52.657235386769905,13.101559835297458));
	    points.add(Point<double>(52.657235386769905,13.700291048547339));
	    points.add(Point<double>(52.37048433239088,13.700291048547339));
	    points.add(Point<double>(52.37048433239088,13.101559835297458));
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
	}

};

static GMLParserTester gmlParserTester;

#endif
