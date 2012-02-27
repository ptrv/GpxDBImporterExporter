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
	box->addChildElement(coordUpperRight);
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

#include "../testsuite/GMLUtilsTest.h"

#endif
