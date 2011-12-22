/*=======================================================
 Copyright (c) Peter Vasil, 2011
=======================================================*/

#ifndef _FILEEXPORTER_H_
#define _FILEEXPORTER_H_

#include "includes.h"
#include "Data.h"

class FileExporter : public ThreadWithProgressWindow 
{
public:
	FileExporter(const String& dbPath, const String& savePath, const String& query);
	~FileExporter();
	
	void run();
	const String& getStatus() const;
	
	void getGpsSegmentsAndPoints(Array<GpsData>& data, Array< Array<GpsData> >& segAndPoint);
	void generateGpxFile(Array< Array<GpsData> >& segAndPoint, GpsMinMax gpsMinMax, int size);

public:
	String m_dbPath;
	String m_savePath;
	String m_status;
	String m_query;
};



#endif  // _FILEEXPORTER_H_
