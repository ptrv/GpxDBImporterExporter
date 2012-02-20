/*=======================================================
 Copyright (c) Peter Vasil, 2011
=======================================================*/

#include "FileExporter.h"
#include "Data.h"

#include "DBConnector.h"

FileExporter::FileExporter(const String& dbPath, const String& savePath, const String& query)
:
ThreadWithProgressWindow("GPX Export", true, false),
m_dbPath(dbPath),
m_savePath(savePath),
m_status(String::empty),
m_query(query)
{
}

const String& FileExporter::getStatus() const
{
	return m_status;
}

FileExporter::~FileExporter()
{
}

void FileExporter::run()
{
	Array<GpsData> gpsDatas;

	GpsMinMax gpsMinMax;

    setStatusMessage("Reading database...");

    DBConnector dbcon(m_dbPath);
    dbcon.setupDbConnection();
    setProgress(1.1);
    //-----
    if(dbcon.getGpsDataForExport(gpsDatas,gpsMinMax, m_query))
	{
//		for (int i = 0; i < gpsDatas.size(); ++i) {
//			std::cout << "nr: " << i << ", " << gpsDatas[i].getGpsDataId() << ", ";
//			std::cout << gpsDatas[i].getLatitude() << ", ";
//			std::cout << gpsDatas[i].getLongitude() << ", ";
//			std::cout << gpsDatas[i].getElevation() << ", ";
//			std::cout << gpsDatas[i].getTime() << ", ";
//			std::cout << gpsDatas[i].getSegment() << std::endl;
//		}

		// -----------------------------------------------------------------------------
		Array< Array<GpsData> > gpsSegAndPoints;
		getGpsSegmentsAndPoints(gpsDatas, gpsSegAndPoints);

		generateGpxFile(gpsSegAndPoints, gpsMinMax, gpsDatas.size());

		// -----------------------------------------------------------------------------
		m_status = String::empty;
		m_status = "Got ";
		m_status += gpsDatas.size();
		m_status += " rows. Export succeeded!";
	}
	else
	{
		m_status = "DB Error!";
	}

	//-----
	dbcon.closeDbConnection();
}

void FileExporter::getGpsSegmentsAndPoints(Array<GpsData>& data, Array< Array<GpsData> >& segAndPoint)
{
	segAndPoint.clear();
	Array<GpsData> tmpDatas;
	int lastSegNum = -1;
	bool firstTime = true;

	for (int i = 0; i < data.size(); ++i) {

		if(data[i].getSegment() == lastSegNum)
		{
			tmpDatas.add(data[i]);
			lastSegNum = data[i].getSegment();
		}
		else
		{
			if(!firstTime)
				segAndPoint.add(tmpDatas);
			else
				firstTime = false;

			tmpDatas.clear();
			tmpDatas.add(data[i]);
			lastSegNum = data[i].getSegment();
		}
	}
	segAndPoint.add(tmpDatas);


}
void FileExporter::generateGpxFile(Array< Array<GpsData> >& segAndPoint, GpsMinMax gpsMinMax, int size)
{
    setStatusMessage("Generating Gpx file structure...");
    DBG(size);
	// -----------------------------------------------------------------------------
	// Header
	// -----------------------------------------------------------------------------
	XmlElement gpxFile ("gpx");
	gpxFile.setAttribute("version", "1.0");
	gpxFile.setAttribute("creator", "avp::ptr - http://avp-ptr.de");
	gpxFile.setAttribute("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
	gpxFile.setAttribute("xmlns", "http://www.topografix.com/GPX/1/0");
	gpxFile.setAttribute("xsi:schemaLocation", "http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd");

	// -----------------------------------------------------------------------------

	XmlElement* gpxFileTime = new XmlElement("time");
	gpxFileTime->addTextElement(Time::getCurrentTime().formatted("%Y-%m-%dT%H:%M:%SZ"));
	gpxFile.addChildElement(gpxFileTime);

	XmlElement* gpxMinMax = new XmlElement("bounds");
	gpxMinMax->setAttribute("minlat", gpsMinMax.minLat);
	gpxMinMax->setAttribute("minlon", gpsMinMax.minLon);
	gpxMinMax->setAttribute("maxlat", gpsMinMax.maxLat);
	gpxMinMax->setAttribute("maxlon", gpsMinMax.maxLon);
	gpxFile.addChildElement(gpxMinMax);

	// -----------------------------------------------------------------------------
	setProgress(0.0);
	int tmpSize = 0;
	for (int i = 0; i < segAndPoint.size(); ++i) {
		XmlElement* trk = new XmlElement("trk");
		XmlElement* trkName = new XmlElement("name");
		String nameElem = "ACTIVE LOG #";
		nameElem += i;
		if(segAndPoint[i].size() > 0)
		{
			trkName->addTextElement(segAndPoint[i][0].getTime());
		}
		else
		{
			trkName->addTextElement(nameElem);
		}
		XmlElement* trkNum = new XmlElement("number");
		trkNum->addTextElement(String(i));
		XmlElement* trkSeg = new XmlElement("trkseg");

		trk->addChildElement(trkName);
		trk->addChildElement(trkNum);
		trk->addChildElement(trkSeg);

		for (int j = 0; j < segAndPoint[i].size(); ++j) {
			XmlElement* trkpt = new XmlElement("trkpt");
			trkpt->setAttribute("lat", segAndPoint[i][j].getLatitude());
			trkpt->setAttribute("lon", segAndPoint[i][j].getLongitude());
			XmlElement* trkEle = new XmlElement("ele");
			trkEle->addTextElement(String(segAndPoint[i][j].getElevation()));
			XmlElement* trkTime = new XmlElement("time");
			trkTime->addTextElement(segAndPoint[i][j].getTime());
			trkpt->addChildElement(trkEle);
			trkpt->addChildElement(trkTime);
			trkSeg->addChildElement(trkpt);
			++tmpSize;
            setProgress((double)tmpSize/size);
		}
		gpxFile.addChildElement(trk);
	}


	// -----------------------------------------------------------------------------
    setStatusMessage("Saving file...");

	File saveFile(m_savePath);
	if(saveFile.existsAsFile())
	{
		saveFile.deleteFile();
	}
	gpxFile.writeToFile(saveFile, String::empty);
}
