/*
 * GMLParser.cpp
 *
 *  Created on: Feb 23, 2012
 *      Author: peter
 */
#include "includes.h"
#include "GMLUtils.h"
#include "HelperFunctions.h"

Array<GpsLocation> GMLUtils::parse(const String& gmlFile)
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
			 Helper::getPointsFromPolygonString(coordsStr, loc.polygon);

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

bool GMLUtils::write(const Array<GpsLocation>& locs, const String& filePathToWrite)
{
	GpsMinMax gpsMaxMin = Helper::getMinMaxForGpsLocations(locs);

	// -------------------------------------------------------------------------
	// Header
	// -------------------------------------------------------------------------
	XmlElement* gml = new XmlElement("ogr:FeatureCollection");
	gml->setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	gml->setAttribute("xmlns:ogr", "http://ogr.maptools.org/");
	gml->setAttribute("xmlns:gml", "http://www.opengis.net/gml");
	gml->setAttribute("xsi:schemaLocation", "http://ogr.maptools.org/ citydefs.xsd");

	// -------------------------------------------------------------------------

	XmlElement* boundedBy = new XmlElement("gml:boundedBy");
	XmlElement* box = new XmlElement("gml:Box");
	XmlElement* coordBottomLeft = new XmlElement("gml:coord");
	XmlElement* coordUpperRight = new XmlElement("gml:coord");
	XmlElement* bottomLeftX = new XmlElement("gml:X");
	XmlElement* bottomLeftY = new XmlElement("gml:Y");
	XmlElement* upperRightX = new XmlElement("gml:X");
	XmlElement* upperRightY = new XmlElement("gml:Y");

	gml->addChildElement(boundedBy);
	boundedBy->addChildElement(box);
	box->addChildElement(coordBottomLeft);
	bottomLeftX->addTextElement(String(gpsMaxMin.minLon));
	bottomLeftY->addTextElement(String(gpsMaxMin.minLat));
	coordBottomLeft->addChildElement(bottomLeftX);
	coordBottomLeft->addChildElement(bottomLeftY);
	boundedBy->addChildElement(coordUpperRight);
	upperRightX->addTextElement(String(gpsMaxMin.maxLon));
	upperRightY->addTextElement(String(gpsMaxMin.maxLat));
	coordUpperRight->addChildElement(upperRightX);
	coordUpperRight->addChildElement(upperRightY);

	// -------------------------------------------------------------------------

	for (int i = 0; i < locs.size(); ++i) {
		XmlElement* featureMember = new XmlElement("gml:featureMember");
		XmlElement* citydefs = new XmlElement("ogr:citydefs");
		XmlElement* geometryProperty = new XmlElement("ogr:geometryProperty");
		XmlElement* polygon = new XmlElement("gml:Polygon");
		XmlElement* outerBoundaryIs = new XmlElement("gml:outerBoundaryIs");
		XmlElement* linearRing = new XmlElement("gml:LinearRing");
		XmlElement* coordinates = new XmlElement("gml:coordinates");

		XmlElement* pkuid = new XmlElement("ogr:pkuid");
		XmlElement* city = new XmlElement("ogr:city");
		XmlElement* country = new XmlElement("ogr:country");

		gml->addChildElement(featureMember);
		citydefs->setAttribute("fid", ("F"+String(i+2)));
		featureMember->addChildElement(citydefs);
		citydefs->addChildElement(geometryProperty);
		geometryProperty->addChildElement(polygon);
		polygon->addChildElement(outerBoundaryIs);
		outerBoundaryIs->addChildElement(linearRing);
		String polyStr = Helper::getPolygonStringFromPoints(locs[i].polygon);
		coordinates->addTextElement(polyStr);
		linearRing->addChildElement(coordinates);

		pkuid->addTextElement(String(i+2));
		citydefs->addChildElement(pkuid);
		city->addTextElement(locs[i].city.toUTF8());
		citydefs->addChildElement(city);
		country->addTextElement(locs[i].country);
		citydefs->addChildElement(country);
	}
	// -------------------------------------------------------------------------

	File saveFile(filePathToWrite);
	if(saveFile.existsAsFile())
	{
		saveFile.deleteFile();
	}
	bool writeOk = gml->writeToFile(saveFile, String::empty);

	delete gml;

	return writeOk;
}


//==============================================================================
#if UNIT_TESTS

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

	    bool writeOk = GMLUtils::write(locs,
	    		File::getSpecialLocation(File::tempDirectory).getChildFile("testFile.gml").getFullPathName());

	    expect(writeOk, "Could not write file");

	    File testFile(File::getSpecialLocation(File::tempDirectory).getChildFile("testFile.gml"));
	    String testFileAsString = testFile.loadFileAsString();
	    Array<GpsLocation> locs2 = GMLUtils::parse(testFileAsString);

	    const bool sizeBothLocsEquals = (locs.size() == locs2.size());
	    expect(sizeBothLocsEquals, "size of actual and expected differs");

	    if(! sizeBothLocsEquals)
	    	return;

	    double epsilon = 0.0000001;
	    for (int i = 0; i < locs.size(); ++i) {
		    expectEquals(locs[i].city, locs2[i].city);
		    expectEquals(locs[i].country, locs2[i].country);
		    expect(isEqualWithEpsilon(locs[i].polygon[0].x, locs2[i].polygon[0].x,epsilon));
		    expect(isEqualWithEpsilon(locs[i].polygon[0].y, locs2[i].polygon[0].y,epsilon));
		    expect(isEqualWithEpsilon(locs[i].polygon[1].x, locs2[i].polygon[1].x,epsilon));
		    expect(isEqualWithEpsilon(locs[i].polygon[1].y, locs2[i].polygon[1].y,epsilon));
		    expect(isEqualWithEpsilon(locs[i].polygon[2].x, locs2[i].polygon[2].x,epsilon));
		    expect(isEqualWithEpsilon(locs[i].polygon[2].y, locs2[i].polygon[2].y,epsilon));
		    expect(isEqualWithEpsilon(locs[i].polygon[3].x, locs2[i].polygon[3].x,epsilon));
		    expect(isEqualWithEpsilon(locs[i].polygon[3].y, locs2[i].polygon[3].y,epsilon));
		    expect(isEqualWithEpsilon(locs[i].polygon[4].x, locs2[i].polygon[4].x,epsilon));
		    expect(isEqualWithEpsilon(locs[i].polygon[4].y, locs2[i].polygon[4].y,epsilon));
	    }
	}
};

static GMLParserTester gmlParserTester;

#endif
